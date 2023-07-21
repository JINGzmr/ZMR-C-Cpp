#include "IO.h"

// 客户端发送序列化好的数据
void SendMsg::SendMsg_fun(int client_socket, const std::string &userJson_string)
{
    if (send(client_socket, userJson_string.c_str(), userJson_string.size(), 0) == -1)
    {
        std::cerr << "Send failed" << std::endl;
    }
    else
    {
        std::cout << "Data sent to the server" << std::endl;
    }
}