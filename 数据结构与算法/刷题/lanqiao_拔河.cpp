//bug
#include<iostream>
#include<vector>
#include<cmath>
#define lld long long
using namespace std;
 
lld check(vector<lld> vec, lld mid, lld sum, vector<lld> ff){
    return sum-ff[mid]*2;
}
 
int main()
{
    lld n;
    cin >> n;
    vector<lld> vec(n+1);
    lld sum = 0;
    vector<lld> ff(n+1,0);
    for(int i=1;i<=n;i++){
        cin >> vec[i];
        sum+=vec[i];
        ff[i] = ff[i-1] + vec[i];
    }

    lld l = 0,r = n+1;
    while(l+1<r){
        lld mid = (l+r)>>1;
        if(check(vec,mid,sum,ff)>0){
            l = mid;
        }else{
            r = mid;
        }
    }
 
    cout << min(abs(check(vec,l,sum,ff)),abs(check(vec,r,sum,ff)));
     
    return 0;
}