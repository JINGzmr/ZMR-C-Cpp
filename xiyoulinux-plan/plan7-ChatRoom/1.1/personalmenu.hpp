#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"
#include "menu.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

void addfriend_client(int client_socket);

void logout_client(int client_socket, string username);
void addfriend_client(int client_socket, string username);
void friendapply_client(int client_socket, string id);
void onlinefriend_client(int client_socket, string id);

void personalmenuUI(void)
{
    cout << "————————————————————————————————————————————————————" << endl;
    cout << "|---------------------  聊天室  --------------------|" << endl;
    cout << "|——————————————————————————————————————————————————|" << endl;
    cout << "|                      4.添加好友                   |" << endl;
    cout << "|                      5.查看好友申请                |" << endl;
    cout << "|                      6.选择好友私聊                |" << endl;
    cout << "|                      7.查看历史聊天记录            |" << endl;
    cout << "|                      8.在线好友                   |" << endl;
    cout << "|                      9.屏蔽好友                   |" << endl;
    cout << "|                      10.删除好友                  |" << endl;
    cout << "|                      11.查看好友                  |" << endl;
    cout << "|                      12.查看屏蔽好友               |" << endl;
    cout << "|--------------------------------------------------|" << endl;
    cout << "|                      11.群聊                      |" << endl;
    cout << "|                      12.拉入黑名单                 |" << endl;
    cout << "|                      13.拉出黑名单                 |" << endl;
    cout << "|                      14.发送文件                   |" << endl;
    cout << "|                      15.接受文件                   |" << endl;
    cout << "|---------------------------------------------------|" << endl;
    cout << "|                      16.退出登录                   |" << endl;
    cout << "————————————————————————————————————————————————————" << endl;
}

void messagemenu(int client_socket, string id)
{
    personalmenuUI();

    int num = 1;
    do
    {
        cin >> num;

        switch (num)
        {
        case 4:
            addfriend_client(client_socket, id);
            personalmenuUI();
            break;
        case 5:
            friendapply_client(client_socket, id);
            break;
        // case 6:
        //     chatfriend_client(client_socket);
        //     break;
        // case 7:
        //     historychat_client(client_socket);
        //     break;
        // case 8:
        //     onlinefriend_client(client_socket,id);
        //     break;
        // case 9:
        //     addblack_client(client_socket);
        //     break;
        // case 10:
        //     delfriend_client(client_socket);
        //     break;
        // case 11:
        //     friendlist_client(client_socket);
        //     break;
        // case 12:
        //     blackfriendlist_client(client_socket);
        //     break;
        case 13:

            break;
        case 14:

            break;
        case 15:

            break;
        case 16:
            logout_client(client_socket, id);
            break;
        default:
            cout << "无效的数字，请重新输入！" << endl;
            personalmenuUI();
        }
    } while (num != 16); // 16表示退出登录，即退出循环，返回上一级

    return;
}

// 退出登录
void logout_client(int client_socket, string id)
{
    nlohmann::json sendJson_client = {
        {"flag", LOGOUT},
        {"id", id},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);
    cout << "退出成功！" << endl;
}

// 加好友
void addfriend_client(int client_socket, string id)
{
    Friend friend_;
    do
    {
        cout << "请输入你要添加的朋友ID：";
        cin >> friend_.oppoid;
        friend_.id = id;
        friend_.flag = ADDFRIEND;

        if (friend_.id == friend_.oppoid)
        {
            cout << "不可添加自己！请重新输入！" << endl;
        }
    } while (friend_.id == friend_.oppoid);

    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", friend_.id},
        {"oppoid", friend_.oppoid},
        {"flag", friend_.flag},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收数据
    int state_;
    RecvMsg recvmsg;
    state_ = recvmsg.RecvMsg_int(client_socket);

    // 判断是否登入成功
    if (state_ == SUCCESS)
    {
        cout << "已发送好友申请！" << endl;
    }
    else if (state_ == HADFRIEND)
    {
        cout << "你们已经是好友！" << endl;
    }
    else if (state_ == USERNAMEUNEXIST)
    {
        cout << "该id不存在，请重新输入" << endl;
    }

    return;
}

// 好友申请
void friendapply_client(int client_socket, string id)
{
    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"flag", FRIENDAPPLY},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收好友申请的个数
    int n = 0;
    RecvMsg recvmsg;
    n = recvmsg.RecvMsg_int(client_socket);
    cout << "一共有 " << n << " 条好友请求" << endl;
    if (n == 0)
    {
        return;
    }

    // 依次展示好友请求
    for (int i = 0; i < n; i++)
    {
        // 接收好友昵称
        string recvJson_buf;
        RecvMsg recvmsg;
        recvmsg.RecvMsg_client(client_socket, recvJson_buf);
        json parsed_data = json::parse(recvJson_buf);
        string username = parsed_data["username"];

        // 是否同意
        cout << username << " 请求添加为好友 ( yes--1 / no--0 )" << endl;
        int state;
        cin >> state;
        SendMsg sendmsg;
        sendmsg.SendMsg_int(client_socket, state);
        if (state == 1)
        {
            cout << "你们已成为好友！" << endl;
        }
        else
        {
            cout << "你已拒绝对方申请！" << endl;
        }
    }
}

// // 在线好友
// void onlinefriend_client(int client_socket, string id)
// {
//     // 发送数据
//     nlohmann::json sendJson_client = {
//         {"flag", ONLINEFRIEND},
//     };
//     string sendJson_client_string = sendJson_client.dump();
//     SendMsg sendmsg;
//     sendmsg.SendMsg_client(client_socket, sendJson_client_string);

//     // 接收数据

// }