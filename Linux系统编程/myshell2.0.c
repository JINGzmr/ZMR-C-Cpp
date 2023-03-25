#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wait.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 1024 // 最大命令长度
#define MAX_ARGS 64             // 最大参数数量
#define MAX_COMMANDS 16         // 最大命令数量
#define MAX_PATH_LENGTH 1024    // 最大路径长度
#define DELIMS " \t\n"          // strsep要的分割符，包括空格

int has[10]={0};
#define cd_ 0
#define echo_ 1
#define exit_ 2
#define output 3
#define append_output 4
#define input 5
#define Background_running 6
#define pipeline 7
#define ls_ 8


char *argv[MAX_ARGS] = {NULL}; // 放 ls / -a / -t / > / 1.txt
int argc = 0;

char commands[MAX_COMMANDS][MAX_ARGS]; // 命令数组
int num_commands = 0;                  // 命令数量
char path[MAX_PATH_LENGTH];            // 当前工作路径

void prompt(void);                          // 打印提示符 zmr-super-shell:路径$ 
void Split_command(char *cmd);              // 分割命令 strtok()
void parse_command(char *argv[], int argc); // 解析命令 根据有的东东(><>>|cd&)来调用相应的函数

void command_with_Pipe(char *buf);
void command_with_OutRe(char *buf);
void command_with_InRe(char *buf);
void command_with_OutRePlus(char *buf);

int main()
{
    // while (1)
    {
        prompt(); // 打印提示符$
        getcwd(path, MAX_PATH_LENGTH);
        char cmd[MAX_COMMAND_LENGTH]; // 存一整行命令
        fgets(cmd, MAX_COMMAND_LENGTH, stdin);
        Split_command(cmd);
        parse_command(argv, argc);
    }
}

void prompt(void)
{
    // 打印提示符和当前路径
    printf("zmr-super-shell:%s$ ", getcwd(path, MAX_PATH_LENGTH));
    flush(stdout); // 清空标准输出缓冲区，确保之前的输出内容被立即写入到输出设备中，如果不清空缓冲区，可能会导致输出的内容不及时或不完整
}

void Split_command(char *cmd)
{
    const char *sep = " "; // 分割表示符，将每个指令分割出来
    argv[0] = strtok(cmd, sep);
    int i = 1;
    while (argv[i] = strtok(NULL, sep))
    {
        i++;
    }
    argc = i;          // 命令数
    argv[argc] = NULL; // argv[argc-1]存最后一个命令
}

void parse_command(char *argv[], int argc)
{
    
    
}

// void command_with_OutRe(char *buf)
// {
//     char outfile_name[1024]; // >后面的文件名
//     memset(outfile_name, 0, MAX_PATH_LENGTH);

//     int i;
//     char *argv1[MAX_ARGS];
//     for (i = 0; i < argc; i++)
//     {
//         argv1[i] = argv[i];
//         if (strcmp(argv[i], ">") == 0)
//         {
//             strcpy(outfile_name, argv[i + 1]);
//             argv1[i] = '\0';
//             break;
//         }
//     }

//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         int fd = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 0666); // 0666：设置文件权限为用户、组和其他用户均可读写，其中 0 表示八进制数，6 表示用户可读写，6 表示组可读写，6 表示其他用户可读写。
//         dup2(fd,STDOUT_FILENO);
//         execvp(argv[0],argv);
//     }
//     else if (pid > 0)
//     {
//         int status;
//         waitpid(pid, &status, 0);
//     }else{
//         perror("fork()");
//         exit(1);
//     }
// }
