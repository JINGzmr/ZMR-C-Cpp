#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h> //errno的头文件
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h> // getpwuid的头文件
#include <grp.h> // getgrgid的头文件
#include <time.h> // ctime的头文件
#include <locale.h>
#include <langinfo.h>
#include <unistd.h> //getcwd、chdir的头文件

char *filenames[4096];    // 存放文件名的数组，方便a-z排序
long int *filetime[4096]; // 存文件修改时间，和filenamet一一对应
int file_cnt = 0;         // 目录中文件个数，用来计数

#define a 0
#define l 1
#define R 2
#define t 3 
#define r 4
#define i 5
#define s 6
//-a  -l -R  -t  -r -i  -s
//-a、-l、-R、-t、-r、-i、-s

void myls(int has[], const char *dirpath_name);                     // 打开、读取、关闭目录
void mystat(int has[], char *file_name);                            // 获取文件具体信息
void print(int has[], const char *file_name);                       // 打印没有-l的普通文件名
void print_file_information(char *file_name, struct stat *buf_ptr); // 打印文件具体信息
long long int total(const char *file_name[]);
void myls_i(struct stat *buf_ptr);
void myls_s(struct stat *buf_ptr);
void myls_t(char *filenames[]); // 不是*filenames
void myls_R(int has[], char path[]);
void restored_ls(struct dirent *cur_item); // 将目录中的文件依次存入数组中,便于后续排序及逆向输出

// 按a-z排序
void sort(char **filenames, int start, int end);
int compare(char *s1, char *s2);
void swap(char **s1, char **s2);
int partition(char **filenames, int start, int end);

int main(int argc, char *argv[])
{
    char ch;
    int has[8] = {0};
    int num = 0; // 记录-l/-lai的数目，若小于argc-1(即相差大于等于2时），则有可能是指定目录
    // char *dir;   // 存指定目录
    // dir = (char *)malloc(sizeof(char));
    char path[256]; // 存储路径
    while ((ch = getopt(argc, argv, "alRtris")) != -1)
    {
        switch (ch){
        case 'a':
            has[a] = 1;
            break;
        case 'l':
            has[l] = 1;
            break;
        case 'R':
            has[R] = 1;
            break;
        case 't':
            has[t] = 1;
            break;
        case 'r':
            has[r] = 1;
            break;
        case 'i':
            has[i] = 1;
            break;
        case 's':
            has[s] = 1;
            break;
        }
        num++;
    }

    getcwd(path, sizeof(path)); // 获取当前路径函数，并存入path

    int n;
    for (n = 1; n < argc; n++){
        if (argv[n][0] != '-'){
            strcpy(path, argv[n]);
        }
    }

    if (has[R]){
        myls_R(has, path);
    }
    else{
        myls(has, path);
    }

    return 0;
}

// 打开、读取、关闭目录
void myls(int has[], const char *dirpath_name)
{
    // 每次把filenames里面的内容清除，file_cnt归零，否则-R会在打印子目录时打印出上级目录的内容
    int n;
    for (n = 0; n < file_cnt; n++){
        filenames[n] = "\0";
    }
    file_cnt = 0;

    chdir(dirpath_name);
    DIR *cur_dir = NULL;
    struct dirent *cur_item = NULL;
    // 开目录
    cur_dir = opendir(dirpath_name);
    if (cur_dir == NULL){
        printf("目录打开错误!\n");
    }
    else{
        // 读目录
        while (1)
        {
            errno = 0;
            cur_item = readdir(cur_dir);
            if (errno != 0)
                printf("文件读取错误!\n");
            if (cur_item == NULL)
                break;
            // 判断-a
            // if ((cur_item->d_name[0] == '.' || cur_item->d_name[0] == '..') && has[a] == 0)// 报错：multi-character character constant，即..不是字符
            if ((cur_item->d_name[0] == '.' || strncmp(cur_item->d_name, "..", 2) == 0) && has[a] == 0)
                continue; // 在有-a参数时就不能跳过了

            restored_ls(cur_item);
        }

        //参数判断
        if (has[t]){ 
            myls_t(filenames);
        }
        else{
            sort(filenames, 0, file_cnt - 1);
        }

        if(has[s]||has[l]){ //打印总用量
            total(filenames);
        }

        if (has[l]) {
            int n;
            if (has[r]){
                for (n = file_cnt - 1; n >= 0; n--)
                    mystat(has, filenames[n]);
            }
            else{
                for (n = 0; n < file_cnt; n++)
                    mystat(has, filenames[n]);
            }
        }
        else{
            int n;
            if (has[r]){
                for (n = file_cnt - 1; n >= 0; n--)
                    print(has, filenames[n]);
            }
            else{
                for (n = 0; n < file_cnt; n++)
                    print(has, filenames[n]);
            }
        }
        printf("\n");
        closedir(cur_dir); // 关目录
    }
}

