#include <bits/stdc++.h>
#include "coins.h"
using namespace std;
bool ini = false;
int w[64];
inline void init(){
	if(ini)	return ;
	ini = true;
	for(int i = 0; i < 64; ++ i)	w[i] = i;
	srand(858585);
	random_shuffle(w, w + 64);
}
vector<int> coin_flips(vector<int> a, int x){
	init();
	int y = 0;
	for(int i = 0; i < 64; ++ i)
		y = (y + a[i] * w[i]) % 64;
	int ted = (x - y + 64) % 64;
	vector<int> ans;
	for(int i = 0; i < 64; ++ i)
		if(((y - a[i] * w[i] + !a[i] * w[i] + 128) % 64) == x){
			ans.push_back(i);
			break ;
		}
	if(ans.empty()){
		ans.push_back(x);
		ans.push_back(x);
	}
	return ans;
}
int find_coin(vector<int> a){
	init();
	int x = 0;
	for(int i = 0; i < 64; ++ i)
		x = (x + a[i] * w[i]) % 64;
	return x;
}
