#include <iostream>
using namespace std;

int global_var = 10;

int& get_local_reference() {
    int local_var = 20;
    // 不要返回局部变量的引用
    // 这里返回的引用实际上指向了已经被销毁的内存空间
    return local_var;
}

int& get_global_reference() {
    // 返回全局变量的引用是安全的
    return global_var;
}

int& static_local_reference(){
    static int a = 10;
    return a;
}


int main() {

    int& ref = get_local_reference();
    // 因为 get_local_reference() 返回的是一个已经被销毁的内存空间的引用
    // 所以这里的操作是未定义的行为





    // 函数调用可以作为左值
     int& ref2 = get_global_reference();
    int& a = static_local_reference();
    ref2 = 40;
    static_local_reference() = 666;
    cout << global_var << endl << a << endl; // 输出 40  666
        cout << ref2 << endl ;

    return 0;
}