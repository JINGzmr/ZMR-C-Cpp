#include<iostream>
#include<string>
#include<sys/epoll>

const int MAX_CONN = 1024;//最大连接数

//保存客户端的信息
struct client
{
    int sockfd;
    std::string name;//名字
}

int main()
{
    //创建epoll实例
    int epid = epoll_create(10);
    
}