#include <bits/stdc++.h>
#include "coins.h"
using namespace std;
int d[3][4] = {{0, 1, 14, 15}, {2, 3, 12, 13}, {4, 5, 10, 11}};
vector<int> coin_flips(vector<int> a, int x){
	int w = 0;
	for(int i = 0; i < 4; ++ i)
		w = (w << 1) | a[i];
	int fnd = -1;
	for(int i = 0; i < 4; ++ i)
		if(__builtin_popcount(d[x][i] ^ w) == 1){
			fnd = d[x][i];
			break ;
		}
	int co[] = {8, 4, 2, 1};
	vector<int> ans;
	for(int i = 0; i < 4; ++ i)
		if(bool((fnd & (co[i]))) != a[i])
			ans.push_back(i);
	assert((int)ans.size() == 1);
	return ans;
}
int find_coin(vector<int> a){
	int w = 0;
	for(int i = 0; i < 4; ++ i)
		w = (w << 1) | a[i];
	for(int i = 0; i < 3; ++ i)
		for(int j = 0; j < 4; ++ j)
			if(d[i][j] == w)
				return i;
	return -1;
}
