#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> vec;
    int n;
    // 以输入一个非数字的值作为输入结束标志!!!!!!!!!!!!
    while (cin >> n) {
        vec.push_back(n);
    }
    sort(vec.begin(), vec.end());
    cout << "从标准设备读入数据，直到输入是非整型数据为止" << endl;
    for (int i = 0; i < vec.size(); i++) {
        cout << " " << vec[i];
    }

    return 0;
}