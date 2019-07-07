#include <bits/stdc++.h>
#include "coins.h"
using namespace std;
vector<int> coin_flips(vector<int> a, int x){
	vector<int> ans;
	if(!a[x])
		ans.push_back(x);
	for(int i = 0; i < 64; ++ i)
		if(x != i && a[i])
			ans.push_back(i);
	if(ans.empty()){
		ans.push_back(x);
		ans.push_back(x);
	}
	return ans;
}
int find_coin(vector<int> a){
	for(int i = 0; i < 64; ++ i)
		if(a[i])	return i;
	return -1;
}
