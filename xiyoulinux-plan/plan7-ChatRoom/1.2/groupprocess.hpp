// 服务器对客户端groupmenu里不同的选项进行不同的处理
#ifndef GROUPPROCESS_HPP
#define GROUPPROCESS_HPP

#include "data.h"
#include "define.h"
#include "IO.h"
#include "redis.hpp"
#include <vector>

#include <iostream>
using json = nlohmann::json;
using namespace std;

// 创建群组
void creatgroup_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Group group;
    group.groupname = parsed_data["groupname"];
    group.ownerid = parsed_data["ownerid"];
    printf("--- %s 用户将要创建名称为 %s 的群聊 ---\n", group.ownerid.c_str(), group.groupname.c_str());

    Redis redis;
    redis.connect();

    if (redis.sismember("groupname", group.groupname) == 1) // 名称已被使用
    {
        cout << "该群组名称已存在，请更改名称后重新创建" << endl;
        group.state = USERNAMEEXIST;
    }
    else
    {
        // 生成群id
        group.groupid = produce_id();

        // 向数据库里加数据
        int m = redis.saddvalue("groupname", group.groupname);                   // 所有的群聊名称
        int n = redis.hsetValue("groupname_id", group.groupname, group.groupid); // 群名找群id
        int o = redis.hsetValue("groupid_name", group.groupid, group.groupname); // 群id找群名
        int p = redis.saddvalue(group.ownerid + ":group", group.groupid);        // id对应用户所加的群聊
        int q = redis.saddvalue(group.groupid + ":num", group.ownerid);          // 群成员名单
        int r = redis.saddvalue(group.groupid + ":admin", group.ownerid);        // 群管理员
        int s = redis.saddvalue(group.ownerid + ":mycreatgroup", group.groupid); // id对应用户创建的群聊
        int t = redis.saddvalue(group.ownerid + ":myadmingroup", group.groupid); // id对应用户管理的群聊（包括当群主的群聊）

        if (n == REDIS_REPLY_ERROR || m == REDIS_REPLY_ERROR || o == REDIS_REPLY_ERROR || p == REDIS_REPLY_ERROR || q == REDIS_REPLY_ERROR || r == REDIS_REPLY_ERROR || s == REDIS_REPLY_ERROR || t == REDIS_REPLY_ERROR)
        {
            cout << "创建失败" << endl;
            group.state = FAIL;
        }
        else
        {
            cout << "创建成功" << endl;
            group.state = SUCCESS;
        }
    }

    // 发送状态和信息类型
    nlohmann::json json_ = {
        {"type", NORMAL},
        {"state", group.state},
        {"flag", 0},
        {"groupid", group.groupid},
    };
    string json_string = json_.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(fd, json_string);
}

// 加入群组
void addgroup_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Group group;
    group.groupid = parsed_data["groupid"];
    group.userid = parsed_data["userid"];
    printf("--- %s 用户将向 %s 发送加群申请 ---\n", group.userid.c_str(), group.groupid.c_str());

    Redis redis;
    redis.connect();

    string key = group.groupid + ":admin";
    int len = redis.scard(key);
    redisReply **arry = redis.smembers(key);
    vector<string> admins_Vector;  // 放群主及管理员的的容器
    vector<string> online_Vector;  // 在线的管理员名单
    // vector<string> offline_Vector; // 离线管理员名单
    int online_len = 0;            // 名单长度
    // int offline_len = 0;

    // 加群
    if (redis.hashexists("groupid_name", group.groupid) != 1) // 群id不存在
    {
        cout << "该群id不存在" << endl;
        group.state = USERNAMEUNEXIST;
        group.type = NORMAL;
    }
    else if (redis.sismember(group.userid + ":group", group.groupid) == 1) // 已加入该群
    {
        cout << "你已加入该群！" << endl;
        group.state = HADINGROUP;
        group.type = NORMAL;
    }
    else // 可以申请
    {
        // 找出群管理员
        for (int i = 0; i < len; i++)
        {
            string admin_id = arry[i]->str;
            admins_Vector.push_back(admin_id);

            if (redis.sismember("onlinelist", admin_id) == 1) // 在线列表里有群管理员，那就给每个在线的发送通知
            {
                cout << admin_id << "在线" << endl;
                online_Vector.push_back(admin_id);
                online_len++;
                group.msg = redis.gethash("id_name", group.userid) + "向" + redis.gethash("groupid_name", group.groupid) + "发送了一条加群申请";
                group.state = SUCCESS;
                group.type = NOTICE;

                // 放到该群的申请表中
                redis.saddvalue(group.groupid + ":groupapply", group.userid);
            }
            else // 对方不在线：加入数据库，等管理员上线时提醒，如果被其他管理员同意了，进入申请进群列表里无法看到(同意时要把这个从申请表中移除)
            {
                cout << admin_id << "不在线" << endl;
                // offline_Vector.push_back(admin_id);
                // offline_len++;
                group.msg = redis.gethash("id_name", group.userid) + "向" + redis.gethash("groupid_name", group.groupid) + "发送了一条加群申请";
                group.state = SUCCESS;
                group.type = NORMAL;

                // 加入到对方的未读通知消息队列里
                redis.saddvalue(admin_id + ":unreadnotice", group.msg);

                // 放到该群的申请表中
                redis.saddvalue(group.groupid + ":groupapply", group.userid);
            }
            freeReplyObject(arry[i]);
        }
    }

    // 发送状态和信息类型
    nlohmann::json json_ = {
        {"type", group.type},
        {"state", group.state},
        {"msg", group.msg},
        {"flag", 0},
    };
    string json_string = json_.dump();
    SendMsg sendmsg;

    if (group.type == NORMAL)
    {
        sendmsg.SendMsg_client(fd, json_string);
    }
    else if (group.type == NOTICE) // 如果是通知消息，那就把这条消息发给管理员（所以下面要根据管理员的id获得对方的socket）
    {
        for (int i = 0; i < online_len; i++)
        {
            string onlineadmin_id = online_Vector[i];
            sendmsg.SendMsg_client(stoi(redis.gethash("usersocket", onlineadmin_id)), json_string);
        }
        // 改成正常的类型后给本用户的客户端发回去，不然客户端接不到事件的处理进度
        json_["type"] = NORMAL;
        json_string = json_.dump();
        sendmsg.SendMsg_client(fd, json_string);
    }
    cout << "here" << endl;
}

#endif