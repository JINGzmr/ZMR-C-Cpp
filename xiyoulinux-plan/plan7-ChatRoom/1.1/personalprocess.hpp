// 服务器对客户端personalmenu里不同的选项进行不同的处理
#ifndef PERSONALPROCESS_HPP
#define PERSONALPROCESS_HPP

#include "data.h"
#include "define.h"
#include "IO.h"
#include "redis.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

// 退出登录
void logout_server(string buf)
{
    json parsed_data = json::parse(buf);
    string id = parsed_data["id"];
    printf("--- %s 用户将要退出登录 ---\n", id.c_str());

    Redis redis;
    redis.connect();

    string userjson_string;
    userjson_string = redis.gethash("userinfo", id);
    parsed_data = json::parse(userjson_string);

    // 改变用户的在线状态
    parsed_data["online"] = OFFLINE;
    userjson_string = parsed_data.dump();
    redis.hsetValue("userinfo", id, userjson_string);

    cout << "退出登录成功" << endl;
}

void addfriend_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    friend_.oppoid = parsed_data["oppoid"];
    printf("--- %s 用户将向 %s 发送好友申请 ---\n", friend_.id.c_str(),friend_.oppoid.c_str());

    Redis redis;
    redis.connect();

    if (redis.hashexists("userinfo", friend_.id) != 1) // 账号不存在
    {
        cout << "该用户名不存在，请重新输入" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
    }
    // else if()
}


#endif