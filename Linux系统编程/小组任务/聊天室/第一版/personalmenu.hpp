#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"
#include "menu.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

void logout_client(int client_socket);

void messagemenu(int client_socket, string username)
{
    cout << "————————————————————————————————————————————————————" << endl;
    cout << "|---------------------  聊天室  --------------------|" << endl;
    cout << "|——————————————————————————————————————————————————|" << endl;
    cout << "|                      4.加好友                     |" << endl;
    cout << "|                      5.查看好友申请                |" << endl;
    cout << "|                      6.私聊                       |" << endl;
    cout << "|                      7.查看历史聊天记录             |" << endl;
    cout << "|                      8.查询好友信息                |" << endl;
    cout << "|                      9.查看好友列表                |" << endl;
    cout << "|                      10.删除好友                   |" << endl;
    cout << "|                      11.群聊                      |" << endl;
    cout << "|                      12.拉入黑名单                 |" << endl;
    cout << "|                      13.拉出黑名单                 |" << endl;
    cout << "|                      14.发送文件                   |" << endl;
    cout << "|                      15.接受文件                   |" << endl;
    cout << "|                      16.退出登录                   |" << endl;
    cout << "————————————————————————————————————————————————————" << endl;

    int num = 1;
    do
    {
        cin >> num;

        switch (num)
        {
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:

            break;
        case 11:

            break;
        case 12:

            break;
        case 13:

            break;
        case 14:

            break;
        case 15:

            break;
        case 16:
            logout_client(client_socket);
            break;
        default:
            cout << "无效的数字，请重新输入！" << endl;
        }
    } while (num != 16); // 16表示退出登录，即退出循环，返回上一级

    return;
}

void logout_client(int client_socket)
{
    SendMsg sendmsg;
    sendmsg.SendMsg_int(client_socket, LOGOUT);
    cout << "退出成功！" << endl;
}
 
