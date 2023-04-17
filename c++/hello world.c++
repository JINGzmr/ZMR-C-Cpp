#include <iostream>  //i-input输入  o-output输出  stream流
using namespace std; // 使用 标准 命名空间

int main()
{
    //cout标准的输出对象 ，将输出发送到标准输出设备（一般是控制台窗口）

    /* << 左移运算符   c++里：用于在cout后拼接输出的内容
       （插入运算符 << 的左侧通常是一个输出流对象（例如 std::cout），右侧是要插入到输出流中的数据） */

    /* endl : end line 刷新缓冲区，并且换行
        （在输出流中插入一个换行副，并刷新输出缓冲区，以确保输出被立即发送到标准输出设备中）*/

    cout << "hello world"; 
    cout << "hello world" << endl; 

    system("pause");
    return 0; // return EXIT_SUCCESS
}


