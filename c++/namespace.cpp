#include <iostream>
using namespace std;

// 1.命名空间用途：解决名称冲突
void test01()
{
    // KingGlory::goAtk();没写具体的，取消注释会报错

    // LOL::goAtk();
}

// 2.命名空间下可以存放的东西：变量、函数、结构体、类...
namespace A
{
    int a;
    void func();
    struct ddd
    {
    };
    class sss
    { // 类
    };
}

// 3.命名空间必须要声明在全局作用域
void test02()
{
    // namespace B{}; 不可以命名到局部作用域
}

// 4. 命名空间可以嵌套命名空间
namespace B
{
    int m_A = 10;
    namespace C
    {
        int m_A = 20;
    }
}
void test03()
{
    cout << "B空间下的A= " << B::m_A << endl;    // 10
    cout << "C空间下的A= " << B::C::m_A << endl; // 20
}

// 5.命名空间是开放的，可以随时将新成员添加到命名空间下
namespace B // 上面写过一次B了
{
    int m_B = 100;
}
void test03()
{
    cout << "B空间下的A= " << B::m_A << endl; // 10  ->说明之前命名空间B里的东西没有被后来的给覆盖掉，而是进行了追加
    cout << "B空间下的A= " << B::m_B << endl; // 100
}

// 6.命名空间可以是匿名的  相当于写了static int m_C = 1000; static int m_D = 2000;
namespace
{
    int m_C = 1000;
    int m_D = 2000;
}
void test05()
{
    cout << "m_C = " << m_C << endl; // 就是全局作用域啦
    cout << "m_D = " << ::m_D << endl;
}

// 7.命名空间可以起别名
namespace aaa
{
    int m_E = 1000;
}
void test06()
{
    namespace bbb = aaa;
    cout << bbb ::m_E << endl; //1000
    cout << aaa ::m_E << endl; //1000 
}