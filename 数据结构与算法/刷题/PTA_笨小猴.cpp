#include <bits/stdc++.h>
using namespace std;

int func(int x) {
    int y = sqrt(x);
    if (x <= 1)
        return 0;  // 不是质数
    for (int i = 2; i <= y; i++) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    string str;
    cin >> str;
    int a[1000] = {0};
    for (int i = 0; i < str.size(); i++) {
        a[str[i] - 'a']++;
    }
    int max = 0, min = 100000;
    for (int i = 0; i < 1000; i++) {
        if (a[i] == 0)
            continue;
        if (a[i] > max)
            max = a[i];
        if (a[i] < min)
            min = a[i];
    }

    if (func(max - min) == 1) {
        cout << "Lucky Word" << endl;
        cout << max - min;
    } else {
        cout << "No Answer" << endl;
        cout << 0;
    }

    return 0;
}