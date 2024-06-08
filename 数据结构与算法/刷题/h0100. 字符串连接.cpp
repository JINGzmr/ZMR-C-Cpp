#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int cnt = 1;
    while (n--) {
        int a, b;
        cin >> a >> b;
        // cout << a << "-- "  << b << endl;
        int sum = a * b;
        vector<string> v1, v2;
        for (int i = 1; i <= a + b; i++) {
            string str;
            cin >> str;
            if (i <= a) {
                v1.push_back(str);
            } else {
                v2.push_back(str);
            }
        }
        cout << "Case " << cnt++ << ": " << sum << endl;
    }

    return 0;
}