// 总用量
long long int total(const char *file_name[])
{
    long long int totall = 0;
    int n;
    for (n = 0; n < file_cnt; n++){
        struct stat file_message;   //就是不能定义成struct stat* file_message，否则一直段错误
        stat(file_name[n], &file_message);
        long long int size = (file_message.st_blocks)/2;
        totall += size;
    }
    printf("总用量 %lld\n", totall);
}

// 将目录中的文件依次存入数组中
void restored_ls(struct dirent *cur_item)
{
    filenames[file_cnt] = cur_item->d_name;
    // strcpy(filenames[file_cnt], cur_item->d_name); ????????
    // printf("%s\n",filenames[file_cnt]);
    file_cnt++;
}

void print(int has[], const char *file_name)
{
    struct stat buf;
    if (stat(file_name, &buf) == -1)
        ;
    // perror("stat");             // 有这一句会出现path不是当前路径时，报错‘ 获取文件信息错误!! ’
    // printf("获取文件信息错误!!\n");
    else{
        if (has[i]){ // 如果有-i参数，则执行
            myls_i(&buf);
        }
        if (has[s]){ // 如果有-s参数，则执行
            myls_s(&buf);
        }
    }
    printf("%s    ", file_name); // 不是很对齐
}

// 获取文件具体信息
// 有-l时执行
void mystat(int has[], char *file_name)
{
    struct stat file_message;
    if (stat(file_name, &file_message) == -1)
        ;
    // perror("stat");         // 有这一句会出现path不是当前路径时，报错‘ 获取文件信息错误!! ’
    else{
        if (has[i]){ // 如果有-i参数，则执行
            myls_i(&file_message);
        }
        if (has[s]){ // 如果有-s参数，则执行
            myls_s(&file_message);
        }
        print_file_information(file_name, &file_message); // 注意是&file_message
    }
}

void myls_i(struct stat *buf_ptr)
{
    printf("%ld ", buf_ptr->st_ino); // ino_t是long int 类型
}

// 在文件左侧显示文件大小（在-l左边，-i右边），以1024字节为块单位
// ls -s
void myls_s(struct stat *buf_ptr)
{
    printf("%5ld ", (buf_ptr->st_blocks) / 2); // blkcnt_t是long int 类型
}

// 按照最后一次修改时间进行排序
// buf_ptr->st_mtime可以直接进行比大小
// time_t相当于long类型
void myls_t(char *filenames[])
{                                                           
    int n, m;                                    // 改成这样出来的filetime都一样，就错了，无法进行时间排序-->因为struct stat *buf_ptr需要对 buf_ptr 进行动态内存分配，否则在调用 stat() 函数时会出现段错误
    struct stat buf;                             // struct stat *buf_ptr
    for (n = 0; n < file_cnt; n++){
        stat(filenames[n], &buf);               // buf_ptr
        filetime[n] = (long int *)buf.st_mtime; // buf_ptr->st_mtime
    }//如果只是long int，会有警告long int类型赋值给了long int*

    for (n = 0; n < file_cnt - 1; n++){
        for (m = 0; m < file_cnt - 1 - n; m++){
            if (filetime[m] < filetime[m + 1]) {// 降序
                long int *x;         //这也要一起改，加上*
                // char *y;
                // y=(char*)malloc(sizeof(char));

                x = filetime[m + 1]; // 若x=... 则报错：表达式必须是可修改的左值
                filetime[m + 1] = filetime[m];
                filetime[m] = x;

                swap(&filenames[m], &filenames[m + 1]);
                // 错！因为字符数组不能直接赋值
                // y[512]=filenames[m+1];
                // filenames[m+1]=filenames[m];
                // filenames[m]=y[512];

                // strcpy(y, filenames[m + 1]);
                // strcpy(filenames[m + 1], filenames[m]);
                // strcpy(filenames[m], y);

                // free(y);
            }
        }
    }
}


