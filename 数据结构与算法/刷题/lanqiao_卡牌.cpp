#include <iostream>
#include <vector>
#define lld long long
using namespace std;

lld check(lld mid, vector<lld> kapai, vector<lld> kongpai, lld n) {
    lld sum = 0;  // 空牌数
    for (lld i = 0; i < n; i++) {
        if (kapai[i] + kongpai[i] >= mid) {
            sum += (mid - kapai[i]);  // 表示要补的卡牌数
        } else {
            return -1;  // 第i种牌都不够mid的数量，说明mid套牌肯定凑不齐
        }
    }

    return sum;
}

int main() {
    lld n, m;
    cin >> n >> m;
    vector<lld> kapai(n);
    vector<lld> kongpai(n);
    lld max = 0;
    for (lld i = 0; i < n; i++) {
        cin >> kapai[i];
        if (kapai[i] > max)
            max = kapai[i];
    }

    for (lld i = 0; i < n; i++) {
        cin >> kongpai[i];
    }

    lld l = -1, r = max + 1;// 能得到的套牌的套数
    while (l + 1 < r) {
        lld mid = (l + r) >> 1;
        lld return_kongpai = check(mid, kapai, kongpai, n);
        if (return_kongpai >= m || return_kongpai == -1) { // m为提供空牌数
                                                           // 如果check的结果比给的空牌多，说明能组成的套牌过多了
                                                           // 所以套牌应该减少，即mid减少
            r = mid;// 让套牌的右区间往左移动
        } else {
            l = mid;
        }
    }

    cout << l;

    return 0;
}