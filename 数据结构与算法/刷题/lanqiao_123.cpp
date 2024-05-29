// bug
#include<iostream>
#include<vector>
#include<cmath>
#define lld long long
using namespace std;

int main()
{
  lld t;
  cin >> t;
  // vector<vector<lld>> vec(t+1,vector<lld>(3,0));
  lld n = 100000000;
  vector<lld> add(n+10,0);
  add[1] = 1;
  lld x = 2, xx = 1;
  for(int i=2;i<n;i++){
    add[i]+=add[i-1]+xx;
    xx++;
    if(xx-1==x){
      xx = 1;
      x++;
    }
  }
  while(t--){
    lld l,r;
    cin >> l >> r;
    cout << add[r] - add[l-1] << endl;
  }

  return 0;
}