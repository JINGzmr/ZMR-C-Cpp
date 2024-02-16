#include <iostream>
using namespace std;

int add(int a, int b);

int main()
{
    int a, b;
    cin >> a >> b;

    int *ptr = &a;
    int c, sum = 0;
    c = add(a, b);

    for (int i = 0; i < c; i++)
    {
        sum += i;
    }

    cout << sum << endl;

    return 0;
}

int add(int a, int b)
{
    return a + b;
}
