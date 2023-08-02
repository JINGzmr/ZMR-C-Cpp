#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"
#include "menu.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

void logout_client(int client_socket, string username);
void addfriend_client(int client_socket, string username);
void friendapplylist_client(int client_socket, string id);
void friendapplyedit_client(int client_socket, string id);
void friendinfo_client(int client_socket, string id);
void addblack_client(int client_socket, string id);
void delfriend_client(int client_socket, string id);
void blackfriendlist_client(int client_socket, string id);
void blackfriendedit_client(int client_socket, string id);
void historychat_client(int client_socket, string id);

void personalmenuUI(void)
{
    cout << "————————————————————————————————————————————————————" << endl;
    cout << "---------------------  聊天室  --------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "                      4.添加好友                   " << endl;
    cout << "         51.查看好友申请列表   52.编辑好友申请         " << endl;
    cout << "                      6.选择好友私聊                " << endl;
    cout << "                      7.查看历史聊天记录            " << endl;
    cout << "                      8.好友信息                   " << endl;
    cout << "                      9.屏蔽好友                   " << endl;
    cout << "                      10.删除好友                  " << endl;
    cout << "         111.查看屏蔽好友列表   112.编辑屏蔽好友       " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "                      11.群聊                      " << endl;
    cout << "                      12.拉入黑名单                 " << endl;
    cout << "                      13.拉出黑名单                 " << endl;
    cout << "                      14.发送文件                   " << endl;
    cout << "                      15.接受文件                   " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "                      16.退出登录                   " << endl;
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
        case 51:
            friendapplylist_client(client_socket, id);
            break;
        case 52:
            friendapplyedit_client(client_socket, id);
            personalmenuUI();
            break;
        // case 6:
        //     chatfriend_client(client_socket);
        //     break;
        case 7:
            historychat_client(client_socket, id);
            break;
        case 8:
            friendinfo_client(client_socket, id);
            break;
        case 9:
            addblack_client(client_socket, id);
            personalmenuUI();
            break;
        case 10:
            delfriend_client(client_socket, id);
            personalmenuUI();
            break;
        case 111:
            blackfriendlist_client(client_socket, id);
            break;
        case 112:
            blackfriendedit_client(client_socket, id);
            break;
        // case 13:

        //     break;
        // case 14:

        //     break;
        // case 15:

        //     break;
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
void friendapplylist_client(int client_socket, string id)
{
    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"flag", FRIENDAPPLYLIST},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收好友申请的个数
    int n = 0;
    RecvMsg recvmsg;
    n = recvmsg.RecvMsg_int(client_socket);
    cout << "（ 一共有 " << n << " 条好友请求 ）" << endl;
    if (n == 0)
    {
        return;
    }

    // 清空容器
    friendapply_Vector.clear();

    cout << "————————————以下为好友申请列表————————————" << endl;
    // 展示好友请求
    for (int i = 0; i < n; i++)
    {
        // 接收好友昵称
        string recvJson_buf;
        RecvMsg recvmsg;
        recvmsg.RecvMsg_client(client_socket, recvJson_buf);
        json parsed_data = json::parse(recvJson_buf);
        string username = parsed_data["username"];

        // 放入本地vector里
        friendapply_Vector.push_back(username);

        // 打印出好友请求列表
        cout << username << endl;
    }
    cout << "——————————————————————————————————————————" << endl;
}
// 编辑申请
void friendapplyedit_client(int client_socket, string id)
{
    string name;
    int state;
    cout << "输入要编辑的好友昵称" << endl;
    cin >> name;
    cout << "同意---1 / 拒绝---0" << endl;
    cin >> state;

    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"flag", FRIENDAPPLYEDIT},
        {"name", name},
        {"state", state},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收数据
    int state_;
    RecvMsg recvmsg;
    state_ = recvmsg.RecvMsg_int(client_socket);

    // 判断是否操作成功
    if (state_ == SUCCESS)
    {
        cout << "操作成功！" << endl;

        // 从容器中去除已编辑过的成员
        for (auto it = friendapply_Vector.begin(); it != friendapply_Vector.end(); ++it)
        {
            if (*it == name)
            {
                friendapply_Vector.erase(it);
                break;
            }
        }
    }
    else if (state_ == FAIL)
    {
        cout << "不存在此好友申请！" << endl;
    }
    else if (state_ == USERNAMEUNEXIST)
    {
        cout << "查无此人! " << endl;
    }
}

// 好友信息
void friendinfo_client(int client_socket, string id)
{
    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"flag", FRIENDINFO},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收在线好友个数
    int n = 0;
    RecvMsg recvmsg;
    n = recvmsg.RecvMsg_int(client_socket);
    cout << "（ 一共有 " << n << " 个好友 ）" << endl;
    if (n == 0)
    {
        return;
    }

    cout << "————————————以下为你的好友列表————————————" << endl;
    // 展示好友列表（并显示在线状态）
    for (int i = 0; i < n; i++)
    {
        // 接收好友昵称
        string recvJson_buf;
        RecvMsg recvmsg;
        recvmsg.RecvMsg_client(client_socket, recvJson_buf);
        json parsed_data = json::parse(recvJson_buf);
        string username = parsed_data["username"];
        string id = parsed_data["id"];
        int state = parsed_data["online"];

        cout << username << "  " << id;
        if (state == 1)
        {
            cout << " （在线）" << endl;
        }
        else
        {
            cout << '\n';
        }
    }
    cout << "——————————————————————————————————————————" << endl;
}

