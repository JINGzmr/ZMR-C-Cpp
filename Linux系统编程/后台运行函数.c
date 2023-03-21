void command_with_Back(char *buf)
{
    char BackBuf[strlen(buf)];
    memset(BackBuf, 0, strlen(buf));
    // 提取 & 前的命令
    for (int i = 0; i < strlen(buf); i++)
    {
        BackBuf[i] = buf[i];
        if (buf[i] == '&')
        {
            BackBuf[i - 1] = '\0';
            break;
        }
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        my_error(“Fork”, LINE);
    }

    if (pid == 0)
    {
        // FILE freopen(const chatpathname, const char*mode, FILE *stream);
        freopen(“/ dev / null”, “w”, stdout);
        freopen(“/ dev / null”, “r”, stdin);
        signal(SIGCHLD, SIG_IGN);
        parse(BackBuf);
        execvp(argv[0], argv);
        my_error(“execvp”, LINE);
    }
    else
    {
        exit(0); // 父进程直接退出
    }
}
