// 服务器对客户端managegroupmenu里不同的选项进行不同的处理
#ifndef MANAGEGROUPPROCESS_HPP
#define MANAGEGROUPPROCESS_HPP

#include "data.h"
#include "define.h"
#include "IO.h"
#include "redis.hpp"
#include <vector>

#include <iostream>
using json = nlohmann::json;
using namespace std;

// 添加管理员（通知被添加的管理员）
void addmin_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Group group;
    group.groupid = parsed_data["groupid"];
    group.userid = parsed_data["userid"];
    group.oppoid = parsed_data["oppoid"];
    printf("--- %s 用户将要添加 %s 为管理员 ---\n", group.userid.c_str(), group.oppoid.c_str());

    Redis redis;
    redis.connect();

// ***********判断用户是否存在************
    if (redis.sismember(group.userid + ":mycreatgroup", group.groupid) != 1) // 不是群主，无权操作
    {
        group.type = NORMAL;
        group.state = FAIL;
    }
    else if (redis.sismember(group.groupid + ":admin", group.oppoid) == 1) // 对方已经是管理员了
    {
        group.type = NORMAL;
        group.state = HADADMIN;
    }
    else if (redis.sismember("onlinelist", group.oppoid) == 1) // 对方在线
    {
        redis.saddvalue(group.groupid + ":admin", group.oppoid);
        redis.saddvalue(group.oppoid + ":myadmingroup", group.groupid);
        group.msg = "你被添加为“" + redis.gethash("groupid_name", group.groupid) + "”群的管理员";
        group.type = NOTICE;
        group.state = SUCCESS;
    }
    else // 离线
    {
        redis.saddvalue(group.groupid + ":admin", group.oppoid);
        redis.saddvalue(group.oppoid + ":myadmingroup", group.groupid);
        group.msg = "你被添加为“" + redis.gethash("groupid_name", group.groupid) + "”群的管理员";
        group.type = NOTICE;
        group.state = SUCCESS;

        redis.saddvalue(group.oppoid + ":unreadnotice", group.msg);
    }

    // 发送状态和信息类型
    nlohmann::json json_ = {
        {"type", group.type},
        {"flag", 0},
        {"state", group.state},
        {"msg", group.msg},
    };
    string json_string = json_.dump();
    SendMsg sendmsg;
    if (group.type == NORMAL)
    {
        sendmsg.SendMsg_client(fd, json_string);
    }
    else if (group.type == NOTICE)
    {
        sendmsg.SendMsg_client(stoi(redis.gethash("usersocket", group.oppoid)), json_string);

        // 改成正常的类型后给本用户的客户端发回去，不然客户端接不到事件的处理进度
        json_["type"] = NORMAL;
        json_string = json_.dump();
        sendmsg.SendMsg_client(fd, json_string);
    }
}

#endif