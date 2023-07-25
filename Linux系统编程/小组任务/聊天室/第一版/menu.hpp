// 菜单界面，对接的是客户端
// 几个函数，客户端在不同的菜单栏选择不同的选项，进入不同的模块
// 在不同的模块下对用户输入的各种数据进行json序列化和IO的SendMsg
// 并且接收RecvMsg来自服务端发送回来的数据，进行反序列化，打印在页面上
#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"
#include "personalmenu.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

void menu(int client_socket)
{
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "------------------欢迎进入聊天室！-------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "---------------------1.登录------------------------" << endl;
    cout << "---------------------2.注册------------------------" << endl;
    cout << "---------------------3.注销------------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;

    while(1){
        int num;
        cin >> num;

        switch (num)
        {
        case 1:
            login_client(client_socket); // 传一个客户端的socket进来
            break;
        case 2:
            register_client(client_socket);
            break;
        case 3:
            signout_client(client_socket);
            break;
        default:
            cout << "无效的数字，请重新输入！" << endl;
            break;
        }
    }
}

void login_client(int client_socket)
{
    User user;
    cout << "请输入用户名: ";
    cin >> user.username;
    cout << "请输入密码: ";
    cin >> user.password;
    user.flag = LOGIN; // 表示是要登录

    // json序列化，及向服务器发送数据
    nlohmann::json sendJson_client = {
        {"username", user.username},
        {"password", user.password},
        {"flag", user.flag},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收来自服务器的数据，及json反序列化
    string recvJson_client_string;
    RecvMsg recvmsg;
    recvmsg.RecvMsg_client(client_socket, recvJson_client_string);

    json parsed_data = json::parse(recvJson_client_string);
    User un_user;                   // 反序列化得到的结构体
    un_user.status = parsed_data["status"]; // 只有登录成功与否的状态

    // 判断是否登入成功
    if (un_user.status == 0)
    {
        cout << "登入成功！" << endl;
        //********一个进入下一页面的入口********
        messagemenu();
    }
    else
    {
        cout << "登入失败！" << endl;
        //*********再次回到登入界面重新输入***********
    }
}

void register_client(int client_socket)
{
    User user;
    cout << "请输入用户名: ";
    cin >> user.username;
    cout << "请输入密码: ";
    cin >> user.password;
    user.flag = REGISTER; // 表示是要注册

    // 序列化，发送数据
    nlohmann::json sendJson_client = {
        {"username", user.username},
        {"password", user.password},
        {"flag", user.flag},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收数据，反序列化
    string recvJson_client_string;
    RecvMsg recvmsg;
    recvmsg.RecvMsg_client(client_socket, recvJson_client_string);

    json parsed_data = json::parse(recvJson_client_string);
    User un_user;
    un_user.status = parsed_data["status"];

    // 判断是否注册成功
    if (un_user.status == 0)
    {
        cout << "注册成功！" << endl;
        //*******回到登入界面进行登录*********
    }
    else
    {
        cout << "注册失败！" << endl;
        //*********再次回到登入界面重新注册*************
    }
}

void signout_client(int client_socket)
{
    User user;
    cout << "请输入用户名: ";
    cin >> user.username;
    user.flag = SIGNOUT; // 表示是要注销

    // 序列化，发送数据（不用把结构体的所有成员都序列化）
    nlohmann::json sendJson_client = {
        {"username", user.username},
        {"flag", user.flag},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收数据，反序列化
    string recvJson_client_string;
    RecvMsg recvmsg;
    recvmsg.RecvMsg_client(client_socket, recvJson_client_string);

    json parsed_data = json::parse(recvJson_client_string);
    User un_user;
    un_user.status = parsed_data["status"];

    // 判断是否注销成功
    if (un_user.status == 0)
    {
        cout << "注销成功！" << endl;
        //*******回到登入界面，看用户是否注册登入*********
    }
    else
    {
        cout << "注销失败！" << endl;
        //*********再次回到登入界面重新注销*************
    }
}

