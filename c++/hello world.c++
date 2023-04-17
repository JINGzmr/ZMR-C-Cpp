#include <iostream>  //i-input输入  o-output输出  stream流
using namespace std; // 使用 标准 命名空间

int main()
{
    cout << "hello world"; //cout标准的输出对象 ，将输出发送到标准输出设备（一般是控制台窗口）
    cout << "hello world" << endl; // endl是换行（在输出流中插入一个换行副，并刷新输出缓冲区，以确保输出被立即发送到标准输出设备中

    system("pause");
    return 0; // return EXIT_SUCCESS
}
