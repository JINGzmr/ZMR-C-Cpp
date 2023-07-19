#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>

const int MAX_CONN = 1024; // 最大连接数

// 保存客户端的信息
struct client
{
    int sockfd;
    std::string name; // 名字
};

int main()
{
    // 创建epoll实例
    int epid = epoll_create(10);
    if (epid < 0)
    {
        perror("epoll_create error");
        return -1;
    }

    // 创建监听的socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket error");
        return -1;
    }

    // 绑定本地ip和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9999);

    int ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (sockfd < 0)
    {
        perror("bind error");
        return -1;
    }

    // 监听客户端连接
    ret = listen(sockfd, 1024);
    if (ret < 0)
    {
        perror("listen error");
        return -1;
    }

    // 将监听的socket加入epoll
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = socket;

    ret = epoll_ctl(epid, EPOLL_CTL_ADD, sockfd, &ev);
    if (ret < 0)
    {
        perror("epoll_ctl error");
        return -1;
    }

    // 循环监听
    while (1)
    {
        struct epoll_event evs[MAX_CONN];
        int n = epoll_wait(epid, evs, MAX_CONN, -1);
        if (n < 0)
        {
            perror("epoll_wait error");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            int fd = evs[i].data.fd;
            // 如果是监听的fd收到消息，那么则表示有客户端进行连接了
            if (fd == sockfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int client_socket = accept(sockfd, (sturct sockaddr *)&client_addr, &client_addr_len);
                if(client_socket < 0)
                {
                    perror("accept error");
                    continue;
                }
            }
        }
    }
}
