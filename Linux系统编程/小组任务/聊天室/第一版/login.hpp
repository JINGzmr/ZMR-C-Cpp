// 服务端处理客户端在登录界面输入的注册、登入、注销

#include <iostream>
using namespace std;

// 登录
void login_server(int fd,struct User user)
{
    printf("登录");
    printf("%s %s",user.username,user.password);
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