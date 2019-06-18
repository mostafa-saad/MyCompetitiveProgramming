#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct idx{
	int x, y, prev;
}tmp[20005];

int n, t;
int x[20005], y[20005];
int conv1[20005], conv2[20005];
int lab[20005];
vector<int> vx, vy;

void input(){
	scanf("%d %d",&n, &t);
	for(int i=0; i<n; i++){
		scanf("%d %d",&x[i],&y[i]);
		vx.push_back(x[i]);
		vy.push_back(y[i]);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	for(int i=0; i<n; i++){
		x[i] = (int)(lower_bound(vx.begin(), vx.end(), x[i]) - vx.begin());
		y[i] = (int)(lower_bound(vy.begin(), vy.end(), y[i]) - vy.begin());
		tmp[i] = {x[i], y[i], i+1};
	}
	sort(tmp, tmp + n, [&](const idx &a, const idx &b){
		return a.x < b.x;
	});
	for(int i=0; i<n; i++){
		y[i] = tmp[i].y;
		lab[i] = tmp[i].prev;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(y[j] > y[i]) conv1[i]++;
			if(y[j] < y[i]) conv2[i]++;
		}
	}
}

int main(){
	input();
	int minp = 1e9, minx = -1, miny = -1;
	for(int i=0; i<n; i++){
		int under[20005] = {};
		for(int j=0; j<i; j++){
			under[y[j]]++;
		}
		for(int j=1; j<=n; j++){
			under[j] += under[j-1];
		}
		int left = 0;
		for(int j=i+1; j<n; j++){
			if(y[j] < y[i]){
				left++;
				continue;
			}
			int tmp = j + 1 - left - conv1[j] - under[y[j]];
			if(minp > tmp && tmp >= t){
				minp = tmp;
				minx = i, miny = j;
			}
			if(minp == t) break;
		}
		left = 0;
		for(int j=i+1; j<n; j++){
			if(y[j] > y[i]){
				left++;
				continue;
			}
			int tmp = j + 1 - left - conv2[j] - under[n] + under[y[j]];
			if(minp > tmp && tmp >= t){
				minp = tmp;
				minx = i, miny = j;
			}
			if(minp == t) break;
		}		
		if(minp == t) break;
	}
	printf("%d %d",lab[minx], lab[miny]);
}
