// 服务端在用户登录成功后 进入的函数
// 以及对personalmenu里不同的选项进行不同的处理

#include "data.h"
#include "define.h"
#include "IO.h"
#include "redis.hpp"

void logout_server(int client_socket, struct User user);

void personal_process(int client_socket, struct User user)
{
    while (1)
    {
        int state_;
        RecvMsg recvmsg;
        state_ = recvmsg.RecvMsg_int(client_socket);
        //***有问题：如果套接字设置为非阻塞的话，只要有出现recv的地方，就算没有数据可以读取，他也会不断的读数据，不断的读取失败。。。。。。
        // 然后服务器的终端会一直出现 recv读取失败 的错误提示
        // 直到在客户端有新的选择时，才会停下来

        if (state_ == LOGOUT)
        {
            logout_server(client_socket, user);
            return;
        }
        // else if
        // {
            
        // }
    }
}

void logout_server(int client_socket, struct User user)
{
    Redis redis;
    redis.connect();

    string userjson_string;
    userjson_string = redis.gethash("userinfo", user.username);
    json parsed_data = json::parse(userjson_string);

    // 改变用户的在线状态
    parsed_data["online"] = OFFLINE;
    userjson_string = parsed_data.dump();
    redis.hsetValue("userinfo", user.username, userjson_string);
}