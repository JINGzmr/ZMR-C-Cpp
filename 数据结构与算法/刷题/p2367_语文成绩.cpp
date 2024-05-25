#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> vec(n + 1, 0), diff(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> vec[i];
    }

    // 求差分数组
    for (int i = 1; i <= n; i++) {
        diff[i] = vec[i] - vec[i - 1];
    }

    while (p--) {
        int x, y, z;
        cin >> x >> y >> z;
        diff[x] += z;
        diff[y+1] -= z;
    }

    // 求修改后的原数组
    int min = 100000000;
    for(int i=1;i<=n;i++){
        vec[i] = vec[i-1] + diff[i];
        if(vec[i]<min)
            min = vec[i];
    }

    cout << min;

    return 0;
}