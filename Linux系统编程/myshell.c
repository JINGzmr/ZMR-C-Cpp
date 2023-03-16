#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DELIMS " \t\n"

void prompt(void)
{
    printf("mysh-0.1$ ");
}

static parse(char *line)
{
    char *tok;
    while (1)
    {
        tok = strsep(&line, DELIMS);
        if(tok == NULL)
            break;
        if(tok[0]=='\0')
            continue;
            
    }
}

int main()
{
    char *linebuf = NULL;
    size_t linebuf_size = 0;

    while (1)
    {
        prompt(); // 打印提示符

        if (getline(&linebuf, &linebuf_size, stdin) < 0) // 从终端获取用户的输入  stdin->从标准输入来读
            break;

        parse(linebuf); // 解析前面获取的那一行命令（->判断是内部命令还是外部命令）

        if (0) // 是内部命令 ->先不管内部的
        {
        }
        else // 是外部命令
        {
            fork();
            if (< 0)
            {
            }

            if (== 0) // child
            {
                execXX();
                perror();
                exit(1);
            }
            else // parent
            {
                wait();
            }
        }
    }

    exit(0);
}