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
        int r = redis.saddvalue(group.groupid + ":owner", group.ownerid);        // 群主
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

#endif