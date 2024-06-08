#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int cnt = 1;
    while (n) {
        cout << "SET " << cnt++ << endl;
        string str;
        vector<string> vec;
        for (int i = 1; i <= n; i++) {
            cin >> str;
            if (i % 2 != 0) {  // 奇数直接输出
                cout << str << endl;
            } else {
                vec.push_back(str);
            }
        }
        while (!vec.empty()) {
            cout << vec.back() << endl;
            vec.pop_back();
        }

        cin >> n;
    }

    return 0;
}
