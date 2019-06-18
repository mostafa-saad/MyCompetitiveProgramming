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

struct sweep{
	int pos, s, e;
};

bool operator<(sweep a, sweep b){
	return a.pos < b.pos;
}

int w, h, b, n;

struct node{
	int ls, rs, sum, len;
};

node merge(node a, node b){
	node c;
	c.len = a.len + b.len;
	c.ls = a.ls + (a.ls == a.len ? b.ls : 0);
	c.rs = b.rs + (b.rs == b.len ? a.rs : 0);
	c.sum = max(a.sum, b.sum);
	c.sum = max(c.sum, c.ls);
	c.sum = max(c.sum, c.rs);
	c.sum = max(c.sum, a.rs + b.ls);
	return c;
}

struct seg{
	node tree[2100000];
	int tree2[2100000];
	void init(int s, int e, int x){
		if(s == e){
			tree[x] = {1, 1, 1, 1};
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*x);
		init(m+1, e, 2*x+1);
		tree[x] = merge(tree[2*x], tree[2*x+1]);
	}
	void upd(int s, int e, int ps, int pe, int p, int x){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree2[p] += x;
			if(tree2[p]) tree[p] = {0, 0, 0, tree[p].len};
			else if(ps == pe) tree[p] = {1, 1, 1, 1};
			else tree[p] = merge(tree[2*p], tree[2*p+1]);
			return;
		}
		int pm = (ps + pe) / 2;
		upd(s, e, ps, pm, 2*p, x);
		upd(s, e, pm+1, pe, 2*p+1, x);
		if(tree2[p]) tree[p] = {0, 0, 0, tree[p].len};
		else tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	void add(int s, int e, int x){
		upd(s, e, 0, h-1, 1, x);
	}
	int query(){
		return tree[1].sum;
	}
}seg;

vector<sweep> add, erase;


void solve1(){
	seg.init(0,h-1,1);
	for(int i=0; i<n; i++){
		int sx, sy, ex, ey;
		scanf("%d %d %d %d %*d",&sx,&sy,&ex,&ey);
		add.push_back({sx-1,sy-1,ey-1});
		erase.push_back({ex,sy-1,ey-1});
	}
	erase.push_back({0, 0, -1});
	sort(add.begin(), add.end());
	sort(erase.begin(), erase.end());
	int st = 0, ed = 0, spos = 0, epos = add[0].pos;
	int ret = 0;
	while(st < erase.size()){
		ret = max(ret, min(seg.query(), epos - spos));
		while(ed < add.size() && seg.query() > epos - spos){
			int e = ed;
			while(e < add.size() && add[ed].pos == add[e].pos){
				seg.add(add[e].s, add[e].e, 1);
				e++;
			}
			ed = e;
			epos = (ed == add.size() ? w : add[ed].pos);
			ret = max(ret, min(seg.query(), epos - spos));
		}
		int e = st;
		while(e < erase.size() && erase[st].pos == erase[e].pos) e++;
		while(e != erase.size() && ed != add.size() && add[ed].pos <= erase[e].pos){
			seg.add(add[ed].s, add[ed].e, 1);
			ed++;
		}
		epos = (ed == add.size() ? w : add[ed].pos);
		spos = erase[st].pos;
		while(st != e){
			seg.add(erase[st].s, erase[st].e, -1);
			st++;
		}
	}
	printf("%d",ret);
}

struct seg2{
	lint tree[2100000], lazy[2100000];
	void lazydown(int p){
		tree[2*p] += lazy[p];
		lazy[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}seg2;

int sx[30005], ex[30005], sy[30005], ey[30005], cst[30005];

struct sweep2{
	int pos, st, ed, x;
	bool operator<(const sweep2 &b)const{
		return pos < b.pos;
	}
};

vector<sweep2> v;

lint trial(int x){
	v.clear();
	for(int i=0; i<n; i++){
		sweep2 s1 = {sx[i] - x + 1, sy[i] - x + 1, ey[i], cst[i]};
		sweep2 s2 = {ex[i] + 1, sy[i] - x + 1, ey[i], -cst[i]};
		s1.st = max(s1.st, 1);
		s2.st = max(s2.st, 1);
		s1.ed = min(s1.ed, h-x+1);
		s2.ed = min(s2.ed, h-x+1);
		s1.pos = max(s1.pos, 1);
		s2.pos = max(s2.pos, 1);
		s1.pos = min(s1.pos, w-x+2);
		s2.pos = min(s2.pos, w-x+2);
		v.push_back(s1);
		v.push_back(s2);
	}
	sort(v.begin(), v.end());
	lint ret = 1e9;
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].pos == v[i].pos) e++;
		for(int j=i; j<e; j++){
			seg2.add(v[j].st, v[j].ed, 1, h-x+1, 1, v[j].x);
		}
		if(v[i].pos <= w-x+1) ret = min(ret, seg2.tree[1]);
		i = e;
	}
	return ret;
}

void solve2(){
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i],&cst[i]);
	}
	int s = 0, e = min(w, h);
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m) <= b) s = m;
		else e = m-1;
	}
	printf("%d",s);
}

int main(){
	scanf("%d %d %d %d",&w,&h,&b,&n);
	if(b) solve2();
	else solve1();
}
