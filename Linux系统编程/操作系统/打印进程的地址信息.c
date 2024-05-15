#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int  a;
int  b=1;
 
int main()
{
    int  n = 0;
    char *p1 = NULL;
    char *p2 = NULL;
    const int s = 10;
    p1 = (char*)malloc(200);
    p2 = "super-lzx";
    printf("PID is:%d\n\n",getpid());
    printf("main  %p\n",main);
    printf("未初始化 a   %p\n",&a);
    printf("初始化   b   %p\n",&b);
    printf("局部变量 n   %p\n",&n);
    printf("动态内存 p1  %p\n",p1);
    printf("常量    s    %p\n",&s);
    printf("常字符串 p2  %p\n",p2);
    pause();
    return 0;	
}
