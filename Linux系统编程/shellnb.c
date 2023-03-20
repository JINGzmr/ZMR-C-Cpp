#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h> //glob()
#include <sys/types.h>
#include <string.h> // strsep()
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define DELIMS " \t\n" // strsep要的分割符，包括空格

struct cmd_st
{
    glob_t globres;
};

void prompt(void);
static void parse(char *line, struct cmd_st *res); // 将一段文本或数据解析成特定格式
static int have_pipe(char *line);                  // 判断是否有管道符 |
static void redirect(char *line);                  // 输入输出重定向
static void do_pipe(char *line);                   // 执行管道
void do_cd(int argc, char **argv);                 // 执行cd命令
static void mywait(pid_t pid);                     // 用来waitpid的封装函数

int main()
{
    char *linebuf = NULL;
    size_t linebuf_size = 0; // *linebuf缓冲区的大小
    struct cmd_st cmd;
    pid_t pid;
    int status;

    signal(SIGINT, SIG_IGN);  // 忽略SIGINT信号
    signal(SIGQUIT, SIG_IGN); // 忽略SIGQUIT信号
    signal(SIGTSTP, SIG_IGN); // 忽略SIGTSTP信号

    while (1)
    {
        prompt(); // 打印提示符$

        if (getline(&linebuf, &linebuf_size, stdin) < 0) // 从终端获取用户的输入  stdin->从标准输入来读
            break;                                       // getline()从流中读取整行，将包含文本的缓冲区地址存储到*linebuf中

        if (have_pipe(linebuf))
        {
            do_pipe(linebuf); // 执行管道操作
            continue;
        }

        redirect(linebuf); // 输入输出重定向

        parse(linebuf, &cmd); // 解析前面获取的那一行命令（->判断是内部命令还是外部命令）

        if (cmd.globres.gl_pathc == 0) // 用户没有输入命令，就重新进入while循环等待输入
            continue;

        if (strcmp(cmd.globres.gl_pathv[0], "cd") == 0) // 是cd命令
        {
            do_cd(cmd.globres.gl_pathc, cmd.globres.gl_pathv);
            continue;
        }

        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }

        if (pid == 0) // child
        {
            signal(SIGINT, SIG_DFL);  // 恢复SIGINT信号默认处理方式
            signal(SIGQUIT, SIG_DFL); // 恢复SIGQUIT信号默认处理方式
            signal(SIGTSTP, SIG_DFL); // 恢复SIGTSTP信号默认处理方式

            execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
            perror("execvp()");
            exit(1);
        }
        else // parent
        {
            if (redirect(linebuf)) // 输入输出重定向
            {
                close(STDIN_FILENO);
                close(STDOUT_FILENO);
            }

            if (linebuf[strlen(linebuf) - 2] == '&') // 后台运行
            {
                printf("running in background: %s", linebuf);
                continue;
            }
            else // 前台运行
            {
                mywait(pid);
            }
        }
    }

    exit(0);
}

void prompt(void)
{
    printf("mysh-0.1$ ");
}

static void parse(char *line, struct cmd_st *res) // 将一段文本或数据解析成特定格式
{                                                 // ls -a -l   /etc  .....
    char *tok;                                    // strsep要的返回值是一个char*类型，存每次while循环扣出来的小串
    int i = 0;

    while (1)
    {                                // 循环解析
        tok = strsep(&line, DELIMS); // strtok:将一个字符串分解为0个或多个非空标记的序列
        if (tok == NULL)
            break;
        if (tok[0] == '\0') // 解析出来是一个空串
            continue;

        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres); // 把结果带回去
        i = 1;
    }
}

static int have_pipe(char *line) // 判断是否有管道符 |
{
    char *p = line;

    while (*p)
    {
        if (*p == '|')
            return 1;
        p++;
    }

    return 0;
}

