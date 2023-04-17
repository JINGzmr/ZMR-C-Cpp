#include <iostream>
using namespace std;

namespace KingGlory
{
    int sun = 1;
}

namespace LOL
{
    int sun = 3;
}

void test01()
{
    int sun = 2;

    // using声明  
    using KingGlory::sun;

    // 当using声明与就近原则同时出现时，会报错"‘int KingGlory::sun’ conflicts with a previous declaration"
    cout << sun << endl;

    /*
    //使用作用域限定符
    cout << KingGlory::sun << endl;
    如果只写这句话，则打印出KingGlory里的值

    cout << sun << endl;
    如果只写这句话，则打印出本函数里定义的值（就近原则）
    */
}

void test02()
{
    // int sun =2; 有它，打印为2,反之为1

    // 2.using编译指令 
    using namespace KingGlory;
    /*using namespace LOL;再加上这就话，且没有第一句的sun=2时，会报错*/

    // 当using编译指令 与 就近原则同时出现，优先使用 就近
    // 当using编译指令有多个，需要加作用域 区分
    cout << sun << endl;
}

int main()
{
    // test01();
    test02();

    system("pause");
    return 0;
}