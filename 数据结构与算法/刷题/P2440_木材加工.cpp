#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long int check(long long int mid,
                    vector<long long int> vec,
                    long long int n) {
    long long int sum = 0;
    for(int i=0;i<n;i++){
        sum+=vec[i]/mid;
    }
    return sum;
}

int main() {
    long long int n, k;
    cin >> n >> k;
    vector<long long int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    long long int l = 0, r = 100000000;  // 木条长度
    while (l + 1 < r) {
        long long int mid = (l + r) >> 1;
        if (check(mid, vec, n) >= k) {//check返回值>=k,说明切的太多段了，这样每段偏小-->应该让每段长一些-->左指针右移(l = mid)
            l = mid;
        } else {
            r = mid;
        }
    }
    if (l < 1)
        cout << 0;
    else
        cout << l;
    return 0;
}