//下面这个是可以的！！！！！！！！

// void myls_t(char *filenames[])
// {
//     int n, m;
//     struct stat *buf; // 将 buf 声明为指向 struct stat 的指针
//     buf = (struct stat *)malloc(sizeof(struct stat) * file_cnt); // 动态分配内存空间
//     for (n = 0; n < file_cnt; n++){
//         stat(filenames[n], buf + n); // 使用指针访问元素
//         filetime[n] = (long int*)buf[n].st_mtime; // 使用指针访问元素
//     }

//     for (n = 0; n < file_cnt - 1; n++){
//         for (m = 0; m < file_cnt - 1 - n; m++){
//             if (filetime[m] < filetime[m + 1]) {// 降序
//                 long int *x;
//                 x = filetime[m + 1];
//                 filetime[m + 1] = filetime[m];
//                 filetime[m] = x;

//                 swap(&filenames[m], &filenames[m + 1]);
//             }
//         }
//     }
//     free(buf); // 释放动态分配的内存空间
// }


void myls_R(int has[], char pathname[])
{
    chdir(pathname);  //更改进程的当前工作目录,否则一直报错：无法获取除本.c文件目录下的其他文件
    char nextpath[512];

    DIR *ret_opendir = opendir(pathname); // 打开目录"pathname"
    if (ret_opendir == NULL)
        perror(ret_opendir);

    printf("%s:\n", pathname); // 打印pathname目录路径 "/home/zhangminrui/桌面/练习代码/Linux系统编程/notes:"
    myls(has, pathname);       // 打印该目录路径下的文件相关信息

    struct dirent *ret_readdir = NULL;         // 定义readdir函数返回的结构体变量
    while (ret_readdir = readdir(ret_opendir)) // 判断是否读取到目录尾
    {
        char *filename = ret_readdir->d_name; // 获取文件名

        // 优化显示路径（处理"./note/"与"./note"）
        int end = 0;  
        while (pathname[end])
            end++;
        strcpy(nextpath, pathname);  // 先把当前路径名给nextpath
        if (pathname[end - 1] != '/')
            strcat(nextpath, "/");
        strcat(nextpath, filename); // 再把当前文件名给nextpath

        struct stat file_message;                      
        if (lstat(nextpath, &file_message) == -1){  // 获取文件信息
            perror("lstat"); // stat读取文件错误则输出提示信息
        }
        else if (S_ISDIR(file_message.st_mode) && filename[0] != '.'){  // S_ISDIR() 判断一个路径是不是目录                                                 
            if (has[l] == 0){                                           // 筛选"."、".."与隐藏文件
                printf("\n");
            }
            myls_R(has, nextpath);
        }
    }

    closedir(ret_opendir);
}

