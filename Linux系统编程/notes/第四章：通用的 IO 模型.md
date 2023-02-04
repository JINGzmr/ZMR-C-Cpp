#概述
- **文件描述符fd**（小的非负整数）：指代打开的文件，用以表示所有类型的已打开文件（管道（pipe）、FIFO、socket、终端、设备和普通文件）
   - 可以使用数字（0、1、2）表示，或者采用<unistd.h>所定义的POSIX 标准名称
- **标准文件描述符**![](2023-02-05-00-07-08.png)
    - 在程序开始运行之前，[shell](https://blog.csdn.net/qq_40964554/article/details/100899628?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167552686316800213069583%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167552686316800213069583&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-5-100899628-null-null.142^v73^wechat_v2,201^v4^add_ask,239^v1^insert_chatgpt&utm_term=shell&spm=1018.2226.3001.4187) 代表程序打开这3 个文件描述符，命令行有操作，shell会适当修改文件描述符

---
# 打开一个文件：open()
![](2023-02-05-00-28-31.png)
> ==fd = open(pathname, flags, mode)==
>成功-返回文件描述符，失败-返回-1并将errno 置为相应的错误标志
  -  pathname :标识要打开的文件（若是链接，则引用）
  -  flags ：位掩码，用于指定文件的**访问模式**![](2023-02-05-00-32-54.png)
  -  mode ：调用 open()创建新文件时，位掩码参数 mode 指定了文件的**访问权限**（mode_t 属于整数类型）
  ![](2023-02-05-00-42-45.png)