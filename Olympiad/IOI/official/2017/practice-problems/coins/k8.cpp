#include <bits/stdc++.h>
#include "coins.h"
using namespace std;
vector<int> coin_flips(vector<int> a, int x){
	vector<int> ans;
	ans.push_back(63);
	for(int i = 0; i < 6; ++ i){
		int bit = (x >> i) & 1;
		if(bit != a[i])
			ans.push_back(i);
	}
	return ans;
}
int find_coin(vector<int> a){
	int ans = 0;
	for(int i = 0; i < 6; ++ i)
		if(a[i])
			ans ^= (1 << i);
	return ans;
}
