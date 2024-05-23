#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#define lld long long int
using namespace std;

lld check(lld mid, vector<lld>vec, lld n){
    lld pre = vec[0];// 先设置第一个数字，接下来需要找>=mid长度的区间，pre为区间的左坐标
    lld sum = 0;// 记录满足的区间个数，最后牛牛的个数比区间个数多1
    for(lld i=0;i<n;i++){// 从区间的左坐标pre对应的数组下标0开始向右找区间
        if(vec[i]-pre >= mid){// 该区间满足
            sum++;
            pre = vec[i];
        }
    }    

    return sum+1;
}

int main(){
    lld n,c;
    cin >> n >> c;
    vector<lld> vec(n);
    for(lld i=0;i<n;i++){
        cin >> vec[i];
    }

    sort(vec.begin(),vec.end());

    lld l = -1,r = vec[n-1]-vec[0]+1;// 相邻两头牛的距离区间
    while(l+1<r){
        lld mid = (l+r) >> 1;
        if(check(mid,vec,n) >= c){// 如果check出来的牛比要求的多，说明牛牛相隔太近了，所以mid应该大一些，即l右移
            l = mid;
        }else{
            r = mid;
        }
    }

    cout << l;


    return 0;
}