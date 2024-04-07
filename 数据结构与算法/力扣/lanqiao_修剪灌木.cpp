#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i <= n / 2; i++) {
        if (n % 2 == 0 && i == n / 2)
            continue;
        cout << (n - 1) * 2 - i * 2 << endl;
    }
    for (int i = 1; i <= n / 2; i++) {
        cout << (n - 1) * 2 + i * 2 - n / 2 * 2 << endl;
    }

    return 0;
}