
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_CMD_ARG 10
#define MAX_CMD_GRP 10

const char *prompt = "myshell> ";
char *cmdgrps[MAX_CMD_GRP];
char *cmdvector[MAX_CMD_ARG];
char cmdline[BUFSIZ];
int backgnd;

void fatal(char *str)
{
    perror(str);
    exit(1);
}

int makelist(char *s, const char *delimiters, char **list, int MAX_LIST)
{
    /* 将字符串分割为数组 */
    int i = 0;
    int numtokens = 0;
    char *snew = NULL;

    if ((s == NULL) || (delimiters == NULL))
        return -1;

    snew = s + strspn(s, delimiters); // 跳过前面的分隔符
    if ((list[numtokens] = strtok(snew, delimiters)) == NULL)
        return numtokens;

    numtokens = 1;

    while (1)
    {
        if ((list[numtokens] = strtok(NULL, delimiters)) == NULL)
            break;
        if (numtokens == (MAX_LIST - 1))
            return -1; // 列表超出最大长度，返回错误
        numtokens++;
    }
    return numtokens;
}

void executecmd(char **cmd)
{
    /* 执行命令 */
    int fd, pid;
    switch (pid = fork())
    {
    case -1:
        fatal("fork error");
    case 0:
        /* 子进程执行 */
        if (!backgnd)
            signal(SIGINT, SIG_DFL);
        if (cmdgrps[1])
        {
            if ((fd = open(cmdgrps[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
                fatal("file open error");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (cmdgrps[2])
        {
            if ((fd = open(cmdgrps[2], O_RDONLY)) == -1)
                fatal("file open error");
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execvp(cmd[0], cmd);
        fatal("exec error");
    }
    if (!backgnd)
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void pipe_cmd(char *cmd)
{
    /* 处理管道命令 */
    int pfd[2], pid;
    char *pipe_cmds[MAX_CMD_ARG];
    int num_pipe_cmds = makelist(cmd, "|", pipe_cmds, MAX_CMD_ARG);
    for (int i = 0; i < num_pipe_cmds - 1; i++)
    {
        if (pipe(pfd) == -1)
            fatal("pipe error");
        switch (pid = fork())
        {
        case -1:
            fatal("fork error");
        case 0:
            close(pfd[0]);
            dup2(pfd[1], STDOUT_FILENO);
            executecmd(makelist(pipe_cmds[i], " \t", cmdvector, MAX_CMD_ARG));
            fatal("exec error");
        }
        close(pfd[1]);
        dup2(pfd[0], STDIN_FILENO);
    }
    executecmd(makelist(pipe_cmds[num_pipe_cmds - 1], " \t", cmdvector, MAX_CMD_ARG));
}

void execcmd()
{
    /* 执行命令组 */
    int cnt = makelist(cmdline, ";\n", cmdgrps, MAX_CMD_GRP);
    if (cnt == 0)
        return;
    for (int i = 0; i < cnt; i++)
    {
        memset(cmdvector, 0, sizeof(cmdvector));
        int argc = makelist(cmdgrps[i], " \t", cmdvector, MAX_CMD_ARG);
        if (argc == 0)
            continue;

        if (!strcmp(cmdvector[0], "cd"))
        {
            /* 处理 cd 命令 */
            if (chdir(cmdvector[1] ? cmdvector[1] : getenv("HOME")) == -1)
                perror("cd error");
            continue;
        }

        backgnd = 0;
        if (argc > 1 && !strcmp(cmdvector[argc - 1], "&"))
        {
            backgnd = 1;
            cmdvector[argc - 1] = 0;
        }

        if (strchr(cmdgrps[i], '|'))
        {
            /* 如果有管道符，则处理管道命令 */
            pipe_cmd(cmdgrps[i]);
        }
        else
        {
            executecmd(cmdvector);
        }
    }
}

void handle_signal(int signo)
{
    /* 处理信号 */
    printf("\nCaught signal %d\n", signo);
}

int main()
{
    signal(SIGINT, SIG_IGN);        // 忽略 Ctrl-C 信号
    signal(SIGQUIT, SIG_IGN);       // 忽略 Ctrl-\ 信号
    signal(SIGTSTP, SIG_IGN);       // 忽略 Ctrl-Z 信号
    signal(SIGTERM, handle_signal); // 捕获 SIGTERM 信号

    while (1)
    {
        fputs(prompt, stdout);
        fgets(cmdline, BUFSIZ, stdin);
        if (feof(stdin))
            exit(0);

        execcmd();
    }
    return 0;
}