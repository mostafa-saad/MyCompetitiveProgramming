#include "books.h"
#include <bits/stdc++.h>
const int MAXN = 1000005;
typedef long long lint;
using namespace std;
typedef pair<int, int>pi;

int vis[MAXN], dx[MAXN], n;
vector<pi> v;
vector<pi> gph[MAXN];

void add_edge(int s, int e, int x){
	gph[s].push_back(pi(x, e));
}

int dijkstra(int s, int e){
	memset(vis, 0, sizeof(vis));
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, s));
	while(!pq.empty()){
		auto l = pq.top();
		pq.pop();
		if(l.second == e) return l.first;
		if(vis[l.second]) continue;
		vis[l.second] = 1;
		for(auto &i : gph[l.second]){
			pq.push(pi(i.first + l.first, i.second));
		}
	}
	return -1;
}

struct rmq1{
	pi tree[2100000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2100000, pi(-1e9, -1e9));
	}
	void update(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-1e9, -1e9);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}rmq1;

struct rmq2{
	pi tree[2100000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2100000, pi(1e9, -1e9));
	}
	void update(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, -1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq2;

void dfs(int x){
	vis[x] = 1;
	rmq1.update(v[x].first, pi(-1e9, -1e9));
	rmq2.update(v[x].second, pi(1e9, -1e9));
	while(true){
		auto l = rmq1.query(v[x].first + 1, v[x].second - 1); // max segtree, first <- (second, idx)
		if(l.first <= v[x].second) break;
		add_edge(v[x].second, l.first, 0);
		add_edge(l.first, v[x].second, 0);
		dfs(l.second);
	}
	while(true){
		auto l = rmq2.query(v[x].first + 1, v[x].second - 1); // min segtree, second <- (first, idx)
		if(l.first >= v[x].first) break;
		add_edge(v[x].second, l.first, 0);
		add_edge(l.first, v[x].second, 0);
		dfs(l.second);
	}
}

long long minimum_walk(std::vector<int> p, int s) {
	if(is_sorted(p.begin(), p.end())) return 0;
	n = p.size();
	lint ans = 0;
	for(int i=0; i<n; i++){
		if(p[i] != i && !vis[i]){
			vector<int> w;
			for(int j=i; !vis[j]; j=p[j]){
				vis[j] = 1;
				ans += abs(p[j] - j);
				w.push_back(j);
			}
			sort(w.begin(), w.end());
			for(int j=1; j<w.size(); j++){
				add_edge(w[j-1], w[j], 0);
				add_edge(w[j], w[j-1], 0);
				v.push_back(pi(w[j-1], w[j]));
			}
			dx[w[0]]++;
			dx[w.back()]--;
		}
	}
	int lo = s, hi = s;
	for(int i=1; i<n; i++) dx[i] += dx[i-1];
	for(int i=0; i<n; i++){
		if(dx[i]){
			lo = min(lo, i);
			hi = max(hi, i+1);
		}
	}
	ans += 2 * count(dx + lo, dx + hi, 0);
	sort(v.begin(), v.end());
	rmq1.init(n);
	rmq2.init(n);
	for(int i=0; i<v.size(); i++){
		rmq1.update(v[i].first, pi(v[i].second, i));
		rmq2.update(v[i].second, pi(v[i].first, i));
	}
	vector<int> li;
	for(int i=0; i<n; i++){
		if(i == s || vis[i]) li.push_back(i);
	}
	for(int i=1; i<li.size(); i++){
		int l = li[i-1], r = li[i];
		add_edge(l, r, r-l);
		add_edge(r, l, r-l);
	}
	memset(vis, 0, sizeof(vis));
	for(int i=0; i<v.size(); i++){
		if(!vis[i]) dfs(i);
	}
	int ps = s;
	while(ps > 0 && dx[ps-1]) ps--;
	ans += 2 * dijkstra(ps, s);
	return ans;
}
