// bug
#include <iostream>
#include <vector>
#define lld long long
using namespace std;

lld check1(lld mid, vector<vector<lld>> vec, lld n) {
    for (int i = 1; i < n; i++) {
        if (vec[i][1] / mid > vec[i][2])
            return 1;
    }
    return 0;
}

lld check2(lld mid, vector<vector<lld>> vec, lld n) {
    for (int i = 1; i < n; i++) {
        if (vec[i][1] / mid >= vec[i][2])
            return 1;
    }
    return 0;
}


int main() {
    lld n, max = 0;
    cin >> n;
    vector<vector<lld>> vec(n + 1, vector<lld>(3, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 2; j++) {
            cin >> vec[i][j];
            if (vec[i][1] > max)
                max = vec[i][1];
        }
    }
    lld ll, rr;
    lld l = 0, r = max + 1;
    while (l + 1 < r) {
        lld mid = (l + r) >> 1;
        if (check1(mid, vec, n)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    ll = r + 1;
    l = 0, r = max + 1;
    while (l + 1 < r) {
        lld mid = (l + r) >> 1;
        if (check2(mid, vec, n)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    rr = l-1;
    cout << ll << " " << rr;

    return 0;
}