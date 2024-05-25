#include <iostream>
#include <vector>
#define lld long long int

using namespace std;

lld check(lld mid, vector<lld> vec, lld n) {
    lld sum = 0, pre = 0; // pre表示选手所站的位置（石头）
    for (lld i = 0; i <= n; i++) {
        if (vec[i] - pre < mid) {// 如果所站的石头距离下一个石头的位置比mid小，那就把下一个石头移走
            sum++;
        } else {// 否则跳到下一个石头上
            pre = vec[i];
        }
    }

    return sum;
}

int main() {
    lld ll, n, m;
    cin >> ll >> n >> m;
    vector<lld> vec(n + 1);
    for (lld i = 0; i < n; i++) {
        cin >> vec[i];
    }
    vec[n] = ll;  // ll表示起点到终点的距离，那就把最后一个点也加进去

    lld l = -1, r = ll + 1;  // 跳跃距离
    while (l + 1 < r) {
        lld mid = (l + r) >> 1;
        if (check(mid, vec, n) > m) { // m为要移走的石头个数，如果check出来的个数偏多，说明剩下的石头偏少，距离偏大
            r = mid;// 所以应该少移一些石头，让mid减小
        } else {
            l = mid;
        }
    }

    cout << l;

    return 0;
}
