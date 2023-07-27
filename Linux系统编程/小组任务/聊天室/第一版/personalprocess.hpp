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
        printf("\n\n%d\n\n",state_); //输出为0
        printf("777");

        if (state_ == LOGOUT)
        {
            logout_server(client_socket, user);
            return;
        }
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
    printf("666");
}