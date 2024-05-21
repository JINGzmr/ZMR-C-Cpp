#include <iostream>
#include <string>
using namespace std;

int main() {
    long long int a, b, n;
    long long int sum = 0;
    cin >> a >> b >> n;
    long long int i;
    int flag = 0;
    for (i = 1; i <= 7; i++) {
        if (i % 6 == 0 || i % 7 == 0)  // 周末
        {
            sum += b;
        } else {
            sum += a;
        }
        if (sum >= n) {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        cout << i;
    else {
         long long int x = n / sum;
        sum *= x;
        long long int j;
        for (j = 1; sum < n; j++) {
            if (j % 6 == 0 || j % 7 == 0)  // 周末
            {
                sum += b;
            } else {
                sum += a;
            }
        }

        cout << 7 * x + j - 1;
    }
}