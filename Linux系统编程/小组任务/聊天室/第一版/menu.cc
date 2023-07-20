// 菜单界面，对接的是客户端
// 几个函数，客户端在不同的菜单栏选择不同的选项，进入不同的模块
// 在不同的模块下对用户输入的各种数据进行json序列化和IO的SendMsg
// 并且接收RecvMsg来自服务端发送回来的数据，进行反序列化，打印在页面上
#include "data.h"
#include "define.h"
#include "head.h"

#include <iostream>


using namespace std;

void menu()
{
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "------------------欢迎进入聊天室！-------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "---------------------1.登录------------------------" << endl;
    cout << "---------------------2.注册------------------------" << endl;
    cout << "---------------------3.注销------------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;

    int num;
    cin >> num;
    switch (num)
    {
    case 1:
        login();
        break;
    case 2:
        // 执行代码块2
        break;
    case 3:
        // 执行代码块3
        break;
    }
}

void login(void)
{
    User user;
    std::cout << "请输入用户名: ";
    std::cin >> user.username;
    std::cout << "请输入密码: ";
    std::cin >> user.password;
    user.flag = LOGIN; // 表示是要登录

    nlohmann::json userJson = {
        {"username", user.username},
        {"password", user.password},
        {"flag", user.flag},
    };

    std::string userJson_string = userJson.dump();

    if (send(client_socket, userJson_string.c_str(), userJson_string.size(), 0) == -1) {
        std::cerr << "Send failed" << std::endl;
    } else {
        std::cout << "Data sent to the server" << std::endl;
    }
}
