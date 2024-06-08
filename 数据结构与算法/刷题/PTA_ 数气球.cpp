// #include<bits/stdc++.h>
// using namespace std;

// int main()
// {
//     int t;
//     cin >> t;
//     while(t--){
//         int n;
//         cin >> n;
//         // unordered_map<string,int> m;
//         map<string,int> m;
//         for(int i=0;i<n;i++){
//             string str;
//             cin >> str;
//             m[str]++;
//         }
//         for(auto it = m.begin();it!=m.end();it++)
//             cout << it->first << " " << it->second << endl;
//     }

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<string, int>
            colorCount;  // 单独map会将元素自动排序，需要拿vector记录元素出现的顺序
        vector<string> order;

        for (int i = 0; i < n; i++) {
            string color;
            cin >> color;
            if (colorCount[color] == 0) {  // 如果map里没有，说明第一次出现
                order.push_back(color);  // 插进去
            }
            colorCount[color]++;  // 该颜色出现次数++
        }

        for (int i = 0; i < order.size(); i++) {
            cout << order[i] << " " << colorCount[order[i]] << endl;
        }
    }

    return 0;
}
