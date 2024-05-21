#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    priority_queue<pair<long long, int>> vec;
    int n, sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long h;
        cin >> h;
        if (h != 1) {  // 把高度不为1的竹子放到要砍的优先队列里
            vec.push({h, i});
        }
    }

    while (!vec.empty()) {
        pair<long long, int> top = vec.top();
        vec.pop();
        long long new_h = floor(sqrtl(floor(top.first * 1.0 / 2) + 1.0));
        if (new_h != 1) {
            vec.push({new_h, top.second});
        }

        int cont = 1;
        while (!vec.empty() && vec.top().first == top.first &&
               vec.top().second == top.second - cont) {
            pair<long long, int> topp = vec.top();
            vec.pop();
            if (new_h != 1) {
                vec.push({new_h, topp.second});
            }
            cont++;
        }
        sum++;
    }
    cout << sum;

    return 0;
}