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
const int mod = 1234567891;

struct points{
	int x, y, c, i;
};

int ccw(points a, points b, points c){
	return 1ll * (b.x - a.x) * (c.y - a.y) > 1ll * (b.y - a.y) * (c.x - a.x);
}

bool inside(points p1, points p2, points p3, points x){
	int t = ccw(p1, p2, x) + ccw(p2, p3, x) + ccw(p3, p1, x);
	return t == 0 || t == 3;
}

void solve(points p1, points p2, points p3, vector<points> v){
	// p3 have different color.
	int pivi = -1;
	for(int i=0; i<v.size(); i++){
		if(v[i].c == p3.c){
			pivi = i;
			break;
		}
	}
	if(pivi != -1){
		printf("%d %d %c\n",p3.i, v[pivi].i, p3.c);
		vector<points> v1, v2, v3;
		for(int i=0; i<v.size(); i++){
			if(i == pivi) continue;
			if(inside(p1, p2, v[pivi], v[i])){
				v1.push_back(v[i]);
			}
			if(inside(p1, p3, v[pivi], v[i])){
				v2.push_back(v[i]);
			}
			if(inside(p2, p3, v[pivi], v[i])){
				v3.push_back(v[i]);
			}
		}
		solve(p1, p2, v[pivi], v1);
		solve(p3, v[pivi], p1, v2);
		solve(p3, v[pivi], p2, v3);
		return;
	}
	sort(v.begin(), v.end(), [&](const points &a, const points &b){
		return ccw(p1, a, b);
	});
	for(auto &i : v){
		printf("%d %d %c\n",i.i, p1.i, p1.c);
	}
}

int main(){
	int r, g;
	scanf("%d",&r);
	vector<points> v;
	points p1, p2, p3, p4;
	for(int i=0; i<r; i++){
		points p;
		p.c = 'g', p.i = i + 1;
		scanf("%d %d",&p.x,&p.y);
		if(i == 0) p1 = p;
		if(i == 1) p2 = p;
		if(i >= 2) v.push_back(p);
	}
	scanf("%d",&g);
	for(int i=0; i<g; i++){
		points p;
		p.c = 'r', p.i = i + 1;
		scanf("%d %d",&p.x,&p.y);
		if(i == 0) p3 = p;
		if(i == 1) p4 = p;
		if(i >= 2) v.push_back(p);
	}
	random_shuffle(v.begin(), v.end());
	printf("1 2 g\n1 2 r\n");
	vector<points> v1, v2;
	for(auto &i : v){
		if(inside(p1, p2, p3, i)) v1.push_back(i);
		else v2.push_back(i);
	}
	solve(p1, p2, p3, v1);
	solve(p3, p4, p2, v2);
}