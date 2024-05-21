#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int n,m;
	cin >> n >>m;
	vector<int > vec(n);
	for(int i=0;i<n;i++){
		cin >> vec[i];
	} 
	while(m--){
		int x;
		cin >>x;
		
		int l = -1, r = n;
		while(r>l+1){
			int mid = (r+l)/2;
			if(vec[mid]>=x){
				r = mid;
			}else{
				l = mid;
			}
		}
		if(vec[r]==x)cout << r+1 << " ";
		else cout << -1 <<" ";
	}
	
	
	return 0;
}