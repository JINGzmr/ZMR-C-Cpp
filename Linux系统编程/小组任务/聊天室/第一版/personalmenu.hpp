#include "data.h"
#include "define.h"
#include "head.h"
#include "IO.h"

#include <iostream>

void messagemenu()
{
    cout << "————————————————————————————————————————————————————" << endl;
    cout << "|---------------------  聊天室  --------------------|" << endl;
    cout << "|——————————————————————————————————————————————————|" << endl;
    cout << "|                      4.私聊                       |" << endl;
    cout << "|                      5.查看好友申请                |" << endl;
    cout << "|                      6.加好友                     |" << endl;
    cout << "|                      7.查看历史聊天记录             |" << endl;
    cout << "|                      8.查询好友信息                |" << endl;
    cout << "|                      9.查看好友列表                |" << endl;
    cout << "|                      10.删除好友                   |" << endl;
    cout << "|                      11.群聊                      |" << endl;
    cout << "|                      12拉入黑名单                  |" << endl;
    cout << "|                      13.拉出黑名单                 |" << endl;
    cout << "|                      14.发送文件                   |" << endl;
    cout << "|                      15.接受文件                   |" << endl;
    cout << "|                      16.返回上一页                 |" << endl;
    cout << "————————————————————————————————————————————————————" << endl;


    int num;
    cin >> num;

    while(1){
        switch (num)
        {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        default:
            cout << "无效的数字，请重新输入！" << endl;
        }
    }
}