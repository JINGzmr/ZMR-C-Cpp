#include <iostream>
using namespace std;

int atk = 1000;

void test01()
{
    int atk = 2000;
    cout << "atk = " << atk << endl;

    //::代表作用域  如果前面什么都不加，则代表全局作用域
    cout << "atk = " << ::atk << endl;
}

int main()
{
    test01();

    system("pause");
    return 0;
}