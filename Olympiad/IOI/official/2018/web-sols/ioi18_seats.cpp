#include "seats.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 1000005;
const int MAXT = 2100000;

int n, m;
vector<vector<int>> G;
vector<vector<char>> is_valid;
vector<int> R, C;
pi val[MAXN];

void ADD(pi &a, pi b){
	a.first += b.first;
	a.second += b.second;
}

struct seg{
	pi tree[MAXT];
	pi lazy[MAXT];
	int cnt_min[MAXT];
	void lazydown(int p){
		ADD(tree[2*p], lazy[p]);
		ADD(tree[2*p+1], lazy[p]);
		ADD(lazy[2*p], lazy[p]);
		ADD(lazy[2*p+1], lazy[p]);
		lazy[p] = pi(0, 0);
	}
	void eat(int p){
		tree[p] = min(tree[2*p], tree[2*p+1]);
		cnt_min[p] = 0;
		if(tree[p] == tree[2*p]) cnt_min[p] += cnt_min[2*p];
		if(tree[p] == tree[2*p+1]) cnt_min[p] += cnt_min[2*p+1];
	}
	void init(int s, int e, int p){
		if(s == e){
			cnt_min[p] = 1;
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		eat(p);
	}
	void add(int s, int e, int ps, int pe, int p, pi v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			ADD(tree[p], v);
			ADD(lazy[p], v);
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		eat(p);
	}
	int query(){
		return tree[1] == pi(4, 0) ? cnt_min[1] : 0;
	}
}seg;

pi mp[MAXN];
vector<int> updp; 

void flush(){
	sort(updp.begin(), updp.end());
	updp.resize(unique(updp.begin(), updp.end()) - updp.begin());
	auto v = pi(0, 0);
	for(int i=0; i+1<updp.size(); i++){
		ADD(v, mp[updp[i]]);
		seg.add(updp[i], updp[i + 1] - 1, 0, n * m - 1, 1, v);
	}
	for(auto &i : updp) mp[i] = pi(0, 0);
	updp.clear();
}

void update(int x, int y, int f){
	if(is_valid[x][y] == 0 && f == -1) return;
	if(is_valid[x][y] == 1 && f == 1) return;
	is_valid[x][y] ^= 1;
	vector<pi> times;
	times.emplace_back(G[x][y], 0);
	times.emplace_back(G[x + 1][y], 1);
	times.emplace_back(G[x + 1][y + 1], 2);
	times.emplace_back(G[x][y + 1], 3);
	sort(times.begin(), times.end());
	for(int i=0; i<3; i++){
		int starting_time = times[i].first;
		int ending_time = times[i + 1].first;
		starting_time = max(starting_time, 0);
		ending_time = min(ending_time, n * m);
		if(starting_time >= ending_time) continue;
		pi updates;
		if(i == 0){
			updates = pi(f, 0);
		}
		if(i == 1){
			if((times[0].second ^ times[1].second) == 2){
				updates = pi(2 * f, 0);
			}
			else continue;
		}
		if(i == 2){
			updates = pi(0, f);
		}
		ADD(mp[starting_time], updates);
		ADD(mp[ending_time], pi(-updates.first, -updates.second));
		updp.push_back(starting_time);
		updp.push_back(ending_time);
	}
}

void give_initial_chart(int H, int W, std::vector<int> _R, std::vector<int> _C) {
	G.resize(H + 2);
	for(auto &i : G) i.resize(W + 2);
	for(auto &i : G) for(auto &j : i) j = 1e7;
	is_valid.resize(H + 1);
	for(auto &i : is_valid) i.resize(W + 1);
	n = H, m = W, R = _R, C = _C;
	for(int i=0; i<n*m; i++){
		G[R[i] + 1][C[i] + 1] = i;
	}
	for(int i=0; i<n+1; i++){
		for(int j=0; j<m+1; j++){
			update(i, j, 1);
		}
	}
	seg.init(0, n*m-1, 1);
}

int swap_seats(int a, int b) {
	swap(R[a], R[b]);
	swap(C[a], C[b]);
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			update(R[a] + i, C[a] + j, -1);
			update(R[b] + i, C[b] + j, -1);
		}
	}
	swap(G[R[a] + 1][C[a] + 1], G[R[b] + 1][C[b] + 1]);
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			update(R[a] + i, C[a] + j, 1);
			update(R[b] + i, C[b] + j, 1);
		}
	}
	flush();
	return seg.query();
}
