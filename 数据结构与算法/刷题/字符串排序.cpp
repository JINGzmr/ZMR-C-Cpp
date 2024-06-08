#include <bits/stdc++.h>
using namespace std;

bool cmp(const pair<int, string>& pa, const pair<int, string>& pb) {
    return pa.first < pb.first;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        vector<pair<int, string>> vec;
        string str = "\n";
        getline(cin, str);
        while (n--) {
            getline(cin, str);
            if (str == "stop")
                break;
            vec.push_back({str.size(), str});
        }
        stable_sort(
            vec.begin(), vec.end(),
            cmp);  // 要用stable_sort，在比较内容相同时，能保证相对位置不变
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i].second << endl;
        }
    }

    return 0;
}
