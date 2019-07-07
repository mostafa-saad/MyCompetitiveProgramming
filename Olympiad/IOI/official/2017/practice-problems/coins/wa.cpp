#include <bits/stdc++.h>
#include "coins.h"
using namespace std;
vector<int> coin_flips(vector<int> a, int x){
	int y = 0;
	for(int i = 0; i < 64; ++ i)
		y = (y + a[i] * i) % 64;
	int ted = (x - y + 64) % 64;
	vector<int> ans;
	if(!a[ted])
		ans.push_back(ted);
	else
		ans.push_back((64-ted)%64);
	if(ans.empty()){
		ans.push_back(x);
		ans.push_back(x);
	}
	return ans;
}
int find_coin(vector<int> a){
	int x = 0;
	for(int i = 0; i < 64; ++ i)
		x = (x + a[i] * i) % 64;
	return x;
}
