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
#define MAX 128                 // 最大文件名
#define SEP " \t\n"             // strsep要的分割符，包括空格 (一定要有\n，否则输入 cd - 的话，argv[1]=-\n，即最后一个参数一定会有带在终端输入的换行符\n,会影响cd等函数)

int has[10] = {0};
#define cd_ 0
#define echo_ 1
#define exit_ 2
#define output 3             // >
#define append_output 4      // >>
#define input 5              // <
#define Background_running 6 // &
#define pipeline 7           // |
#define ls_ 8

char *argv[MAX_ARGS] = {NULL}; // 放 ls / -a / -t / > / 1.txt
int argc = 0;

char commands[MAX_COMMANDS][MAX_ARGS]; // 命令数组
int num_commands = 0;                  // 命令数量
char path[MAX_PATH_LENGTH];            // 当前工作路径

void prompt(void);                          // 打印提示符 zmr-super-shell:路径$
void Split_command(char *cmd);              // 分割命令 strtok()
void has_(char *cmd);                       // 看看有啥命令参数
void parse_command(char *argv[], int argc); // 解析命令 根据有的东东(><>>|cd&)来调用相应的函数

void mycd(char *argv[]); // 只输入cd报段错误
void myOutRe(char *argv[]);
void myOutRePlus(char *argv[]);
void myInRe(char *argv[]);
void myPipe(char *argv[]);
void myls(char *argv[]);

int main()
{
    while (1)
    {
        memset(has, 0, sizeof(has_));
        prompt(); // 打印提示符$
        getcwd(path, MAX_PATH_LENGTH);
        char cmd[MAX_COMMAND_LENGTH]; // 存一整行命令
        fgets(cmd, MAX_COMMAND_LENGTH, stdin);
        Split_command(cmd);
        has_(cmd);
        parse_command(argv, argc);
    }
}

void prompt(void)
{
    // 打印提示符和当前路径
    printf("zmr-super-shell:%s$ ", getcwd(path, MAX_PATH_LENGTH));
    fflush(stdout); // 清空标准输出缓冲区，确保之前的输出内容被立即写入到输出设备中，如果不清空缓冲区，可能会导致输出的内容不及时或不完整
}

void Split_command(char *cmd)
{
    // const char *sep = " "; // 分割表示符，将每个指令分割出来
    argv[0] = strtok(cmd, SEP);
    int i = 1;
    while (argv[i] = strtok(NULL, SEP))
    {
        i++;
    }
    argc = i;          // 命令数
    argv[argc] = NULL; // argv[argc-1]存最后一个命令

    // printf("%s",argv[1]);
}

void has_(char *cmd)
{
    if (argv[0] == NULL)
    {
        return;
    }

    // 内部命令
    if (strcmp(argv[0], "cd") == 0)
    {
        has[cd_]++;
    }
    else if (strcmp(argv[0], "echo") == 0)
    {
        has[echo_]++;
    }
    else if (strcmp(argv[0], "exit") == 0)
    {
        has[exit_]++;
    }

    // 外部命令
    int i;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], ">") == 0)
        {
            has[output]++;
        }
        if (strcmp(argv[i], ">>") == 0)
        {
            has[append_output]++;
        }
        if (strcmp(argv[i], "<") == 0)
        {
            has[input]++;
        }
        if (strcmp(argv[i], "&") == 0)
        {
            has[Background_running]++;
        }
        if (strcmp(argv[i], "&") == 0)
        {
            has[pipeline]++;
        }
        if (strcmp(argv[i], "ls") == 0)
        {
            has[ls_]++;
        }
    }
}

void parse_command(char *argv[], int argc)
{
    // 内部
    if (has[cd_])
    {
        mycd(argv);
    }
    if (has[echo_])
    {
        // 暂无
    }
    if (has[exit_])
    {
        exit(0);
    }

    // 外部
    if (has[output])
    {
        myOutRe(argv);
    }
    if (has[append_output])
    {
        myOutRePlus(argv);
    }
    if (has[input])
    {
        myInRe(argv);
    }
    // if (has[pipeline])
    // {
    //     myPipe(argv);
    // }
    if (has[ls_])
    {
        myInRe(argv);
    }
}