// 屏蔽好友
void addblack_client(int client_socket, string id)
{
    Friend friend_;
    do
    {
        cout << "请输入你要屏蔽的朋友ID：";
        cin >> friend_.oppoid;
        friend_.id = id;
        friend_.flag = ADDBLACK;

        if (friend_.id == friend_.oppoid)
        {
            cout << "不可屏蔽自己！请重新输入！" << endl;
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

    // 判断是否拉黑成功
    if (state_ == SUCCESS)
    {
        cout << "拉黑成功！" << endl;
    }
    else if (state_ == FAIL)
    {
        cout << "对方不是你的好友！" << endl;
    }
    else if (state_ == HADBLACK)
    {
        cout << "对方已被拉黑！" << endl;
    }
}

// 删除好友
void delfriend_client(int client_socket, string id)
{
    Friend friend_;
    do
    {
        cout << "请输入你要删除的朋友ID：";
        cin >> friend_.oppoid;
        friend_.id = id;
        friend_.flag = DELFRIEND;

        if (friend_.id == friend_.oppoid)
        {
            cout << "不可删除自己！请重新输入！" << endl;
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
        cout << "删除成功！" << endl;
    }
    else if (state_ == FAIL)
    {
        cout << "删除失败！" << endl;
    }
}

// 查看屏蔽好友
void blackfriendlist_client(int client_socket, string id)
{
    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"flag", BLACKFRIENDLIST},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收屏蔽好友个数
    int n = 0;
    RecvMsg recvmsg;
    n = recvmsg.RecvMsg_int(client_socket);
    cout << "（ 一共有 " << n << " 个被拉黑的好友 ）" << endl;
    if (n == 0)
    {
        return;
    }

    // 清空容器
    bfriends_Vector.clear();

    cout << "————————————以下为拉黑好友列表————————————" << endl;
    // 展示好友请求
    for (int i = 0; i < n; i++)
    {
        // 接收好友昵称
        string recvJson_buf;
        RecvMsg recvmsg;
        recvmsg.RecvMsg_client(client_socket, recvJson_buf);
        json parsed_data = json::parse(recvJson_buf);
        string username = parsed_data["username"];

        // 放入本地vector里
        bfriends_Vector.push_back(username);

        // 打印出好友请求列表
        cout << username << endl;
    }
    cout << "——————————————————————————————————————————" << endl;
}
// 编辑屏蔽好友
void blackfriendedit_client(int client_socket, string id)
{
    string name;
    int state;
    cout << "输入要移除黑名单的好友昵称" << endl;
    cin >> name;

    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"flag", BLACKFRIENDEDIT},
        {"name", name},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收数据
    int state_;
    RecvMsg recvmsg;
    state_ = recvmsg.RecvMsg_int(client_socket);

    // 判断是否操作成功
    if (state_ == SUCCESS)
    {
        cout << "操作成功！" << endl;

        // 从容器中去除已编辑过的成员
        for (auto it = bfriends_Vector.begin(); it != friendapply_Vector.end(); ++it)
        {
            if (*it == name)
            {
                bfriends_Vector.erase(it);
                break;
            }
        }
    }
    else if (state_ == FAIL)
    {
        cout << "不存在此拉黑好友！" << endl;
    }
    else if (state_ == USERNAMEUNEXIST)
    {
        cout << "查无此人! " << endl;
    }
}

// 好友聊天历史记录
void historychat_client(int client_socket, string id)
{
    string opponame;
    cout << "输入要查看历史消息的好友昵称：" << endl;
    cin >> opponame;

    // 发送数据
    nlohmann::json sendJson_client = {
        {"id", id},
        {"opponame", opponame},
        {"flag", HISTORYCHAT},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 接收历史消息个数
    int n = 0;
    RecvMsg recvmsg;
    n = recvmsg.RecvMsg_int(client_socket);
    cout << "（ 一共有 " << n << " 条历史消息 ）" << endl;
    if (n == 0)
    {
        return;
    }

    cout << "———————————————以下为历史消息——————————————————" << endl;
    for (int i = 0; i < n; i++)
    {
        string recvJson_buf;
        RecvMsg recvmsg;
        recvmsg.RecvMsg_client(client_socket, recvJson_buf);
        json parsed_data = json::parse(recvJson_buf);
        string msg = parsed_data["msg"]; // msg还是json字符串类型的

        // 打印
        parsed_data = json::parse(msg);
        struct Chatinfo chatinfo;
        chatinfo.name = parsed_data["name"];
        chatinfo.msg = parsed_data["msg"];
        chatinfo.time = parsed_data["time"];

        cout << chatinfo.name << ": " << chatinfo.msg << endl;
    }
    cout << "———————————————以上为历史消息——————————————————" << endl;
}