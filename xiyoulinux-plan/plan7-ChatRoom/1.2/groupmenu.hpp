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
    cout << "                      17.创建群组                  " << endl; // set:groupname,groupname/hash:groupname_id,name,id/hash:groupid_name,id,name
    cout << "                      18.加入群组                   " << endl;
    cout << "                      19.查看已加入的群组            " << endl; // set:uid+group,groupid
    cout << "                      20.退出已加入的群组            " << endl;
    cout << "                      21.查看群组成员列表            " << endl; // set:groupid+num,uid/groupid+admin,uid(分两块打印不同的人，管理员包括群主，且群主在第一个)
    cout << "                      22.查看我创建的群组            " << endl; // set:uid+mycreatgroup,groupid
    cout << "                      23.查看我管理的群组            " << endl; // set:uid+myadmingroup,groupid
    cout << "                      24.管理群组（群主、管理员）     " << endl;
    cout << "                      25.选择群组聊天               " << endl;
    cout << "                      26.查看群组聊天记录            " << endl; // list:groupid,消息的结构体
    cout << "--------------------------------------------------" << endl;
    cout << "                      27.返回上一级                 " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "                      16.刷新页面                   " << endl;
    cout << "———————————————————————————————————————————————————" << endl;
}

void manegegroupUI(void)
{
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "---------------------  管理群组  -------------------" << endl;
    cout << "——————————————————————————————————————————————————" << endl;
    cout << "                      28.添加管理员（群主）          " << endl; // set:groupid+admin,uid
    cout << "                      29.删除管理员（群主）          " << endl; // set:groupid+admin,uid
    cout << "                      30.查看申请列表               " << endl;  // set:groupid+apply,uid
    cout << "                      31.同意加群申请               " << endl;
    cout << "                      32.删除群成员                 " << endl;
    cout << "                      33.解散该群（群主）            " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "                      27.返回上一级                 " << endl;
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

#endif