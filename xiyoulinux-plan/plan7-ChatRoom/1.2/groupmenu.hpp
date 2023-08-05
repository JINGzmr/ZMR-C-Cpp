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
    cout << "                      22.查看我创建的群组            " << endl;
    cout << "                      23.查看我管理的群组            " << endl;
    cout << "                      24.管理群组（群主、管理员）     " << endl;
    cout << "                      25.选择群组聊天               " << endl;
    cout << "                      26.查看群组聊天记录            " << endl;
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
    cout << "                      28.添加管理员（群主）          " << endl;
    cout << "                      29.删除管理员（群主）          " << endl;
    cout << "                      30.查看申请列表               " << endl;
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
    
}

#endif