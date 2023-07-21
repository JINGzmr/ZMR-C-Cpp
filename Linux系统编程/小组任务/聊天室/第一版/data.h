// 各种结构体
#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

struct User
{
    std::string username;
    std::string password;
    // int uid = 0;
    int flag = 0;//标记选项
    bool yn; //标记从服务器返回的状态（成功yes，失败no）
    // int fd = 0;
};



#endif