// 打印文件具体信息
void print_file_information(char *file_name, struct stat *buf_ptr)
{
    // 第一列
    char first_column[11] = {0};
    // 第一个字母
    if (S_ISLNK(buf_ptr->st_mode)){
        first_column[0] = 'l';
    }
    else if (S_ISDIR(buf_ptr->st_mode)){
        first_column[0] = 'd';
    }
    else if (S_ISCHR(buf_ptr->st_mode)){
        first_column[0] = 'c';
    }
    else if (S_ISSOCK(buf_ptr->st_mode)){
        first_column[0] = 's';
    }
    else if (S_ISFIFO(buf_ptr->st_mode)){
        first_column[0] = 'p';
    }
    else if (S_ISBLK(buf_ptr->st_mode)){
        first_column[0] = 'b';
    }
    else{
        first_column[0] = '-';
    }

    // 后面三个为一组
    // r表示读权限,w表示写权限,x表示可执行权限,-表示无权限
    // 第一组为表示所有者权限
    first_column[1] = (buf_ptr->st_mode & S_IRUSR) ? 'r' : '-';
    first_column[2] = (buf_ptr->st_mode & S_IWUSR) ? 'w' : '-';
    first_column[3] = (buf_ptr->st_mode & S_IXUSR) ? 'x' : '-';

    // 第二组为表示组用户权限
    first_column[4] = (buf_ptr->st_mode & S_IRGRP) ? 'r' : '-';
    first_column[5] = (buf_ptr->st_mode & S_IWGRP) ? 'w' : '-';
    first_column[6] = (buf_ptr->st_mode & S_IXGRP) ? 'x' : '-';

    // 第三组为表示其他用户组的权限
    first_column[7] = (buf_ptr->st_mode & S_IROTH) ? 'r' : '-';
    first_column[8] = (buf_ptr->st_mode & S_IWOTH) ? 'w' : '-';
    first_column[9] = (buf_ptr->st_mode & S_IXOTH) ? 'x' : '-';

    printf("%s ", first_column);

    // 第二列
    // 目录：表示当前这个目录下面的一级目录个数
    // 文件：表示硬链接个数
    printf("%2d ", (int)buf_ptr->st_nlink);

    // 第三列
    // 该文件或目录的所有者
    struct passwd *pwuid_ptr;
    if ((pwuid_ptr = getpwuid(buf_ptr->st_uid)) != NULL){
        printf("%-8s ", pwuid_ptr->pw_name); //-8向左对齐
    }

    // 第四列
    // 表示所属的组
    struct group *group_ptr;
    if ((group_ptr = getgrgid(buf_ptr->st_gid)) != NULL){
        printf("%-8s ", group_ptr->gr_name); //-8向左对齐
    }

    // 第五列
    // 文件大小
    printf("%8ld ", (long int)buf_ptr->st_size); // 8ld向右对齐

    // 第六、七、八列
    // 月、日、时
    char *time = ctime(&(buf_ptr->st_mtime));  //将st_mtime转为标准日历时间字符串
    char file_time[512] = {0};
    strncpy(file_time, time, strlen(time) - 1);
    printf("%.12s ", 4 + file_time); // 不用星期，星期占前4地址, .12 为截取日期长度为12

    // 第九列
    // 文件名
    printf("%s\n", file_name);
}

// 排序
void sort(char **filenames, int start, int end)
{
    if (start < end){
        int position = partition(filenames, start, end);
        sort(filenames, start, position - 1);
        sort(filenames, position + 1, end);
    }
}

// 比较两字符串的字典序
int compare(char *s1, char *s2)
{
    if (*s1 == '.')
        s1++;
    if (*s2 == '.')
        s2++;

    while (*s1 && *s2 && *s1 == *s2)
    {
        ++s1;
        ++s2;
        if (*s1 == '.')
            s1++;
        if (*s2 == '.')
            s2++;
    }
    return *s1 - *s2; // s1靠前，返回负数，s1靠后，返回正数；s1和s2完全一样，返回0
}

// 交换两字符串
void swap(char **s1, char **s2)
{
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

int partition(char **filenames, int start, int end)
{
    char *privot = filenames[start];
    while (start < end)
    {
        while (start < end && compare(privot, filenames[end]) < 0)
            --end;
        swap(&filenames[start], &filenames[end]);
        while (start < end && compare(privot, filenames[start]) >= 0)
            ++start;
        swap(&filenames[start], &filenames[end]);
    }
    return start;
}