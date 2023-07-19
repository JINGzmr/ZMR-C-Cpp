#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <map>

const int MAX_CONN = 1024; // 最大连接数

// 保存客户端的信息
struct Client
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
    ev.data.fd = sockfd;

    ret = epoll_ctl(epid, EPOLL_CTL_ADD, sockfd, &ev);
    if (ret < 0)
    {
        perror("epoll_ctl error");
        return -1;
    }

    // 保存客户端信息
    std::map<int, Client> clients;
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

                ret = epoll_ctl(epid, EPOLL_CTL_ADD, client_sockfd, &ev_client);
                if (ret < 0)
                {
                    perror("client epoll_ctl error");
                    break;
                }
                std::cout << client_addr.sin_addr.s_addr << "正在连接..." << std::endl;

                // 保存该客户端的信息
                Client client;
                client.sockfd = client_sockfd;
                client.name = "";

                clients[client_sockfd] = client;
            }
            else // 如果客户端有消息
            {
                // 那就把这个消息保存起来
                char buffer[1024];
                int n = read(fd, buffer, 1024);
                if (n < 0)
                {
                    perror("read error");
                    break;
                }
                else if (n == 0) // 客户断开连接
                {
                    close(fd);                             // 先关闭该客户端
                    epoll_ctl(epid, EPOLL_CTL_DEL, fd, 0); // 从epoll里面删除，不需要再检测了
                    clients.erase(fd);                     // 同时把他从map里面删除
                }
                else // 接收到客户端的消息，但不确定是 登录时的用户名 这个消息，还是客户端发来的消息
                {
                    std::string msg(buffer, n);
                    
                    // 如果该客户端的name为空，说明该消息是这个客户端的用户名
                    if(clients[fd].name == "")
                    {
                        clients[fd].name = msg;
                    }
                    else // 否则是聊天消息
                    {
                        std::string name = clients[fd].name;

                        // 把消息发给其他客户端
                        for(auto&c :clients)
                        {
                            if(c.first != fd)// 不发给自己
                            {
                                write(c.first, ('['+name+']'+":"+msg).c_str(),msg.size()+name.size()+4);
                            }

                        }
                    }
                }
            }
        }
    }
}