static void redirect(char *line) // 输入输出重定向
{
    char *file;
    int fd;
    int pos;

    pos = strlen(line) - 1; // 找到最后一个字符

    while (pos > 0 && line[pos] != '>' && line[pos] != '<' && line[pos] != '2')
        pos--;

    if (pos == 0) // 没有输入输出重定向符
        return;

    if (line[pos] == '<') // 输入重定向
    {
        file = line + pos + 1; // 文件名在符号后面的位置

        while (*file == ' ') // 文件名前面可能有空格
            file++;

        if (*file == '\0')
        {
            fprintf(stderr, "invalid input redirect\n");
            exit(1);
        }

        file[strlen(file) - 1] = '\0'; // 去掉文件名末尾的换行符

        fd = open(file, O_RDONLY);
        if (fd < 0)
        {
            perror("open()");
            exit(1);
        }

        dup2(fd, STDIN_FILENO); // 将fd复制到标准输入流
        close(fd);
        line[pos] = '\0'; // 将输入重定向符替换成\0
    }
    else if (line[pos + 1] == '>') // 输出重定向
    {
        if (line[pos + 2] == '>') // 追加重定向
        {
            file = line + pos + 3;
            while (*file == ' ')
                file++;

            if (*file == '\0')
            {
                fprintf(stderr, "invalid output append redirect\n");
                exit(1);
            }

            file[strlen(file) - 1] = '\0';

            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else // 覆盖重定向
        {
            file = line + pos + 2;
            while (*file == ' ')
                file++;

            if (*file == '\0')
            {
                fprintf(stderr, "invalid output redirect\n");
                exit(1);
            }

            file[strlen(file) - 1] = '\0';

            fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }

        if (fd < 0)
        {
            perror("open()");
            exit(1);
        }

        dup2(fd, STDOUT_FILENO); // 将fd复制到标准输出流
        close(fd);
        line[pos] = '\0';
    }
    else if (strcmp(&line[pos], "2>") == 0) // 错误重定向
    {
        file = line + pos + 2;
        while (*file == ' ')
            file++;

        if (*file == '\0')
        {
            fprintf(stderr, "invalid error redirect\n");
            exit(1);
        }

        file[strlen(file) - 1] = '\0';

        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd < 0)
        {
            perror("open()");
            exit(1);
        }

        dup2(fd, STDERR_FILENO); // 将fd复制到标准错误流
        close(fd);
        line[pos] = '\0';
    }
}

static void do_pipe(char *line) // 执行管道
{
    char *p = line;
    int pipefd[2];
    pid_t pid;
    int status;

    while (*p)
    {
        if (*p == '|')
            *p = '\0'; // 将管道符替换成结束符\0
        p++;
    }
    p = line;
    while (*p == ' ')
        p++; // 去掉管道符前面可能有的空格

    if (pipe(pipefd) < 0)
    {
        perror("pipe()");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) // child
    {
        close(pipefd[0]);               // 关闭读端
        dup2(pipefd[1], STDOUT_FILENO); // 将输出流重定向到写端
        close(pipefd[1]);               // 关闭写端

        execl("/bin/sh", "sh", "-c", p, NULL);
        perror("execl()");
        exit(1);
    }
    else // parent
    {
        close(pipefd[1]);              // 关闭写端
        dup2(pipefd[0], STDIN_FILENO); // 将输入流重定向到读端
        close(pipefd[0]);              // 关闭读端

        while (*p++)
            ;

        execl("/bin/sh", "sh", "-c", p, NULL);
        perror("execl()");
        exit(1);
    }

    mywait(pid); // 等待子进程结束
}

void do_cd(int argc, char **argv) // 执行cd命令
{
    if (argc == 1 || strcmp(argv[1], "~") == 0) // 没有指定目录或者指定为~
        chdir(getenv("HOME"));
    else if (strcmp(argv[1], "-") == 0) // 指定为-
        chdir(getenv("OLDPWD"));
    else
        chdir(argv[1]);

    printf("current dir: %s\n", getenv("PWD"));
}

static void mywait(pid_t pid) // 用来waitpid的封装函数
{
    int status;

    while (waitpid(pid, &status, WNOHANG) == 0) // 等待子进程结束
    {
        sleep(1);
    }

    if (WIFEXITED(status)) // 子进程正常退出
    {
        printf("child %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) // 子进程被信号杀死
    {
        printf("child %d terminated by signal %d\n", pid, WTERMSIG(status));
    }
    else if (WIFSTOPPED(status)) // 子进程被暂停
    {
        printf("child %d stopped by signal %d\n", pid, WSTOPSIG(status));
    }
}
