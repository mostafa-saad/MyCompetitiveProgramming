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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
char str1[100005], str2[100005];

char buf[200005];
int ord[200005], nord[200005], h, p = 1;

int sfx[200005], lcp[200005], rev[200005];
int match[100005];

struct rmq{
	int tree[530000], lim;
	void init(int n){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq1;

set<int> topgear;

void get_sfx(){
	for(int i=0; i<n; i++){
		buf[i] = str1[i];
	}
	buf[n] = max('z', 'Z') + 1;
	for(int i=0; i<m; i++){
		buf[n+1+i] = str2[i];
	}
	int s = n + m + 1;
	ord[s] = -1;
	for(int i=0; i<s; i++){
		ord[i] = buf[i];
		sfx[i] = i;
	}
	auto cmp = [&](const int &a, const int &b){
		if(ord[a] != ord[b]) return ord[a] < ord[b];
		return ord[a+p] < ord[b+p];
	};
	while(1){
		sort(sfx, sfx + s, cmp);
		if(2*p >= s) break;
		nord[sfx[0]] = 0;
		for(int i=1; i<s; i++){
			nord[sfx[i]] = nord[sfx[i-1]];
			if(cmp(sfx[i-1], sfx[i])) nord[sfx[i]]++;
		}
		p *= 2;
		for(int i=0; i<s; i++){
			ord[i] = nord[i];
		}
	}
	for(int i=0; i<s; i++){
		rev[sfx[i]] = i;
	}
	int p = 0;
	for(int i=0; i<s; i++){
		if(rev[i]){
			int p = sfx[rev[i] - 1];
			while(buf[i+h] == buf[p+h]) h++;
			lcp[rev[i]] = h;
		}
		h = max(h-1, 0);
	}
	for(int i=n+1; i<s; i++){
		topgear.insert(rev[i]);
	}
	rmq1.init(s);
	for(int i=1; i<s; i++){
		rmq1.add(i, lcp[i]);
	}
}


int trial(int x){
	set<int> s;
	s.insert(n);
	for(int i=n-1; i>=0; i--){
		auto it = s.lower_bound(i+x);
		if(it != s.end() && *it <= i + match[i]){
			s.insert(i);
		}
	}
	return *s.begin() == 0;
}

int main(){
	scanf("%s %s",str1, str2);
	n = strlen(str1), m = strlen(str2);
	get_sfx();
	for(int i=0; i<n; i++){
		auto it = topgear.lower_bound(rev[i]);
		if(it != topgear.end()){
			match[i] = max(match[i], rmq1.query(rev[i] + 1, *it));
		}
		if(it != topgear.begin()){
			it--;
			match[i] = max(match[i], rmq1.query(*it + 1, rev[i]));
		}
		//aprintf("%d %d\n",i, match[i]);
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	if(s == 0) s = -1;
	cout << s;
}