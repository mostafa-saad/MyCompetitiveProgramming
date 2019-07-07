#include <bits/stdc++.h>
#include "coins.h"
using namespace std;
vector<int> coin_flips(vector<int> a, int x){
	if(!x){
		if(a[0])
			return vector<int>({0});
		else
			return vector<int>({63});
	}
	if(!a[0])
		return vector<int>({0});
	else
		return vector<int>({63});
}
int find_coin(vector<int> a){
	return a[0];
}
