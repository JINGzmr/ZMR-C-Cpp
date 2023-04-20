#include <iostream>
using namespace std;

int fun(int a , int b = 20 , int c = 30)
{
return a+b+c;
}

int main()
{
// fun();//
fun(10);
fun(10,10);
cout << fun(10) << fun(10,10) <<endl;
}