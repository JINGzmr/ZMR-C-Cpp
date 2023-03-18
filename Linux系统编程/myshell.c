#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h> //glob()
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>


#define DELIMS " \t\n"

struct cmd_st
{
    glob_t globres;
};

void prompt(void)
{
    printf("mysh-0.1$ ");
}

static void parse(char *line, struct cmd_st *res)
{ // ls -a -l /etc  .....
    char *tok;
    int i = 0;

    while (1)
    {
        tok = strsep(&line, DELIMS);
        if (tok == NULL)
            break;
        if (tok[0] == '\0')
            continue;

        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres);
        i = 1;
    }
}

int main()
{
    char *linebuf = NULL;
    size_t linebuf_size = 0;
    struct cmd_st cmd;
    pid_t pid;

    while (1)
    {
        prompt(); // 打印提示符

        if (getline(&linebuf, &linebuf_size, stdin) < 0) // 从终端获取用户的输入  stdin->从标准输入来读
            break;

        parse(linebuf,&cmd); // 解析前面获取的那一行命令（->判断是内部命令还是外部命令）

        if (0) // 是内部命令 ->先不管内部的
        {
            //do something
        }
        else // 是外部命令
        {
            fork();
            if (pid < 0)
            {
                perror("fork()");
                exit(1);
            }

            if (pid == 0) // child
            {
                execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            }
            else // parent
            {
                wait(NULL);  //收尸完再进行循环
            }
        }
    }

    exit(0);
}