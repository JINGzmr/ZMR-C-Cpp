#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h> //glob()
#include <sys/types.h>
#include <string.h> // strsep()
#include <sys/wait.h>

#define DELIMS " \t\n" // strsep要的分割符，包括空格

struct cmd_st
{
    glob_t globres;
};

void prompt(void);
static void parse(char *line, struct cmd_st *res); // 将一段文本或数据解析成特定格式

int main()
{
    char *linebuf = NULL;  //存从终端输入的一整行命令
    size_t linebuf_size = 0; // 是一个指向 lineptr 指向的缓冲区大小的指针（如果缓冲区太小，则会自动调整大小）
    struct cmd_st cmd;
    pid_t pid;

    while (1)
    {
        prompt(); // 打印提示符$
                                            //readline()函数好像也行
        if (getline(&linebuf, &linebuf_size, stdin) < 0) // 从终端获取用户的输入  stdin->从标准输入来读
            break;                                       // getline()从流中读取整行，将包含文本的缓冲区地址存储到*linebuf中

        parse(linebuf, &cmd); // 解析前面获取的那一行命令（->判断是内部命令还是外部命令）

        if (0) // 是内部命令 ->先不管内部的
        {
            // do something
        }
        else // 是外部命令
        {
            pid = fork();
            if (pid < 0)
            {
                perror("fork()");
                exit(1);
            }

            if (pid == 0) // child
            {
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            }
            else // parent
            {
                wait(NULL); // 收尸完再进行循环
            }
        }
        
        // if (linebuf)   //要free，但会显示 “free(): double free detected in tcache 2” 以及 “zsh: abort (core dumped)  ./a.out”
        //     free(linebuf);

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

    while (1) // 循环解析这些命令
    {
        tok = strsep(&line, DELIMS); // strtok:将一个字符串分解为0个或多个非空标记的序列
        if (tok == NULL)
            break;
        if (tok[0] == '\0') // 解析出来是一个空串
            continue;

        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres); // 把结果带回去
        i = 1;
    }
}