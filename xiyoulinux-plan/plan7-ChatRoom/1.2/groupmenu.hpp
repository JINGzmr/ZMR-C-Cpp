// 客户端的群聊选项界面，及与群聊有关的事务
#ifndef GROUPMENU_HPP
#define GROUPMENU_HPP

#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"
#include "menu.hpp"
#include "threadwork.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

void groupmenuUI(void)
{
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "----------------------  群聊  ---------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "                      17.创建群组                  " << endl; 
    cout << "                      18.加入群组                   " << endl;
    cout << "                      19.查看已加入的群组            " << endl; 
    cout << "                      20.退出已加入的群组            " << endl;
    cout << "                      21.查看群组成员列表            " << endl; 
    cout << "                      22.管理群组（群主、管理员）     " << endl;
    cout << "                      23.选择群组聊天               " << endl;
    cout << "                      24.查看群组聊天记录            " << endl; 
    cout << "--------------------------------------------------" << endl;
    cout << "                      25.返回上一级                 " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "                      16.刷新页面                   " << endl;
    cout << "———————————————————————————————————————————————————" << endl;
}

void manegegroupUI(void)
{
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "---------------------  管理群组  -------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "                      26.添加管理员（群主）          " << endl; 
    cout << "                      27.删除管理员（群主）          " << endl; 
    cout << "                      28.查看申请列表               " << endl;  
    cout << "                      29.同意加群申请               " << endl;
    cout << "                      30.删除群成员                 " << endl;
    cout << "                      31.解散该群（群主）            " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "                      25.返回上一级                 " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "                      16.刷新页面                   " << endl;
    cout << "———————————————————————————————————————————————————" << endl;
}

// 创建群组
void creatgroup_client(int client_socket, string id, Queue<string> &RecvQue)
{
    Group group;
    cout << "输入你要创建的群组名称：(不可有空格或其他非法字符)" << endl;
    cin >> group.groupname;
    group.ownerid = id;
    group.flag = CREATGROUP;

    // 发送数据
    nlohmann::json sendJson_client = {
        {"groupname", group.groupname},
        {"flag", group.flag},
        {"ownerid", group.ownerid},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 从消息队列里取消息
    string buf = RecvQue.remove();
    json parsed_data = json::parse(buf);
    int state_ = parsed_data["state"];
    string groupid = parsed_data["groupid"];

    // 判断是否创建成功
    if (state_ == SUCCESS)
    {
        cout << "创建成功！ 群id为：" << groupid << endl;
    }
    else if (state_ == USERNAMEEXIST)
    {
        cout << "该群组名称已存在，请更改名称后重新创建！" << endl;
    }
    else if (state_ == FAIL)
    {
        cout << "创建失败！" << endl;
        return;
    }
}

// 加入群组
void addgroup_client(int client_socket, string id, Queue<string> &RecvQue)
{
    Group group;

    cout << "请输入你要加入的群组ID：";
    cin >> group.groupid;
    group.userid = id;
    group.flag = ADDGROUP;

    // 发送数据
    nlohmann::json sendJson_client = {
        {"groupid", group.groupid},
        {"userid", group.userid},
        {"flag", group.flag},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 从消息队列里取消息
    string buf = RecvQue.remove();
    json parsed_data = json::parse(buf);
    int state_ = parsed_data["state"];

    // 判断是否发送成功
    if (state_ == HADINGROUP)
    {
        cout << "你已加入该群！" << endl;
    }
    else if (state_ == USERNAMEUNEXIST)
    {
        cout << "该群id不存在！" << endl;
    }
    else if (state_ == SUCCESS)
    {
        cout << "已发送加群申请！" << endl;
    }

    return;
}

// 查看已加入的群组
void checkgroup_client(int client_socket, string id, Queue<string> &RecvQue, int fl)
{
    // 发送数据
    nlohmann::json sendJson_client = {
        {"userid", id},
        {"flag", CHECKGROUP},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 从消息队列里取消息
    string buf = RecvQue.remove();
    json parsed_data = json::parse(buf);
    vector<string> groupname_Vector = parsed_data["groupnamevector"];
    vector<string> groupid_Vector = parsed_data["groupidvector"];
    vector<int> groupposition_Vector = parsed_data["grouppositionvector"];

    if (groupname_Vector.empty())
    {
        cout << "暂无加入任何群组！" << endl;
    }
    else
    {
        // 循环打印输出
        cout << "————————————以下为已加入的群组列表————————————" << endl;
        for (int i = 0; i < groupname_Vector.size(); i++)
        {
            cout << groupname_Vector[i] << "  " << groupid_Vector[i] ;
            if (groupposition_Vector[i] == 2)
            {
                cout << "（群主）" << endl;
            }
            else if (groupposition_Vector[i] == 1)
            {
                cout << "（管理员）" << endl;
            }
            else
            {
                cout << '\n';
            }
        }
        cout << "——————————————————————————————————————————" << endl;
    }

    if (fl == 1)
    {
        cout << "按'q'返回上一级" << endl;
        string a;
        while (cin >> a && a != "q")
        {
        }
        return;
    }
}

// 退出已加入的群组
void outgroup_client(int client_socket, string id, Queue<string> &RecvQue)
{
    // 先打印出好友信息
    checkgroup_client(client_socket, id, RecvQue, 0);

    Group group;
    cout << "请输入你要删除的群id：（警告：若你为该群的群主，则直接解散该群！）";
    cin >> group.groupid;
    group.userid = id;
    group.flag = OUTGROUP;

    // 发送数据
    nlohmann::json sendJson_client = {
        {"groupid", group.groupid},
        {"userid", group.userid},
        {"flag", group.flag},
    };
    string sendJson_client_string = sendJson_client.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(client_socket, sendJson_client_string);

    // 从消息队列里取消息
    string buf = RecvQue.remove();
    json parsed_data = json::parse(buf);
    int state_ = parsed_data["state"];

    // 判断是否退出成功
    if (state_ == SUCCESS)
    {
        cout << "退出成功！" << endl;
    }
    else if (state_ == FAIL)
    {
        cout << "退出失败！" << endl;
    }
}

#endif