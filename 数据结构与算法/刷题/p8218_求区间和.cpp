#include<iostream>
#include<vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> vec(n+1);
    vec[0] = 0;
    for(int i=1;i<=n;i++){// 下标从1开始
        cin >> vec[i];
        vec[i] += vec[i-1];
    }
    int m;
    cin >> m;
    
    while(m--){
        int l,r;
        cin >> l >> r;
        cout << vec[r] - vec[l-1]  <<  endl;
    }


    return 0;
}