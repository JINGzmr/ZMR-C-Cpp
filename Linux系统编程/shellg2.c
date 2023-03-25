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

char *args[MAX_ARGS];                   // 命令参数数组
char *commands[MAX_COMMANDS][MAX_ARGS]; // 命令数组
int num_commands = 0;                   // 命令数量
char path[MAX_PATH_LENGTH];             // 当前工作路径
int is_background = 0;                  // 是否后台运行
int in_redirect = 0;                    // 是否进行输入重定向
int out_redirect = 0;                   // 是否进行输出重定向
char in_filename[MAX_COMMAND_LENGTH];   // 输入重定向的文件名
char out_filename[MAX_COMMAND_LENGTH];  // 输出重定向的文件名
sigset_t mask;                          // 信号屏蔽集合

void parse_command(char *command); // 解析命令
void execute_command();            // 执行命令
void handle_signal(int signum);    // 信号处理函数

int main()
{
    // 初始化信号屏蔽集合
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    // // 注册信号处理函数
    // signal(SIGINT, handle_signal);
    // signal(SIGTERM, handle_signal);
    // signal(SIGQUIT, handle_signal);

    // 启动 Shell 循环
    while (1)
    {
        // 打印提示符和当前路径
        printf("myshell_zmr:%s$ ", getcwd(path, MAX_PATH_LENGTH));
        fflush(stdout);

        // 读取命令行输入
        char command[MAX_COMMAND_LENGTH];          // 存读入的命令字符串
        fgets(command, MAX_COMMAND_LENGTH, stdin); // 使用 fgets 函数从标准输入流中读取用户输入的字符串，并将其保存到 command 字符数组中

        // 去掉结尾的换行符
        command[strlen(command) - 1] = '\0';

        // 解析命令并执行
        parse_command(command);
        execute_command();
    }

    return 0;
}

void parse_command(char *command)
{
    // 初始化命令参数数组
    memset(args, 0, sizeof(args)); // 将 args 数组中的所有元素都设置为 NULL（空指针）
                                   // 并不等同于将数组中的字符串都置为了空字符串（即长度为 0 的字符串）
    /*要将字符串都置为空字符串，可以使用一个循环来遍历数组，对每个元素进行赋值操作：
    for (int i = 0; i < MAX_ARGS; i++)
    {
        args[i] = "";
    }*/

    // 初始化命令数组
    memset(commands, 0, sizeof(commands));
    num_commands = 0;

    // 初始化重定向和后台运行标志
    in_redirect = 0;
    out_redirect = 0;
    is_background = 0;

    // 分割命令行输入为命令和参数
    char *token = strtok(command, " ");
    while (token != NULL)
    {
        // 处理管道符号
        if (strcmp(token, "|") == 0)
        {
            // 将管道符号替换为 NULL，表示命令结束
            commands[num_commands][0] = NULL;
            num_commands++;
        }
        // 处理输入重定向符号
        else if (strcmp(token, "<") == 0)
        {
            in_redirect = 1;
        }
        // 处理输出重定向符号
        else if (strcmp(token, ">") == 0)
        {
            out_redirect = 1;
        }
        // 处理后台运行符号
        else if (strcmp(token, "&") == 0)
        {
            is_background = 1;
        }
        // 处理普通命令参数
        else
        {
            // 添加参数到参数数组
            args[0] = token;
            int num_args = 1;
            while (1)
            {
                token = strtok(NULL, " ");
                if (token == NULL || strcmp(token, "|") == 0 || strcmp(token, "<") == 0 || strcmp(token, ">") == 0 || strcmp(token, "&") == 0)
                {
                    // 将参数数组末尾设置为 NULL，表示参数结束
                    args[num_args] = NULL;
                    break;
                }
                args[num_args] = token;
                num_args++;
            }
            // 复制参数数组到命令数组->参数数组存ls\-l（是散的），命令数组存“ls -l”（是整体的）
            for (int i = 0; i < num_args; i++)
            {
                commands[num_commands][i] = args[i];
            }
            num_commands++;
        }

        // 继续解析下一个命令或参数
        token = strtok(NULL, " ");//在后续调用时，不需要再传入待处理的字符串，而是传入NULL。函数会继续从上一次调用的位置开始处理，返回下一个子字符串的指针，直到所有的子字符串都被处理完毕。
    }

    // 将命令数组末尾设置为 NULL，表示命令结束
    commands[num_commands][0] = NULL;
}

void execute_command()
{
    // 如果命令为空，则不执行
    if (num_commands == 0)
    {
        return;
    }

// printf("%s1\n",commands[0][1]);
    // 执行 cd 命令
    if (strcmp(commands[0][0], "cd") == 0)
    {
        // 处理 cd - 命令，切换到上一个工作路径
        if (commands[0][1] != NULL && strcmp(commands[0][1], "-") == 0)
        {
        // char prev_path[MAX_PATH_LENGTH]; // 不懂有什么用，prev_path和path存的都是当前路径
        // strcpy(prev_path, path);         // getenv()函数是一个C标准库中的函数，用于获取环境变量列表中相应变量的值
        chdir(getenv("OLDPWD"));         // 将当前工作目录更改为之前的工作目录。使用了getenv()获取OLDPWD的值，然后将其作为参数传递给chdir()
        // strcpy(path, prev_path);         // “OLDPWD”，它是一个Shell内置环境变量，表示之前的工作目录
        getcwd(path,MAX_PATH_LENGTH);
        printf("%s\n",path);                                         //“OLDPWD”，它是一个Shell内置环境变量，表示之前的工作目录
        }
         // 处理 cd 命令没有参数或cd ~ 的情况，切换到用户主目录
        else if((commands[0][1] != NULL && strcmp(commands[0][1],"~") == 0 ) || commands[0][1] == NULL)
        {
            char prev_path[MAX_PATH_LENGTH];
            strcpy(prev_path, path);
            chdir(getenv("HOME"));
            strcpy(path, prev_path);
        }
        // 处理普通 cd 命令，切换到指定路径
        else
        {
            char prev_path[MAX_PATH_LENGTH];
            strcpy(prev_path, path);
            chdir(commands[0][1]);
            strcpy(path, prev_path);
        }
       
        return;
    }

    // 创建子进程执行命令
    pid_t pid = fork();
    if (pid == 0)
    {
        // 子进程
        // 处理输入重定向
        if (in_redirect)
        {
            int fd = open(in_filename, O_RDONLY);
            if (fd == -1)
            {
                printf("myshell: %s: %s\n", in_filename, strerror(errno));
                exit(1);
            }
            if (dup2(fd, 0) == -1)
            {
                printf("myshell: %s\n", strerror(errno));
                exit(1);
            }
            close(fd);
        }
        // 处理输出重定向
        if (out_redirect)
        {
            int fd = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1)
            {
                printf("myshell: %s: %s\n", out_filename, strerror(errno));
                exit(1);
            }
            if (dup2(fd, 1) == -1)
            {
                printf("myshell: %s\n", strerror(errno));
                exit(1);
            }
            close(fd);
        }
        // 执行命令
        if (execvp(commands[0][0], commands[0]) == -1)
        {
            printf("myshell: %s: %s\n", commands[0][0], strerror(errno));
            exit(1);
        }
    }
    else if (pid == -1)
    {
        // 创建子进程失败
        printf("myshell: %s\n", strerror(errno));
    }
    else
    {
        // 父进程
        // 等待子进程结束
        waitpid(pid, NULL, 0);
    }
}
