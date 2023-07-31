// 服务器对客户端personalmenu里不同的选项进行不同的处理
#ifndef PERSONALPROCESS_HPP
#define PERSONALPROCESS_HPP

#include "data.h"
#include "define.h"
#include "IO.h"
#include "redis.hpp"
#include <vector>

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
    redis.sremvalue("onlinelist", id); // 把用户从在线列表中移除

    cout << "退出登录成功" << endl;
}

// 加好友
void addfriend_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    friend_.oppoid = parsed_data["oppoid"];
    printf("--- %s 用户将向 %s 发送好友申请 ---\n", friend_.id.c_str(), friend_.oppoid.c_str());

    Redis redis;
    redis.connect();

    // // 从数据库里取出好友列表
    // string userjson_string;
    // userjson_string = redis.gethash("friendlist", friend_.id);
    // parsed_data = json::parse(userjson_string);

    // // JSON 反序列化,并添加到 friendlist.friends 中
    // struct FriendList friendlist;
    // const auto &friendsJson = parsed_data["friends"];
    // for (const auto &friendName : friendsJson)
    // {
    //     friendlist.friends.push_back(friendName);
    // }

    // // 使用 find 在容器中查找目标 id
    // auto it = find(friendlist.friends.begin(), friendlist.friends.end(), friend_.oppoid);

    // 构造好友列表
    string key = friend_.id + "frienids"; //id+friends作为键，值就是id用户的好友们

    // 加好友
    if (redis.hashexists("userinfo", friend_.id) != 1) // 账号不存在
    {
        cout << "该id不存在，请重新输入" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
    }
    // else if (it != friendlist.friends.end())
    else if(redis.sismember(key, friend_.oppoid) == 1) // 好友列表里已有对方
    {
        cout << "你们已经是好友" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, HADFRIEND);
    }
    else if (redis.sismember("onlinelist", friend_.oppoid) == 1) // 在线列表里有对方
    {
        cout << "对方在线" << endl;
        redis.saddvalue(key, friend_.oppoid);// 这里先视为对方在线，发请求对方默认同意
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
    else // 对方不在线：加入数据库，等用户上线时提醒
    {
        cout << "对方不在线" << endl; //*******问不在线要怎么办
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
}

// 在线好友

#endif