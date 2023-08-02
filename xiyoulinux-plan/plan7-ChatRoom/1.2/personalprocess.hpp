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
    string key = friend_.id + ":friends";            // id+friends作为键，值就是id用户的好友们
    string key_ = friend_.oppoid + ":friends_apply"; // 对方的好友申请表

    // 加好友
    if (redis.hashexists("userinfo", friend_.oppoid) != 1) // 账号不存在
    {
        cout << "该id不存在，请重新输入" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
    }
    // else if (it != friendlist.friends.end())
    else if (redis.sismember(key, friend_.oppoid) == 1) // 好友列表里已有对方
    {
        cout << "你们已经是好友" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, HADFRIEND);
    }
    else if (redis.sismember("onlinelist", friend_.oppoid) == 1) // 在线列表里有对方
    {
        cout << "对方在线" << endl;

        // 放到对方的好友申请表中
        redis.saddvalue(key_, friend_.id);

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
    else // 对方不在线：加入数据库，等用户上线时提醒
    {
        cout << "对方不在线" << endl; //*******问不在线要怎么办*************

        // 放到对方的好友申请表中
        redis.saddvalue(key_, friend_.id);

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
}

// 好友申请----->在函数里用到了recv，如果是非阻塞的话，recv会显示接受失败，然后就和那个客户端断开了连接
// 查看申请列表
void friendapplylist_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    printf("--- %s 用户查看好友申请列表 ---\n", friend_.id.c_str());

    Redis redis;
    redis.connect();

    string key = friend_.id + ":friends_apply";
    string userjson_string;
    int len = redis.scard(key);
    SendMsg sendmsg;
    sendmsg.SendMsg_int(fd, len);
    cout << "一共有 " << len << " 条好友请求" << endl;
    if (len == 0)
    {
        return;
    }

    redisReply **arry = redis.smembers(key);
    // 展示好友请求列表
    for (int i = 0; i < len; i++)
    {
        // 得到发送请求的用户id
        string applyfriend_id = arry[i]->str;

        // 根据id发送好友昵称
        nlohmann::json json_ = {
            {"username", redis.gethash("id_name", applyfriend_id)}, // 拿着id去找username
        };
        string json_string = json_.dump();
        SendMsg sendmsg;
        sendmsg.SendMsg_client(fd, json_string);

        freeReplyObject(arry[i]);
    }
}
// 编辑好友申请
void friendapplyedit_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    string name = parsed_data["name"];
    int state = parsed_data["state"];
    printf("--- %s 用户编辑好友申请 ---\n", friend_.id.c_str());
    cout << name << endl;
    cout << state << endl;

    Redis redis;
    redis.connect();

    string key = friend_.id + ":friends_apply";

    if (redis.sismember("username", name) != 1)
    {
        cout << "查无此人" << endl;

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
        return;
    }

    // 得到发送请求的用户id
    string applyfriend_id = redis.gethash("name_id", name); // 由昵称找id

    if (redis.sismember(key, applyfriend_id) != 1)
    {
        cout << "不存在此好友申请！" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, FAIL);
    }
    else if (state == 1)
    {
        cout << "已同意" << endl;
        redis.sremvalue(key, applyfriend_id); // 从申请列表中移除
        string key1 = friend_.id + ":friends";
        string key2 = applyfriend_id + ":friends";
        redis.saddvalue(key1, applyfriend_id); // 对方成为自己好友
        redis.saddvalue(key2, friend_.id);     // 自己成为对方好友

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
    else
    {
        cout << "已拒绝" << endl;
        redis.sremvalue(key, applyfriend_id); // 从申请列表中移除

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
}

// 好友信息
void friendinfo_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    printf("--- %s 用户查看在线好友列表 ---\n", friend_.id.c_str());

    Redis redis;
    redis.connect();

    string key = friend_.id + ":friends";
    string userjson_string;
    int len = redis.scard(key);
    SendMsg sendmsg;
    sendmsg.SendMsg_int(fd, len);
    cout << "一共有 " << len << " 个好友" << endl;
    if (len == 0)
    {
        return;
    }

    redisReply **arry = redis.smembers(key);
    // 向客户端挨个发送好友在线信息
    for (int i = 0; i < len; i++)
    {
        // 得到好友id
        int state = 0;
        string friend_id = arry[i]->str;
        if (redis.sismember("onlinelist", friend_id) == 1)
        {
            state = 1;
        }

        // 根据id发送好友昵称
        nlohmann::json json_ = {
            {"username", redis.gethash("id_name", friend_id)},
            {"id", friend_id},
            {"online", state},
        };
        string json_string = json_.dump();
        SendMsg sendmsg;
        sendmsg.SendMsg_client(fd, json_string);

        freeReplyObject(arry[i]);
    }
}