void mycd(char *argv[])
{
    // 处理 cd - 命令，切换到上一个工作路径
    if (strcmp(argv[1], "-") == 0)
    {
        // char prev_path[MAX_PATH_LENGTH]; // 不懂有什么用，prev_path和path存的都是当前路径
        // strcpy(prev_path, path);         // getenv()函数是一个C标准库中的函数，用于获取环境变量列表中相应变量的值
        chdir(getenv("OLDPWD")); // 将当前工作目录更改为之前的工作目录。使用了getenv()获取OLDPWD的值，然后将其作为参数传递给chdir()
        // strcpy(path, prev_path);         // “OLDPWD”，它是一个Shell内置环境变量，表示之前的工作目录
        getcwd(path, MAX_PATH_LENGTH);
        printf("%s\n", path); // 要先把切换后的路径打印一下
    }
    // 处理 cd 命令没有参数或cd ~ 的情况，切换到用户主目录
    else if (strcmp(argv[1], "~") == 0 || argv[1] == NULL)
    {
        // char prev_path[MAX_PATH_LENGTH];
        // strcpy(prev_path, path);
        chdir(getenv("HOME"));
        // strcpy(path, prev_path);
        getcwd(path, MAX_PATH_LENGTH);
    }
    // 处理普通 cd 命令，切换到指定路径
    else
    {
        // char prev_path[MAX_PATH_LENGTH];
        // strcpy(prev_path, path);
        chdir(argv[1]);
        // strcpy(path, prev_path);
        getcwd(path, MAX_PATH_LENGTH);
    }

    return;
}

void myOutRe(char *argv[])
{
    char file_name[MAX];
    char *arg[MAX_ARGS];
    int i;
    for (i = 0; i < argc; i++)
    {
        arg[i] = argv[i];
        if (strcmp(argv[i], ">") == 0)
        {
            strcpy(file_name, argv[i + 1]); // 第i+1个就是文件名了
            arg[i] = NULL;                  // 把第i个存的>给置为NULL
            break;
        }
    }

    int fdout = dup(1);                                           // 让标准输出获取一个新的文件描述符，（ 标准输入、标准输出和标准错误输出默认分别使用文件描述符 0、1 和 2 ）
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666); // 函数调用打开了一个文件名为file_name的文件，打开模式为只写模式（O_WRONLY），如果文件不存在则创建这个文件（O_CREAT），如果文件已经存在则将其长度截断为零（O_TRUNC），文件权限设置为 0666
    dup2(fd, 1);                                                  // 将文件描述符 fd 复制到标准输出的文件描述符 1 中，实现了标准输出的重定向。此时，所有输出到标准输出的内容都会被重定向到打开的文件中

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }
    else if (pid == 0)
    {
        // if(has[pipeline]){   //有管道时
        //     myPipe();
        // }
        // else
        {
            execvp(arg[0], arg);
            perror("execvp()");
            exit(1);
        }
    }
    else
    {
        // if(has[Background_running]){   //有&时
        //     has[Background_running]=0;
        //     printf("%d\n",pid);
        //     return ;
        // }
        waitpid(pid, NULL, 0); // 等待指定进程 pid 结束，并在子进程完成后立即返回。其中，status 参数被设置为 NULL，表示不关心子进程的退出状态，而 options 参数被设置为 0，表示没有特殊选项。
    }

    dup2(fdout, 1); // 将标准输出文件描述符恢复到原来的设置，以确保后续输出能够正常显示在终端上
}

void myOutRePlus(char *argv[])
{
    char file_name[MAX];
    char *arg[MAX_ARGS];
    int i;
    for (i = 0; i < argc; i++)
    {
        arg[i] = argv[i];
        if (strcmp(argv[i], ">>") == 0)
        {
            strcpy(file_name, argv[i + 1]);
            arg[i] = NULL;
            break;
        }
    }

    int fdout = dup(1);
    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666); // O_APPEND ：在写入文件时将数据追加到文件末尾
    dup2(fd, 1);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }
    else if (pid == 0)
    {
        // if(has[pipeline]){   //有管道时
        //     myPipe();
        // }
        // else
        {
            execvp(arg[0], arg);
            perror("execvp()");
            exit(1);
        }
    }
    else
    {
        // if(has[Background_running]){   //有&时
        //     has[Background_running]=0;
        //     printf("%d\n",pid);
        //     return ;
        // }
        waitpid(pid, NULL, 0);
    }

    dup2(fdout, 1);
}

void myInRe(char *argv[])
{
    char file_name[MAX];
    char *arg[MAX_ARGS];
    int i;
    for (i = 0; i < argc; i++)
    {
        arg[i] = argv[i];
        if (strcmp(argv[i], ">>") == 0)
        {
            strcpy(file_name, argv[i + 1]);
            arg[i] = NULL;
            break;
        }
    }

    int fdin = dup(0);                        // 标准输入使用文件描述符 0
    int fd = open(file_name, O_RDONLY, 0666); // O_RDONLY ：表示以只读模式打开文件
    dup2(fd, 0);

    pid_t pid = fork();
    if (pid < 0)
    {
        // if(has[Background_running]){   //有&时
        //     has[Background_running]=0;
        //     printf("%d\n",pid);
        //     return ;
        // }
        perror("fork()");
        exit(1);
    }
    else if (pid == 0)
    {
        // if(has[pipeline]){   //有管道时
        //     myPipe();
        // }
        // else
        {
            execvp(arg[0], arg);
            perror("execvp()");
            exit(1);
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
    }

    dup2(fdin, 0);
}

void myls(char *argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }
    else if (pid == 0)
    {
        execvp(argv[0],argv);
        perror("execvp()");
        exit(1);
    }
}