#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    int n, r;
    cin >> n >> r;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        vec.push_back(x);
    }
    if (r * 2 > n) {
        for (int i = 0; i < n; i++) {
            cout << vec[i];
            if (i < n - 1)
                cout << " ";
        }
    } else {
        sort(vec.begin() + r, vec.end() - r);
        for (int i = 0; i < n; i++) {
            cout << vec[i];
            if (i < n - 1)
                cout << " ";
        }
    }

    return 0;
}