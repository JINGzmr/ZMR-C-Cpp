#include <iostream>
#include <string>
#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

#define PORT 9999
#define ServerAddr "127.0.0.1"

int main()
{
    // 创建连接对象
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    // 客户端连接的IP和端口号
    sockaddr_in server_address{};
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ServerAddr, &server_address.sin_addr) <= 0) {
        perror("invalid address");
        return EXIT_FAILURE;
    }

    // 连接服务器
    int connect_result = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (connect_result == -1) {
        perror("connection failed");
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "欢迎来到私人聊天室，请输入你的聊天用户名：" << std::endl;
    }

    // 循环发消息
    pthread_create(NULL, NULL, SendMsg, client_socket);

    // 循环收消息

    // 关闭套接字
    close(client_socket);
}
