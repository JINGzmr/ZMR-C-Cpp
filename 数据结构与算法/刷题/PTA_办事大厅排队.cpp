#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    list<string> l;
    while (n--) {
        string str;
        cin >> str;
        if (str == "in") {
            cin >> str;
            l.push_back(str);
        } else if (str == "out") {
            l.pop_front();
        } else if (str == "q") {
            if (!l.empty())
                cout << l.front() << endl;
            else
                cout << "NULL" << endl;
        }
    }

    return 0;
}