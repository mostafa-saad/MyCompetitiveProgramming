#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	long long ans = 0;
	int n, m, k, orik;
	cin >> n >> m >> k;
	orik = k;
	
	vector<int> a(n);
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		ans += (a[i]/m)*m;
		k -= a[i]/m;
		a[i] = a[i]%m;
		
	}
	
	if(k <= 0){
		ans = ((long long)(orik)) * ((long long)(m));
		cout << ans << endl;
		return 0;
	}
	
	sort(a.begin(), a.end(), greater<int> () );
	
	for(int i = 0; i < min(n, k); i++){
		ans += a[i];
	}
	
	cout << ans << endl;
}