void command_with_OutRe(char *buf)
{//command > file
    char OutFile[1024];
    memset(OutFile, 0, BUFFSIZE);
    int RedNum = 0;//记录重定向符号的数量，初始值为0

//遍历字符串buf，检查是否含有重定向符号'>', 如果有，则RedNum加1。
    for(int i = 0; buf[i]; i++){
        if(buf[i] == '>'){
            RedNum++;
            break;
        }
    }

    if(RedNum != 1){//重定向符号多余1就错误
        my_error("error num of OutRe",__LINE__);
    }

    int fg = 0;//用于记录重定向符号的位置。

//遍历分割好的命令，找到重定向符号'>'所在的位置，并将其后面的字符串作为重定向输出的文件名保存到OutFile数组中，同时记录重定向符号前一个命令的位置。
    for(int i =0;i < argc; i++){//与分割好的命令逐个比较，确定重定向文件
        if(strcmp(COMMAND[i], ">") == 0){
            if(i+1 < argc){//因为有argv[argc] == NULL,所以不用<=
                strcpy(OutFile,COMMAND[i+1]);
                fg = i-1;
            }else{
                my_error("missing output file",__LINE__);
            }
        }
    }
    for (int j = 0; j < strlen(buf); j++) {
        if (buf[j] == '>') {
            buf[j - 1] = '\0';
            break;
        }
    }
    
    parse(buf);//重定向符号后面的为文件，所以需要重新解析命令
    // 子进程执行命令,利用重定向将结果输出到文件中
    pid_t pid = fork();
    if(pid < 0){
        my_error("fork",__LINE__);
    }
    if(pid == 0){
        int fd;

        fd = open(OutFile, O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
        if(fd < 0){
            my_error("open",__LINE__);
        }
        dup2(fd,STDOUT_FILENO);//灵魂
        execvp(argv[0], argv);
        if(fd != STDOUT_FILENO){
            close(fd);
        }
        my_error("fault argu",__LINE__);
    }else{
        int status;
        waitpid(pid, &status, 0);
        int err = WEXITSTATUS(status);
        if(err){
            printf("Error:%s\n",strerror(err));
        }
    }
}
