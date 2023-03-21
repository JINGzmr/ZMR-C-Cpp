#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 20
#define MAX_COMMAND_LENGTH 100

int num_commands = 0;                   // 命令数量
char *commands[MAX_COMMANDS][MAX_ARGS]; // 命令列表
int input_redirect = 0;                 // 输入重定向标志
int output_redirect = 0;                // 输出重定向标志
int background = 0;                     // 后台运行标志
char *input_file = NULL;                // 输入文件名
char *output_file = NULL;               // 输出文件名

// 读取命令行输入
void read_line(char *line)
{
    printf("shell> ");
    fgets(line, MAX_COMMAND_LENGTH, stdin);
    line[strlen(line) - 1] = '\0'; // 去掉换行符
}

// 解析命令行参数
void parse_args(char *line)
{
    char *token;
    char *rest = line;
    while ((token = strtok_r(rest, " ", &rest)))
    {
        if (strcmp(token, "<") == 0)
        { // 输入重定向
            input_redirect = 1;
            input_file = strtok_r(NULL, " ", &rest);
        }
        else if (strcmp(token, ">") == 0)
        { // 输出重定向
            output_redirect = 1;
            output_file = strtok_r(NULL, " ", &rest);
        }
        else if (strcmp(token, "&") == 0)
        { // 后台运行
            background = 1;
        }
        else
        { // 其他命令
            commands[num_commands][0] = token;
            int i = 1;
            while ((token = strtok_r(NULL, " ", &rest)))
            {
                if (strcmp(token, "<") == 0)
                { // 输入重定向
                    input_redirect = 1;
                    input_file = strtok_r(NULL, " ", &rest);
                }
                else if (strcmp(token, ">") == 0)
                { // 输出重定向
                    output_redirect = 1;
                    output_file = strtok_r(NULL, " ", &rest);
                }
                else if (strcmp(token, "&") == 0)
                { // 后台运行
                    background = 1;
                }
                else
                {
                    commands[num_commands][i++] = token;
                }
            }
            commands[num_commands][i] = NULL;
            num_commands++;
        }
    }
}

// 执行命令
void execute_command()
{
    if (num_commands == 0)
        return;

    // 设置信号屏蔽
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    pid_t pid;
    int fd[2];               // 管道文件描述符
    int input_fd, output_fd; // 输入输出文件描述符

    // 处理管道
    for (int i = 0; i < num_commands; i++)
    {
        if (i < num_commands - 1)
        { // 还有下一个命令，需要创建管道
            pipe(fd);
        }

        pid = fork();

        if (pid < 0)
        { // fork 出错
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        { // 子进程
            if (i > 0)
            { // 不是第一个命令，需要从管道中读取输入
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            else if (input_redirect)
            { // 有输入重定向，需要从文件中读取输入
                input_fd = open(input_file, O_RDONLY);
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            if (i < num_commands - 1)
            { // 不是最后一个命令，需要将输出写入管道
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            else if (output_redirect)
            { // 有输出重定向，需要将输出写入文件
                output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }

            // 运行命令
            execvp(commands[i][0], commands[i]);

            // 如果执行到这里，说明 execvp 失败了
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else
        { // 父进程
            if (i > 0)
            { // 不是第一个命令，需要关闭管道的读端
                close(fd[0]);
                close(fd[1]);
            }
        }
    }

    // 恢复信号屏蔽
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    // 等待子进程运行完毕
    if (!background)
    {
        for (int i = 0; i < num_commands; i++)
        {
            wait(NULL);
        }
    }

    // 重置变量
    num_commands = 0;
    input_redirect = 0;
    output_redirect = 0;
    background = 0;
    input_file = NULL;
    output_file = NULL;
}

// 处理信号
void handle_signal(int signum)
{
    printf("\n");
    execute_command(); // 重新读取命令并执行
}

// 主函数
int main()
{
    char line[MAX_COMMAND_LENGTH];
    signal(SIGINT, handle_signal); // 注册信号处理函数

    while (1)
    {
        read_line(line);
        parse_args(line);
        execute_command();
    }

    return 0;
}