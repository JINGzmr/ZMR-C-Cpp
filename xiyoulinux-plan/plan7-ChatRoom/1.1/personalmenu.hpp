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

void personalmenuUI(void)
{
    cout << "————————————————————————————————————————————————————" << endl;
    cout << "|---------------------  聊天室  --------------------|" << endl;
    cout << "|——————————————————————————————————————————————————|" << endl;
    cout << "|                      4.添加好友                   |" << endl;
    cout << "|                      5.查看好友申请                |" << endl;
    cout << "|                      6.选择好友私聊                |" << endl;
    cout << "|                      7.查看历史聊天记录             |" << endl;
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
        // case 5:
        //     friendapply_client(client_socket);
        //     break;
        // case 6:
        //     chatfriend_client(client_socket);
        //     break;
        // case 7:
        //     historychat_client(client_socket);
        //     break;
        // case 8:
        //     onlinfiend_client(client_socket);
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
    } while (friend_.id != friend_.oppoid);

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
    else if (state_ == FAIL)
    {
        cout << "你们已经是好友！" << endl;
    }
    else if (state_ == USERNAMEUNEXIST)
    {
        cout << "该id不存在，请重新输入" << endl;
    }

    return;
}