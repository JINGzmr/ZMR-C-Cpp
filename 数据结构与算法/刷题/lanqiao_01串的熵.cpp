#include <bits/stdc++.h>
using namespace std;

int main() {
    double n = 23333333;
    double h = 0;
    for (int i = 0; i < n / 2; i++) {
        h = 0;
        h -= i * (i / n) * log2(i / n) +
             (n - i) * ((n - i) / n) * log2((n - i) / n);
        if (h > 11625907.5 && h < 11625907.6) {
            printf("%d",i);
            break;
        }
    }

    return 0;
}