// 屏蔽好友
void addblack_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    friend_.oppoid = parsed_data["oppoid"];
    printf("--- %s 用户将要屏蔽好友 ---\n", friend_.id.c_str());

    Redis redis;
    redis.connect();

    string key = friend_.id + ":bfriends";
    string key_ = friend_.id + ":friends";

    if (redis.sismember(key_, friend_.oppoid) != 1) // 对方不是你的好友
    {
        cout << "对方不是你好友" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, FAIL);
    }
    else if (redis.sismember(key, friend_.oppoid) == 1) // 已拉黑对方
    {
        cout << "已拉黑对方" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, HADBLACK);
    }
    else
    {
        cout << "拉黑成功" << endl;
        redis.saddvalue(key, friend_.oppoid);
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
}

// 删除好友
void delfriend_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    friend_.oppoid = parsed_data["oppoid"];
    printf("--- %s 用户将要删除好友 ---\n", friend_.id.c_str());

    Redis redis;
    redis.connect();

    string key = friend_.id + ":friends";
    string key_ = friend_.oppoid + ":friends";
    string bkey = friend_.id + ":bfriends";
    //*************还要删除聊天记录****************
    if (redis.sismember(key, friend_.oppoid) == 1 && redis.sremvalue(key, friend_.oppoid) == 3 && redis.sremvalue(key_, friend_.id) == 3 && redis.sremvalue(bkey, friend_.oppoid))
    {
        cout << "删除成功" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
    else
    {
        cout << "删除失败" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, FAIL);
    }
}

// 查看屏蔽好友列表
void blackfriendlist_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    printf("--- %s 用户查看屏蔽好友列表 ---\n", friend_.id.c_str());

    Redis redis;
    redis.connect();

    string key = friend_.id + ":bfriends";
    string userjson_string;
    int len = redis.scard(key);
    SendMsg sendmsg;
    sendmsg.SendMsg_int(fd, len);
    cout << "一共有 " << len << " 个被拉黑的好友" << endl;
    if (len == 0)
    {
        return;
    }

    redisReply **arry = redis.smembers(key);
    // 展示好友请求列表
    for (int i = 0; i < len; i++)
    {
        // 得到被拉黑用户的id
        string bfriend_id = arry[i]->str;

        // 根据id发送好友昵称
        nlohmann::json json_ = {
            {"username", redis.gethash("id_name", bfriend_id)}, // 拿着id去找username
        };
        string json_string = json_.dump();
        SendMsg sendmsg;
        sendmsg.SendMsg_client(fd, json_string);

        freeReplyObject(arry[i]);
    }
}
// 编辑屏蔽好友
void blackfriendedit_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    string name = parsed_data["name"];
    printf("--- %s 用户编辑屏蔽好友 ---\n", friend_.id.c_str());
    cout << name << endl;

    Redis redis;
    redis.connect();

    string key = friend_.id + ":bfriends";

    if (redis.sismember("username", name) != 1)
    {
        cout << "查无此人" << endl;

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, USERNAMEUNEXIST);
        return;
    }

    // 得到发送请求的用户id
    string bfriend_id = redis.gethash("name_id", name); // 由昵称找id

    if (redis.sismember(key, bfriend_id) != 1)
    {
        cout << "不存在此拉黑好友！" << endl;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, FAIL);
    }
    else
    {
        cout << "已从拉黑名单中去除" << endl;
        redis.sremvalue(key, bfriend_id); // 从屏蔽列表中移除

        SendMsg sendmsg;
        sendmsg.SendMsg_int(fd, SUCCESS);
    }
}

// 好友聊天历史记录
void historychat_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    friend_.opponame = parsed_data["opponame"];
    printf("--- %s 用户查看与 %s 的聊天记录 ---\n", friend_.id.c_str(), friend_.opponame.c_str());

    Redis redis;
    redis.connect();

    friend_.oppoid = redis.gethash("name_id",friend_.opponame);
    string key;
    if(friend_.id < friend_.oppoid)
    {
        key = friend_.id + friend_.oppoid + ":historychat";
    }
    else 
    {
        friend_.oppoid + friend_.id + ":historychat";
    }
    string userjson_string;
    int len = redis.llen(key);
    SendMsg sendmsg;
    sendmsg.SendMsg_int(fd, len);
    cout << "一共有 " << len << " 条历史消息" << endl;
    if (len == 0)
    {
        return;
    }

    redisReply **arry = redis.lrange(key);
    for (int i = len -1; i >=0; i--)
    {
        // 得到历史消息json的字符串
        string msg = arry[i]->str;

        SendMsg sendmsg;
        sendmsg.SendMsg_client(fd, msg);

        freeReplyObject(arry[i]);
    }
}

#endif