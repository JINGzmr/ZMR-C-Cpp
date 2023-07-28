// 服务端处理客户端在登录界面输入的注册、登入、注销
#include "data.h"
#include "define.h"
#include "redis.hpp"
#include "IO.h"
#include "personalprocess.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

// 登录
void login_server(int fd, struct User user, string buf)
{
    printf("--- %s 用户将要登录 ---\n", user.username.c_str());

    // 下面两种都行，但第一种的话要加上.c_str()
    printf("用户名：%s\n密码：%s\n", user.username.c_str(), user.password.c_str());
    // cout << user.username << '\n' << user.password << endl;

    Redis redis;
    redis.connect();

    if (redis.hashexists("userinfo", user.username) != 1) // 账号不存在
    {
        cout << "该用户名不存在，请注册 或 重新输入" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
    }
    else // 账号存在
    {
        string userjson_string;
        userjson_string = redis.gethash("userinfo", user.username);
        json parsed_data = json::parse(userjson_string);
        if (user.password != parsed_data["password"])
        {
            cout << "密码错误" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, FAIL);
        }
        else if (parsed_data["online"] == ONLINE)
        {
            cout << "用户已登录" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, ONLINE);
        }
        else
        {
            cout << "登录成功" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, SUCCESS);

            // 改变用户的在线状态（将原来的string只改变在线状态后，完整地发送给数据库）
            // int state_ = parsed_data["online"];
            // state_ = ONLINE;
            parsed_data["online"] = ONLINE;
            userjson_string = parsed_data.dump();
            redis.hsetValue("userinfo", user.username, userjson_string);

            // 进入服务器处理每个 个人界面 所选择的的编号对应的函数发送的数据请求 的模块
            personal_process(fd,user);
            cout <<"4564564465456546"<< endl ;
        }
    }

    return;
}

// 注册
void register_server(int fd, struct User user, string buf)
{
    printf("--- %s 用户将要注册 ---\n", user.username.c_str());
    printf("用户名：%s\n密码：%s\n", user.username.c_str(), user.password.c_str());

    Redis redis;
    redis.connect();

    if (redis.hashexists("userinfo", user.username) == 1) // 用户名已被使用
    {
        cout << "该用户名已存在，请登录 或 更改用户名后重新注册" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEEXIST);
    }
    else // 新的用户名，可以被使用
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
    printf("--- %s 用户将要注销 ---\n", user.username.c_str());
    printf("用户名：%s\n密码：%s\n", user.username.c_str(), user.password.c_str());

    Redis redis;
    redis.connect();

    if (redis.hashexists("userinfo", user.username) != 1) // 账号不存在
    {
        cout << "该用户名不存在，请注册 或 重新输入" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
    }
    else // 账号存在
    {
        string userjson_string;
        userjson_string = redis.gethash("userinfo", user.username);
        json parsed_data = json::parse(userjson_string);
        if (user.password == parsed_data["password"] && redis.hashdel("userinfo", user.username) == 3) // 密码正确且账号从哈希表中成功移除
        {
            cout << "注销成功" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, SUCCESS);
        }
        else
        {
            cout << "注销失败" << endl;
            SendMsg sendmsg;
            sendmsg.SendMsg_int(fd, FAIL);
        }
    }
    return;
}


