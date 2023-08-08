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

    if (redis.hashexists("userinfo", group.oppoid) != 1) // 用户不存在
    {
        cout << "该用户不存在" << endl;
        group.type = NORMAL;
        group.state = USERNAMEUNEXIST;
    }
    else if (redis.sismember(group.oppoid + ":group", group.groupid) != 1) // 对方不是群成员
    {
        cout << "该用户不在群聊中" << endl;
        group.type = NORMAL;
        group.state = NOTINGROUP;
    }
    else
    {
        if (redis.sismember(group.userid + ":mycreatgroup", group.groupid) != 1) // 不是群主，无权操作
        {
            cout << "权限不够，操作失败" << endl;
            group.type = NORMAL;
            group.state = FAIL;
        }
        else if (redis.sismember(group.groupid + ":admin", group.oppoid) == 1) // 对方已经是管理员了
        {
            cout << "该成员已是管理员" << endl;
            group.type = NORMAL;
            group.state = HADADMIN;
        }
        else if (redis.sismember("onlinelist", group.oppoid) == 1) // 对方在线
        {
            redis.saddvalue(group.groupid + ":admin", group.oppoid);
            redis.saddvalue(group.oppoid + ":myadmingroup", group.groupid);
            cout << "群管理添加成功" << endl;

            group.msg = "你被添加为“" + redis.gethash("groupid_name", group.groupid) + "”群的管理员";
            group.type = NOTICE;
            group.state = SUCCESS;
        }
        else // 离线
        {
            redis.saddvalue(group.groupid + ":admin", group.oppoid);
            redis.saddvalue(group.oppoid + ":myadmingroup", group.groupid);
            cout << "群管理添加成功" << endl;

            group.msg = "你被添加为“" + redis.gethash("groupid_name", group.groupid) + "”群的管理员";
            group.type = NORMAL;
            group.state = SUCCESS;

            redis.saddvalue(group.oppoid + ":unreadnotice", group.msg);
        }
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

// 删除管理员（通知被删除的管理员）
void deladmin_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Group group;
    group.groupid = parsed_data["groupid"];
    group.userid = parsed_data["userid"];
    group.oppoid = parsed_data["oppoid"];
    printf("--- %s 用户将要删除 %s 的管理员 ---\n", group.userid.c_str(), group.oppoid.c_str());

    Redis redis;
    redis.connect();

    if (redis.hashexists("userinfo", group.oppoid) != 1) // 用户不存在
    {
        cout << "该用户不存在" << endl;
        group.type = NORMAL;
        group.state = USERNAMEUNEXIST;
    }
    else if (redis.sismember(group.oppoid + ":group", group.groupid) != 1) // 对方不是群成员
    {
        cout << "该用户不在群聊中" << endl;
        group.type = NORMAL;
        group.state = NOTINGROUP;
    }
    else
    {
        if (redis.sismember(group.userid + ":mycreatgroup", group.groupid) != 1) // 不是群主，无权操作
        {
            cout << "权限不够，操作失败" << endl;
            group.type = NORMAL;
            group.state = FAIL;
        }
        else if (redis.sismember(group.groupid + ":admin", group.oppoid) != 1) // 对方不是管理员
        {
            cout << "该成员不是管理员" << endl;
            group.type = NORMAL;
            group.state = NOTADMIN;
        }
        else if (redis.sismember("onlinelist", group.oppoid) == 1) // 对方在线
        {
            redis.sremvalue(group.groupid + ":admin", group.oppoid);
            redis.sremvalue(group.oppoid + ":myadmingroup", group.groupid);
            cout << "群管理删除成功" << endl;

            group.msg = "你在“" + redis.gethash("groupid_name", group.groupid) + "”群的管理员被移除";
            group.type = NOTICE;
            group.state = SUCCESS;
        }
        else // 离线
        {
            redis.sremvalue(group.groupid + ":admin", group.oppoid);
            redis.sremvalue(group.oppoid + ":myadmingroup", group.groupid);
            cout << "群管理删除成功" << endl;

            group.msg = "你在“" + redis.gethash("groupid_name", group.groupid) + "”群的管理员被移除";
            group.type = NORMAL;
            group.state = SUCCESS;

            redis.saddvalue(group.oppoid + ":unreadnotice", group.msg);
        }
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

// 查看申请加群列表
void checkapplylist_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Group group;
    group.userid = parsed_data["userid"];
    group.groupid = parsed_data["groupid"];
    printf("--- %s 用户查看 %s 群的加群申请表 ---\n", group.userid.c_str(), group.groupid.c_str());

    Redis redis;
    redis.connect();

    vector<string> groupapply_Vector;

    if (redis.hashexists("groupid_name", group.groupid) != 1) // 群id不存在
    {
        cout << "该群id不存在" << endl;
        group.state = USERNAMEUNEXIST;
    }
    else if (redis.sismember(group.userid + ":group", group.groupid) != 1) // 未加入该群
    {
        cout << "你未加入该群！" << endl;
        group.state = FAIL;
    }
    else
    {
        if (redis.sismember(group.groupid + ":admin", group.userid) != 1) // 操作的不是管理员或群主
        {
            cout << "没有权限" << endl;
            group.state = FAIL;
        }
        else
        {
            string key = group.groupid + ":groupapply";
            int len = redis.scard(key);

            redisReply **arry = redis.smembers(key);

            // 把数据从数据库转移到容器里
            for (int i = 0; i < len; i++)
            {
                // 得到用户id
                string applyuserid = arry[i]->str;
                if (redis.hashexists("userinfo", applyuserid) != 1) // 用户id不存在，说明该用户已注销，但在该用户加入的群的数据库里仍存着（不好删）
                    continue;

                string applyusername = redis.gethash("id_name", applyuserid); // 拿着id去找name

                groupapply_Vector.push_back(applyusername);

                freeReplyObject(arry[i]);
            }
            group.state = SUCCESS;
        }
    }

    // 发送状态和信息类型
    nlohmann::json json_ = {
        {"type", NORMAL},
        {"flag", 0},
        {"state", group.state},
        {"groupapplyvector", groupapply_Vector},
    };
    string json_string = json_.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(fd, json_string);
}


// 同意加群申请(还没编辑*****)
void agreeapply_server(int fd, string buf)
{
    json parsed_data = json::parse(buf);
    struct Friend friend_;
    friend_.id = parsed_data["id"];
    string name = parsed_data["name"];
    int state = parsed_data["state"];
    printf("--- %s 用户编辑好友申请 ---\n", friend_.id.c_str());
    cout << name << endl;
    cout << state << endl;

    Redis redis;
    redis.connect();

    string key = friend_.id + ":friends_apply";

    if (redis.sismember("username", name) != 1)
    {
        cout << "查无此人" << endl;

        friend_.state = USERNAMEUNEXIST;
        friend_.type = NORMAL;
    }
    else
    {
        // 得到发送请求的用户id
        string applyfriend_id = redis.gethash("name_id", name); // 由昵称找id

        if (redis.sismember(key, applyfriend_id) != 1)
        {
            cout << "不存在此好友申请！" << endl;
            friend_.state = FAIL;
            friend_.type = NORMAL;
        }
        else if (state == 1)
        {
            cout << "已同意" << endl;
            redis.sremvalue(key, applyfriend_id); // 从申请列表中移除
            string key1 = friend_.id + ":friends";
            string key2 = applyfriend_id + ":friends";
            redis.saddvalue(key1, applyfriend_id); // 对方成为自己好友
            redis.saddvalue(key2, friend_.id);     // 自己成为对方好友

            friend_.state = SUCCESS;
            friend_.type = NORMAL;
        }
        else
        {
            cout << "已拒绝" << endl;
            redis.sremvalue(key, applyfriend_id); // 从申请列表中移除

            friend_.state = SUCCESS;
            friend_.type = NORMAL;
        }
    }

    // 发送状态和信息类型
    nlohmann::json json_ = {
        {"type", friend_.type},
        {"flag", 0},
        {"state", friend_.state},
    };
    string json_string = json_.dump();
    SendMsg sendmsg;
    sendmsg.SendMsg_client(fd, json_string);
}

#endif