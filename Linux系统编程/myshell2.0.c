#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024 // 最大命令长度
#define MAX_ARGS 64             // 最大参数数量
#define MAX_COMMANDS 16         // 最大命令数量
#define MAX_PATH_LENGTH 1024    // 最大路径长度
#define DELIMS " \t\n"          // strsep要的分割符，包括空格

char *argv[MAX_ARGS] = {NULL};
char commands[MAX_COMMANDS][MAX_ARGS]; // 命令数组
int argc = 0;
int num_commands = 0;       // 命令数量
char path[MAX_PATH_LENGTH]; // 当前工作路径

void parse_command(char *cmd); // 分割命令
void do_cmd(char *cmd);        // 分析命令
void command_with_Pipe(char *buf);
void command_with_OutRe(char *buf);
void command_with_InRe(char *buf);
void command_with_OutRePlus(char *buf);

int main()
{
    // while (1)
    {
        getcwd(path, MAX_PATH_LENGTH);
        char cmd[MAX_COMMAND_LENGTH]; // 存一整行命令
        fgets(cmd, MAX_COMMAND_LENGTH, stdin);
        parse_command(cmd);
        do_cmd(cmd);
    }
}

void parse_command(char *cmd)
{
    const char *sep = " "; // 分割表示符，将每个指令分割出来
    argv[0] = strtok(cmd, sep);
    int i = 1;
    while (argv[i] = strtok(NULL, sep))
    {
        i++;
    }
    argc = i; // 命令数
    argv[argc] = NULL; //argv[argc-1]存最后一个命令
}

// void do_cmd(char *cmd)
// {
//     char buf[1024]; // 存放原始命令
// /// 识别管道命令
// for (int i = 0; i < MAX_PATH_LENGTH; i++)
// {
//     if (cmd[i] == '|')
//     {
//         strcpy(buf, cmd);
//         command_with_Pipe(buf);
//         return;
//     }
// }
// 识别输出重定向
// for (int j = 0; j < argc; j++)
// {
//     if (strcmp(argv[j], ">") == 0)
//     {
//         strcpy(buf, cmd);
//         command_with_OutRe(buf);
//         return;
//     }
// }
// // 识别输入重定向
// for (int j = 0; j < MAX_COMMAND_LENGTH; j++)
// {
//     if (strcmp(commands[j], "<") == 0)
//     {
//         strcpy(buf, cmd);
//         command_with_InRe(buf);
//         return;
//     }
// }
// // 识别追加写重定向
// for (int j = 0; j < MAX_COMMAND_LENGTH; j++)
// {
//     if (strcmp(commands[j], ">>") == 0)
//     {
//         strcpy(buf, cmd);
//         command_with_OutRePlus(buf);
//         return;
//     }
// }
// // 识别后台运行命令
// for (int j = 0; j < MAX_COMMAND_LENGTH; j++)
// {
//     if (strcmp(commands[j], "&") == 0)
//     {
//         strcpy(buf, cmd);
//         command_with_Back(buf);
//         return;
//     }
// }
// }

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
