#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h> //errno的头文件
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include <time.h>

void myls(const char* dirpath_name);
void mystat(const char* file_name);
void print_file_information(const char* file_name, struct stat *buf_ptr);

int main(int argc,char* argv[])
{
    if(argc == 1){
        myls(".");
    }
    else{
        while(--argc){
            myls(*(++argv));
        }
    }
    return 0;
}

//打开、读取、关闭目录
void myls(const char* dirpath_name)
{
    DIR* cur_dir = NULL;
    struct dirent* cur_item = NULL;
    //开目录
    cur_dir = opendir(dirpath_name);
    if(cur_dir == NULL){
        printf("目录打开错误!\n");
    }
    else{
        //读目录
        while(1){
            errno = 0;
            cur_item = readdir(cur_dir);
            if(errno != 0)printf("文件读取错误!\n");
            if(cur_item == NULL)break;
            if(strcmp(cur_item -> d_name,".") == 0 || strcmp(cur_item -> d_name,"..") == 0)continue;
            mystat(cur_item -> d_name);

        }
        printf("\n");
        //关目录
        closedir(cur_item);
    }
}

//获取文件具体信息
void mystat(const char* file_name)
{
    struct stat buf;
    if(stat(file_name, &buf) == -1)printf("获取文件信息错误!\n");
    else{
        print_file_information(file_name,&buf);//注意是&buf
    }
}

//打印文件具体信息
void print_file_information(const char* file_name, struct stat *buf_ptr)
{
    //第一列
    char first_column[11] = {0};
    //第一个字母
    if ( S_ISLNK(buf_ptr ->st_mode) ) {
		first_column[0] = 'l';
	}
	else if ( S_ISDIR(buf_ptr ->st_mode) ) {
		first_column[0] = 'd';
	}
	else if ( S_ISCHR(buf_ptr ->st_mode) ) {
		first_column[0] = 'c';
	}
	else if ( S_ISSOCK(buf_ptr ->st_mode) ) {
		first_column[0] = 's';
	}
	else if ( S_ISFIFO(buf_ptr ->st_mode) ) {
		first_column[0] = 'p';
	}
	else if ( S_ISBLK(buf_ptr ->st_mode) ) {
		first_column[0] = 'b';
	}
	else {
		first_column[0] = '-';
	}

    //后面三个为一组
    //r表示读权限,w表示写权限,x表示可执行权限,-表示无权限
    //第一组为表示所有者权限
    first_column[1] = (buf_ptr ->st_mode & S_IRUSR) ? 'r' : '-';
    first_column[2] = (buf_ptr ->st_mode & S_IWUSR) ? 'w' : '-';
    first_column[3] = (buf_ptr ->st_mode & S_IXUSR) ? 'x' : '-';

    //第二组为表示组用户权限
    first_column[4] = (buf_ptr ->st_mode & S_IRGRP) ? 'r' : '-';
    first_column[5] = (buf_ptr ->st_mode & S_IWGRP) ? 'w' : '-';
    first_column[6] = (buf_ptr ->st_mode & S_IXGRP) ? 'x' : '-';

    //第三组为表示其他用户组的权限
    first_column[7] = (buf_ptr ->st_mode & S_IROTH) ? 'r' : '-';
    first_column[8] = (buf_ptr ->st_mode & S_IWOTH) ? 'w' : '-';
    first_column[9] = (buf_ptr ->st_mode & S_IXOTH) ? 'x' : '-';

    printf("%s ",first_column);

    //第二列
    //目录：表示当前这个目录下面的一级目录个数
    //文件：表示硬链接个数
    printf("%d ",(int)buf_ptr -> st_nlink);

    //第三列
    //该文件或目录的所有者
    struct passwd *getpwuid();
    struct passwd *pwuid_ptr;
    static char numstr[10];
    if((pwuid_ptr = getpwuid(buf_ptr ->st_uid)) == NULL){
        sprintf(numstr, "%d", buf_ptr ->st_uid);
        printf("%s ",numstr);
    }
    else{
        printf("%-8s ",pwuid_ptr -> pw_name);//-8向左对齐
    }

    //第四列
    //表示所属的组
    struct group *getgrgid();
    struct group *group_ptr;
    static char num[10];
    if((group_ptr = getgrgid(buf_ptr ->st_gid)) == NULL){
        sprintf(num, "%d", buf_ptr ->st_gid);
        printf("%s ",num);
    }else{
        printf("%-8s ",group_ptr -> gr_name);//-8向左对齐
    }

    //第五列
    //文件大小
    printf("%8ld ",(long)buf_ptr -> st_size);//8ld向右对齐

    //第六、七、八列
    //月、日、时
    char *time = ctime(&(buf_ptr -> st_mtime));
    char file_time[512] = {0};
    strncpy(file_time, time, strlen(time) - 1);
    printf("%s ",4+file_time);//不用星期，星期占前4地址

    //第九列
    //文件名
    printf("%s\n",file_name);

}