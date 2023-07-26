#ifndef DEFINE_H
#define DEFINE_H

const int BUFFER_SIZE = 10240; // 缓冲区的大小（用于存储recv来的序列化好的string）

#define USERNAMEUNEXIST -5 // 用户名不存在
#define USERNAMEEXIST -4   // 用户名已存在
#define OFFLINE -3         // 不在线
#define ONLINE -2          // 在线
#define FAIL -1            // 失败  --->不能单定义一个N为-1 ！！！，否则可能会破坏引用的三方库里的其他对N的定义
#define SUCCESS 0          // 成功
#define LOGIN 1            // 登录请求
#define REGISTER 2         // 注册请求
#define SIGNOUT 3          // 注销请求

#endif