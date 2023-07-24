// 对客户端发来的各种json进行处理，并将事件加到工作队列，从线程池中取出工作线程进行相应的处理
#include "threadpool.h"

#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#define PORT 9999
const int MAX_CONN = 1024; // 最大连接数

int main()
{
    // 创建线程池(24个线程)
    ThreadPool threadpool(24);

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
    addr.sin_port = htons(PORT);

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

    // 创建epoll实例
    int epld = epoll_create(10);
    if (epld < 0)
    {
        perror("epoll_create error");
        return -1;
    }

    // 将监听的socket加入epoll
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;

    ret = epoll_ctl(epld, EPOLL_CTL_ADD, sockfd, &ev);
    if (ret < 0)
    {
        perror("epoll_ctl error");
        return -1;
    }

    // 循环监听
    while (1)
    {
        struct epoll_event evs[MAX_CONN];
        int n = epoll_wait(epld, evs, MAX_CONN, -1);
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
                int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (client_sockfd < 0)
                {
                    perror("accept error");
                    continue;
                }

                // 将客户端的socket加入epoll
                struct epoll_event ev_client;
                ev_client.events = EPOLLIN; // 检测客户端有没有消息过来
                ev_client.data.fd = client_sockfd;

                // 设置非阻塞
                int flag;
                flag = fcntl(client_sockfd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(client_sockfd, F_SETFL, flag); // 设置非阻塞

                // 心跳检测（开启保活，1分钟内探测不到，断开连接）
                int keep_alive = 1;
                int keep_idle = 3;
                int keep_interval = 1;
                int keep_count = 30;
                if (setsockopt(client_sockfd, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive)))
                {
                    perror("Error setsockopt(SO_KEEPALIVE) failed");
                    exit(1);
                }
                if (setsockopt(client_sockfd, IPPROTO_TCP, TCP_KEEPIDLE, &keep_idle, sizeof(keep_idle)))
                {
                    perror("Error setsockopt(TCP_KEEPIDLE) failed");
                    exit(1);
                }
                if (setsockopt(client_sockfd, SOL_TCP, TCP_KEEPINTVL, (void *)&keep_interval, sizeof(keep_interval)))
                {
                    perror("Error setsockopt(TCP_KEEPINTVL) failed");
                    exit(1);
                }
                if (setsockopt(client_sockfd, SOL_TCP, TCP_KEEPCNT, (void *)&keep_count, sizeof(keep_count)))
                {
                    perror("Error setsockopt(TCP_KEEPCNT) failed");
                    exit(1);
                }
                
                // 将该客户端加入epoll树
                ret = epoll_ctl(epld, EPOLL_CTL_ADD, client_sockfd, &ev_client);
                if (ret < 0)
                {
                    perror("client epoll_ctl error");
                    break;
                }
                std::cout << client_addr.sin_addr.s_addr << "正在连接..." << std::endl;
            }

            else // 如果客户端有消息
            {
                Task task;
                task.function = work;
                task.arg = &fd;
                threadpool.addTask(task);
            }
        }
    }

    // 关闭epoll实例及套接字
    close(epld);
    close(sockfd);
}

void work(void *arg)
{
}