// 各种结构体
#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

struct User
{
    std::string username;
    std::string password;
    int flag;//标记选项
    int status; //标记从服务器返回的状态（成功SUCCESS，失败FAIL）
    int online; // 是否在线（在线ONLINE，不在OFFLINE）
};



#endif