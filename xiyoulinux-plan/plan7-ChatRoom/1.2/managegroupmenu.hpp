// 客户端的群聊管理有关的事务
#ifndef MANAGEGROUPMENU_HPP
#define MANAGEGROUPMENU_HPP

#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"
#include "menu.hpp"
#include "threadwork.hpp"
#include "groupmenu.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

string checkgroupnum_client(int client_socket, string id, Queue<string> &RecvQue, int fl);

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

// 添加管理员
void addmin_client(int client_socket, string id, Queue<string> &RecvQue)
{

    // 先打查看群成员列表
    string re = checkgroupnum_client(client_socket, id, RecvQue, 0);
    if (re == "fail")
    {
        return;
    }
    else
    {
        Group group;
        group.groupid = re;
        cout << "请输入你要设置管理员的成员id：（警告：此操作仅对群主生效！）";
        cin >> group.oppoid;
        group.userid = id;
        group.flag = ADDADMIN;

        // 发送数据
        nlohmann::json sendJson_client = {
            {"oppoid", group.oppoid},
            {"userid", group.userid},
            {"groupid", group.groupid},
            {"flag", group.flag},
        };
        string sendJson_client_string = sendJson_client.dump();
        SendMsg sendmsg;
        sendmsg.SendMsg_client(client_socket, sendJson_client_string);

        // 从消息队列里取消息
        string buf = RecvQue.remove();
        json parsed_data = json::parse(buf);
        int state_ = parsed_data["state"];

        // 判断是否成功
        if (state_ == SUCCESS)
        {
            cout << "群管理添加成功！" << endl;
        }
        else if (state_ == HADADMIN)
        {
            cout << "该成员已是管理员！" << endl;
        }
        else if (state_ == FAIL)
        {
            cout << "你权限不够，操作失败！" << endl;
        }
    }
}

#endif