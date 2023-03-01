    /*
        if(argc == 1){
            myls(".");
        }
        else{
            while(--argc){
                myls(*(++argv));
            }
        }
        return 0;
        char param[100];
        int cnt = 0; // 命令个数
        int num = 0;
        对命令行参数进行解析，提取到param数组中
        for (n = 1; n < argc; n++)
        {
            if (argv[n][0] == '-')
            {
                for (int j = 1; j < strlen(argv[i]); cnt++, j++)
                {
                    param[cnt] = argv[i][j]; // 获取-后面的参数保存到数组param中
                }
                num++; // 保存 - 的个数
            }
        }

        for (n = 0; n < cnt; n++)
        {
            if (param[n] == 'a')has[a]=1;
            else if (param[n] == 'l')has[l]=1;
            else if (param[n] == 'R')has[R]=1;
            else if (param[n] == 't')has[t]=1;
            else if (param[n] == 'r')has[r]=1;
            else if (param[n] == 'i')has[i]=1;
            else if (param[n] == 's')has[s]=1;
        }
        printf("%d",num);
        printf("%d",argc);
        printf("%s",argv[2]);
        char c = '-';
        if (argc - num >= 2)
        {
            if (strncmp(argv[1], c, 1) == 0)
                myls(argv[argc - 1]);
        dir = argv[argc-1];
        printf("%s", argv[argc-1]);
        else
            myls(argv[1]);
        printf("%s", argv[1]);
        dir = argv[1];
        }
        else
        {
            myls(".");
        }
        printf("%s", dir);
    */
    
    
    
    
    
    
    
    
    // // 如果没有输入路径，就设置为当前路径
    // if (argc == 1 || *argv[argc - 1] == '-')
    // {
    //     myls(has, ".");
    //     return 0;
    // }

    // int n = 1;
    // do
    // {
    //     // 如果不是目标文件名或目录，解析下一个命令行参数(/桌面/练习代码/Linux系统编程就是目标文件名或目录，而非在当前目录下)
    //     if (argv[n][0] == '-') // 跳过-s-l
    //     {
    //         n++;
    //         continue;
    //     }
    //     else
    //     {
    //         struct stat buf;
    //         strcpy(path, argv[n]); // path存储目标文件名或目录（路径）

    //         // 如果目标文件或目录不存在，报错并退出程序
    //         if (stat(path, &buf) == -1)
    //             perror("stat fail:");
    //         // 判断该路径是不是目录
    //         if (S_ISDIR(buf.st_mode)) // S_ISDIR判断路径目录函数
    //         {
    //             // 是目录但是没带 '/'就加上'/'
    //             if (path[strlen(argv[n]) - 1] != '/')
    //             {
    //                 path[strlen(argv[n])] = '/';
    //                 path[strlen(argv[n]) + 1] = '\0';
    //             }

    //             if (has[R])
    //             {
    //                 // myls_R(has,path);
    //             }
    //             else                 // 不用递归出目录下的子目录，打印当前目录即可
    //                 myls(has, path); //// 进入‘打开、读取、关闭目录’流程

    //             n++;
    //         }
    //         else // argv[i]是一个文件
    //         {
    //             myls(has, path);
    //             n++;
    //         }
    //     }
    // } while (n < argc);