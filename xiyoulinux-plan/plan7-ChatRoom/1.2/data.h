// 各种结构体及容器
#ifndef DATA_H
#define DATA_H

#include <vector>

#include <iostream>
using namespace std;

// string chatid = "";
string chatname = "";

// 注册登录（哈希存，键：userinfo，字段：用户id，值：User的json字符串）
struct User
{
    int flag;        // 标记选项
    string username; // 用户名（独一无二）
    string password; // 密码
    string id;       // 服务器随机生成的id（独一无二）--->使用户更改用户名的时候，该用户的数据不变
    int status;      // 标记从服务器返回的状态（成功SUCCESS，失败FAIL）
    int online;      // 是否在线（在线ONLINE，不在OFFLINE）
};

// 加好友
struct Friend
{
    int type;        // 标记事件类型（正常NORMAL，通知NOTICE）
    int flag;        // 标记选项
    string username; // 用户名
    string id;       // id
    string opponame; // 对方用户名
    string oppoid;   // 对方id
    string msg;      // 通知消息
    int state;       // 标记从服务器返回的状态（成功SUCCESS，失败FAIL）
    int online;      // 是否在线（在线ONLINE，不在OFFLINE）
};

// 聊天消息
struct Chatinfo
{
    string name;
    string msg;
    // string time;
};

#endif