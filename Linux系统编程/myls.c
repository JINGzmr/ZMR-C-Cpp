#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h> //errno的头文件
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
// 存放文件名的数组，方便a-z排序
char *filenames[4096];
// 目录中文件个数，用来计数
int file_cnt = 0;
#define a 0
#define l 1
#define R 2
#define t 3
#define r 4
#define i 5
#define s 6
//-a -l -i -s
//-a、-l、-R、-t、-r、-i、-s

void myls(int has[], const char *dirpath_name);                    // 打开、读取、关闭目录
void mystat(const char *file_name);                                 // 获取文件具体信息
void print_file_information(char *file_name, struct stat *buf_ptr); // 打印文件具体信息
long long int total(struct stat *buf_ptr);
void myls_i(struct stat *buf_ptr);
void myls_s(struct stat *buf_ptr);
// void myls_R(char path[]);
void restored_ls(struct dirent *cur_item); // 将目录中的文件依次存入数组中,便于后续排序及逆向输出

// 按a-z排序
void sort(char **filenames, int start, int end);
int compare(char *s1, char *s2);
void swap(char **s1, char **s2);
int partition(char **filenames, int start, int end);

int main(int argc, char *argv[])
{
    /*
        if(argc == 1){
            myls(".");
        }
        else{
            while(--argc){
                myls(*(++argv));
            }
        }
        return 0;
        char param[100];
        int cnt = 0; // 命令个数
        int num = 0;
        对命令行参数进行解析，提取到param数组中
        for (n = 1; n < argc; n++)
        {
            if (argv[n][0] == '-')
            {
                for (int j = 1; j < strlen(argv[i]); cnt++, j++)
                {
                    param[cnt] = argv[i][j]; // 获取-后面的参数保存到数组param中
                }
                num++; // 保存 - 的个数
            }
        }

        for (n = 0; n < cnt; n++)
        {
            if (param[n] == 'a')has[a]=1;
            else if (param[n] == 'l')has[l]=1;
            else if (param[n] == 'R')has[R]=1;
            else if (param[n] == 't')has[t]=1;
            else if (param[n] == 'r')has[r]=1;
            else if (param[n] == 'i')has[i]=1;
            else if (param[n] == 's')has[s]=1;
        }
        printf("%d",num);
        printf("%d",argc);
        printf("%s",argv[2]);
        char c = '-';
        if (argc - num >= 2)
        {
            if (strncmp(argv[1], c, 1) == 0)
                myls(argv[argc - 1]);
        dir = argv[argc-1];
        printf("%s", argv[argc-1]);
        else
            myls(argv[1]);
        printf("%s", argv[1]);
        dir = argv[1];
        }
        else
        {
            myls(".");
        }
        printf("%s", dir);
    */

    char ch;
    int has[8] = {0};
    int num = 0; // 记录-l/-lai的数目，若小于argc-1(即相差大于等于2时），则有可能是指定目录
    // char *dir;   // 存指定目录
    // dir = (char *)malloc(sizeof(char));
    char path[256]; // 存储路径
    while ((ch = getopt(argc, argv, "alRtris")) != -1)
    {
        switch (ch)
        {
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

    // 如果没有输入路径，就设置为当前路径
    if (argc==1||*argv[argc-1]=='-')
    {
        myls(has, ".");
        return 0;
    }

    int n = 1;
    do
    {
        // 如果不是目标文件名或目录，解析下一个命令行参数(/桌面/练习代码/Linux系统编程就是目标文件名或目录，而非在当前目录下)
        if (argv[n][0] == '-') // 跳过-s-l
        {
            n++;
            continue;
        }
        else
        {
            struct stat buf;
            strcpy(path, argv[n]); // path存储目标文件名或目录（路径）

            // 如果目标文件或目录不存在，报错并退出程序
            if (stat(path, &buf) == -1)
                perror("stat fail:");
            // 判断该路径是不是目录
            if (S_ISDIR(buf.st_mode)) // S_ISDIR判断路径目录函数
            {
                // 是目录但是没带 '/'就加上'/'
                if (path[strlen(argv[n]) - 1] != '/')
                {
                    path[strlen(argv[n])] = '/';
                    path[strlen(argv[n]) + 1] = '\0';
                }

                if (has[R])
                {
                    // ls_R(char path[]);
                }
                else                 // 不用递归出目录下的子目录，打印当前目录即可
                    myls(has, path); //// 进入‘打开、读取、关闭目录’流程

                n++;
            }
            else // argv[i]是一个文件
            {
                myls(has, path);
                n++;
            }
        }
    } while (n < argc);
    return 0;
}

// 打开、读取、关闭目录
void myls(int has[], const char *dirpath_name)
{
    DIR *cur_dir = NULL;
    struct dirent *cur_item = NULL;
    // 开目录
    cur_dir = opendir(dirpath_name);
    if (cur_dir == NULL)
    {
        printf("目录打开错误!\n");
    }
    else
    {
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
            if ((cur_item->d_name[0] == '.' || cur_item->d_name[0] == '..') && has[a] == 0)
                continue; // 在有-a参数时就不能跳过了

            restored_ls(cur_item);
        }
        sort(filenames, 0, file_cnt - 1);

        // if()//有什么参数，就。。。
        {
            int n;
            for (n = 0; n < file_cnt; n++)
                mystat(filenames[n]);
        }
        printf("\n");
        // 关目录
        closedir(cur_item);
    }
}

// 将目录中的文件依次存入数组中
void restored_ls(struct dirent *cur_item)
{
    filenames[file_cnt++] = cur_item->d_name;
}

// 获取文件具体信息
void mystat(const char *file_name)
{
    struct stat buf;
    if (stat(file_name, &buf) == -1)
        printf("获取文件信息错误!\n");
    else
    {
        if (1)
        { // 如果有-i参数，则执行
            myls_i(&buf);
        }
        if (1)
        { // 如果有-s参数，则执行
            myls_s(&buf);
        }
        print_file_information(file_name, &buf); // 注意是&buf
    }
}

void myls_i(struct stat *buf_ptr)
{
    printf("%d ", buf_ptr->st_ino);
}

// 在文件左侧显示文件大小（在-l左边，-i右边），以1024字节为块单位
// ls -s
void myls_s(struct stat *buf_ptr)
{
    long long int size1 = buf_ptr->st_size;
    long long int size2 = size1 / 1024;
    while (size2 % 4 != 0)
    {
        size2++;
    }
    printf("%5lld ", size2);
}

// 总用量
long long int total(struct stat *buf_ptr)
{
    long long int totall = 0;
    int n;
    for (n = 0; n < file_cnt; n++)
    {
        long long int size1 = buf_ptr->st_size;
        long long int size2 = size1 / 1024;
        while (size2 % 4 != 0)
        {
            size2++;
        }
        totall += size2;
    }
    printf("总用量：%lld", totall);
}

// //递归调用
// //ls -R
// void mydls_R(char path[])
// {
//   printf("%s:\n",path);
//   DIR* dir_ptr;
//   struct dirent* direntp;
//   if((dir_ptr=opendir(path)) != NULL)//打开目录
//   {
//     while((direntp=readdir(dir_ptr)) != NULL)//读取当前目录文件
//     {
//       restored_ls(direntp);
//     }
//        sort(filenames,0,file_cnt-1);
//     int j=0;
//     int i=0;
//     for(j=0;j<file_cnt;++j)
//     {
//       if(has_aRl==1||has_Rl==1)
//       {
//           char temp1[PATH_MAX];
//          sprintf(temp1,"%s/%s",path,filenames[j]);
//          dostat(temp1,filenames[j]);
//         continue;
//       }
//       if(filenames[j][0]=='.'&&(has_aR!=1&&has_aRl!=1))
//         continue;
//       struct stat info;
//       char temp1[PATH_MAX];
//       sprintf(temp1,"%s/%s",path,filenames[j]);
//       if(lstat(temp1,&info)==-1)
//         perror(temp1);
//       int color=get_color(info);
//          if(has_s==1)
//           {
//              long long size=info.st_size/1024;
//                if(size<=4)
//                   printf("4   ");
//                else
//                   printf("%-4lld",size);
//            }
//       printf_name2(filenames[j],color);
//     }
//   }
//   printf("\n");
//   printf("\n");
//   file_cnt=0;
//   closedir(dir_ptr);
//   if((dir_ptr=opendir(path))==NULL)//打开目录
//     fprintf(stderr,"lsl:cannot open %s\n",path);
//   else
//   {
//     while((direntp=readdir(dir_ptr))!=NULL)
//     {
//       if(strcmp(direntp->d_name,".")==0||strcmp(direntp->d_name,"..")==0)
//         continue;
//       if(has_R==1)
//       {
//         if(direntp->d_name[0]=='.')
//           continue;
//       }
//       struct stat info;
//       char temp[PATH_MAX];
//       sprintf(temp,"%s/%s",path,direntp->d_name);
//       if(lstat(temp,&info)==-1)
//         perror(temp);
//       if(S_ISDIR(info.st_mode))//判断是否为目录，如果是目录就进入递归
//       {
//         ls_R(temp);
//       }

//     }
//   }
// }

// 打印文件具体信息
void print_file_information(char *file_name, struct stat *buf_ptr)
{
    // 第一列
    char first_column[11] = {0};
    // 第一个字母
    if (S_ISLNK(buf_ptr->st_mode))
    {
        first_column[0] = 'l';
    }
    else if (S_ISDIR(buf_ptr->st_mode))
    {
        first_column[0] = 'd';
    }
    else if (S_ISCHR(buf_ptr->st_mode))
    {
        first_column[0] = 'c';
    }
    else if (S_ISSOCK(buf_ptr->st_mode))
    {
        first_column[0] = 's';
    }
    else if (S_ISFIFO(buf_ptr->st_mode))
    {
        first_column[0] = 'p';
    }
    else if (S_ISBLK(buf_ptr->st_mode))
    {
        first_column[0] = 'b';
    }
    else
    {
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
    printf("%d ", (int)buf_ptr->st_nlink);

    // 第三列
    // 该文件或目录的所有者
    struct passwd *getpwuid();
    struct passwd *pwuid_ptr;
    static char numstr[10];
    if ((pwuid_ptr = getpwuid(buf_ptr->st_uid)) == NULL)
    {
        sprintf(numstr, "%d", buf_ptr->st_uid);
        printf("%s ", numstr);
    }
    else
    {
        printf("%-8s ", pwuid_ptr->pw_name); //-8向左对齐
    }

    // 第四列
    // 表示所属的组
    struct group *getgrgid();
    struct group *group_ptr;
    static char num[10];
    if ((group_ptr = getgrgid(buf_ptr->st_gid)) == NULL)
    {
        sprintf(num, "%d", buf_ptr->st_gid);
        printf("%s ", num);
    }
    else
    {
        printf("%-8s ", group_ptr->gr_name); //-8向左对齐
    }

    // 第五列
    // 文件大小
    printf("%8ld ", (long)buf_ptr->st_size); // 8ld向右对齐

    // 第六、七、八列
    // 月、日、时
    char *time = ctime(&(buf_ptr->st_mtime));
    char file_time[512] = {0};
    strncpy(file_time, time, strlen(time) - 1);
    printf("%12.12s ", 4 + file_time); // 不用星期，星期占前4地址,12.12为截取日期长度为12

    // 第九列
    // 文件名
    printf("%s\n", file_name);
}

// 排序
void sort(char **filenames, int start, int end)
{
    if (start < end)
    {
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
