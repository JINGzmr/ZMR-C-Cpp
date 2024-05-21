#include <iostream>
#include <math.h>
using namespace std;
int main() {
    string str = "2022";
    int len = str.length();
    long long int a = 0;
    for (int i = 0; i < len; i++) {
        a += (str[i] - '0') * pow(9,(len - 1 - i));
    }
    cout << a;

    return 0;
}