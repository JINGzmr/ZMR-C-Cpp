// 几个类，用于打包实现SendMsg（）和RecvMsg（）
#ifndef IO_H
#define IO_H

#include "head.h"
#include <iostream>

using namespace std;

class SendMsg
{
public:
    static void SendMsg_client(int client_socket, const std::string &str);
};

class RecvMsg
{
public:
    static void RecvMsg_client(int client_socket, std::string &str,int epld);
};

#endif
