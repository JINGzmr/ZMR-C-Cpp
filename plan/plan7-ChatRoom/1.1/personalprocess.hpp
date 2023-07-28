// 服务器对客户端personalmenu里不同的选项进行不同的处理
#ifndef PERSONALPROCESS_HPP
#define PERSONALPROCESS_HPP

#include "data.h"
#include "define.h"
#include "IO.h"
#include "redis.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

// 退出登录
void logout_server(string buf)
{
    json parsed_data = json::parse(buf);
    string username = parsed_data["username"];
    printf("--- %s 用户将要退出登录 ---\n", username.c_str());

    Redis redis;
    redis.connect();

    string userjson_string;
    userjson_string = redis.gethash("userinfo", username);
    parsed_data = json::parse(userjson_string);

    // 改变用户的在线状态
    parsed_data["online"] = OFFLINE;
    userjson_string = parsed_data.dump();
    redis.hsetValue("userinfo", username, userjson_string);

    cout << "退出登录成功" << endl;
}

#endif