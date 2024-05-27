#include <iostream>
#include <vector>
#define lld long long
using namespace std;

lld check(lld mid, vector<vector<lld>> vec, vector<vector<lld>> vec_lr, lld n) {
    lld sum_y = 0;

    /* 最初for嵌套代码
    for (lld i = 1; i < vec_lr.size(); i++) {
        lld l = vec_lr[i][1];
        lld r = vec_lr[i][2];
        lld sum1 = 0, sum2 = 0;
        for (lld j = l; j <= r; j++) {
            if (vec[j][1] >= mid) {
                sum1++;
                sum2 += vec[j][2];
            }
        }
        sum_y += sum1 * sum2;
    }*/
    
    // 前缀和优化
    vector<vector<lld>> add(n + 1, vector<lld>(3, 0));
    for (lld i = 1; i < vec.size(); i++) {
        if (vec[i][1] >= mid) {
            add[i][1] =add[i - 1][1] + 1;  // add第一列为符合标准的矿石数量的前缀和，表示这个矿石符合标准，符合标准的矿石数++
            add[i][2] = add[i - 1][2] + vec[i][2];  // add第二列为符合标准的矿石对应价值的前缀和
        } else {
            add[i][1] = add[i - 1][1];
            add[i][2] = add[i - 1][2];
        }
    }
    for (lld i = 1; i < vec_lr.size(); i++) {
        lld l = vec_lr[i][1];
        lld r = vec_lr[i][2];
        sum_y += (add[r][1] - add[l - 1][1]) * (add[r][2] - add[l - 1][2]);
    }

    return sum_y;
}

int main() {
    lld n, m, s;
    cin >> n >> m >> s;
    vector<vector<lld>> vec(n + 1, vector<lld>(3, 0)),
        vec_lr(m + 1, vector<lld>(3, 0));
    lld max = 0;
    for (lld i = 1; i <= n; i++) {
        for (lld j = 1; j <= 2; j++) {
            cin >> vec[i][j];
            if (j == 2 && vec[i][j] > max) {
                max = vec[i][j];
            }
        }
    }
    for (lld i = 1; i <= m; i++) {
        for (lld j = 1; j <= 2; j++) {
            cin >> vec_lr[i][j];
        }
    }

    lld l = 0, r = max + 1;    // w的范围
    lld ans = 100000000000000000;  // 得开这么大！！！
    while (l + 1 < r) {
        lld mid = (l + r) >> 1;
        lld return_y = check(mid, vec, vec_lr, n);
        if (return_y > s) {
            if (return_y - s < ans)
                ans = return_y - s;
            l = mid;
        } else {
            if (s - return_y < ans)
                ans = s - return_y;
            r = mid;
        }
    }

    cout << min(ans, min(llabs(check(r, vec, vec_lr, n) - s),
                         llabs(check(l, vec, vec_lr, n) - s)));

    return 0;
}