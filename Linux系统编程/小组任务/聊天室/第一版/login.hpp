// 服务端处理客户端在登录界面输入的注册、登入、注销
#include "data.h"
#include "define.h"
#include "redis.hpp"

#include <iostream>
using namespace std;

// 登录
void login_server(int fd, struct User user, string buf)
{
    printf("--- %s 用户将要登录 ---\n", user.username.c_str());

    // 下面两种都行，但第一种的话要加上.c_str()
    printf("用户名：%s\n密码：%s", user.username.c_str(), user.password.c_str());
    // cout << user.username << '\n' << user.password << endl;

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
void register_server(int fd, struct User user, string buf)
{
    printf("--- %s 用户将要注册 ---\n", user.username.c_str());
    printf("用户名：%s\n密码：%s", user.username.c_str(), user.password.c_str());

    Redis redis;
    redis.connect();

    if (redis.hashexists("userinfo", user.username) == 1)
    {
        cout << "该用户名已存在，请登录 或 更改用户名后重新注册" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEEXIST);
    }
    else
    {
        int n = redis.hsetValue("userinfo", user.username, buf);
        if (n == REDIS_REPLY_ERROR)
        {
            cout << "注册失败" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, FAIL);
        }
        else
        {
            cout << "注册成功" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, SUCCESS);
        }
    }
    return;
}

// 注销
void signout_server(int fd, struct User user)
{
    printf("注销");
}