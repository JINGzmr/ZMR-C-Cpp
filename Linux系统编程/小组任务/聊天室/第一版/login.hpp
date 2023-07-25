// 服务端处理客户端在登录界面输入的注册、登入、注销
#include "data.h"
#include "define.h"

#include <iostream>
using namespace std;

// 登录
void login_server(int fd,struct User user)
{
    printf("登录\n");
    printf("%s %s",user.username,user.password);

    // json序列化，及向服务器发送数据
    user.status = SUCCESS;
    nlohmann::json sendJson_server = {
        {"status", user.status},
    };

    string sendJson_server_string = sendJson_server.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(fd, sendJson_server_string);

    return;
}

// 注册
void register_server(int fd,struct User user)
{
    printf("注册");
    
    printf("%s %s",user.username,user.password);

}

// 注销
void signout_server(int fd,struct User user)
{
    printf("注销");
}