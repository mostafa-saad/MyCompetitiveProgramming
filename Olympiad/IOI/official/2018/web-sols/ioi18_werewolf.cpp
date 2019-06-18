#include "werewolf.h"
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 400005;
const int MAXT = 530000;

struct seg{
	int tree[MAXT], lim;
	void init(int n){
		fill(tree, tree + MAXT, -1e9);
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = -1e9;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p > q) swap(p, q);
		if(p == q) return 0;
		pa[p] = q; return 1;
	}
}disj;

struct graph{
	vector<int> gph[MAXN];
	int din[MAXN], dout[MAXN], piv;
	void add_edge(int p, int q){
		gph[p].push_back(q);
	}
	void dfs(int x){
		din[x] = piv;
		if(gph[x].empty()) piv++;
		for(auto &i : gph[x]) dfs(i);
		dout[x] = piv;
	}
}g1, g2;

struct queries{
	int s, l, e, r;
	int rs, re, idx;
}qr[MAXN];

struct edges{ int s, e, x; }ed[MAXN];

std::vector<int> check_validity(int N, std::vector<int> X, std::vector<int> Y,
		std::vector<int> S, std::vector<int> E,
		std::vector<int> L, std::vector<int> R) {
	int M = X.size();
	int Q = S.size();
	for(int i=0; i<Q; i++) qr[i] = {S[i], L[i], E[i], R[i], -1, -1, i};
	// make first tree
	int vtx_num = N, ptr = 0;
	qr[Q].l = -1e9;
	disj.init(N * 2);
	for(int i=0; i<M; i++) ed[i] = {X[i], Y[i], min(X[i], Y[i])};
	sort(qr, qr + Q, [&](const queries &a, const queries &b){
		return a.l > b.l;
	});
	sort(ed, ed + M, [&](const edges &a, const edges &b){
		return a.x > b.x;
	});
	for(int i=0; i<=Q; i++){
		while(ptr < M && ed[ptr].x >= qr[i].l){
			int l = disj.find(ed[ptr].s);
			int r = disj.find(ed[ptr].e);
			ptr++;
			if(l == r) continue;
			disj.uni(l, vtx_num);
			disj.uni(r, vtx_num);
			g1.add_edge(vtx_num, l);
			g1.add_edge(vtx_num, r);
			vtx_num++;
		}
		qr[i].rs = disj.find(qr[i].s);
	}
	// make second tree
	vtx_num = N, ptr = 0;
	qr[Q].r = 1e9;
	disj.init(N * 2);
	for(int i=0; i<M; i++) ed[i] = {X[i], Y[i], max(X[i], Y[i])};
	sort(qr, qr + Q, [&](const queries &a, const queries &b){
		return a.r < b.r;
	});
	sort(ed, ed + M, [&](const edges &a, const edges &b){
		return a.x < b.x;
	});
	for(int i=0; i<=Q; i++){
		while(ptr < M && ed[ptr].x <= qr[i].r){
			int l = disj.find(ed[ptr].s);
			int r = disj.find(ed[ptr].e);
			ptr++;
			if(l == r) continue;
			disj.uni(l, vtx_num);
			disj.uni(r, vtx_num);
			g2.add_edge(vtx_num, l);
			g2.add_edge(vtx_num, r);
			vtx_num++;
		}
		qr[i].re = disj.find(qr[i].e);
	}
	// both done
	g1.dfs(2 * N - 2);
	g2.dfs(2 * N - 2);
	vector<pi> points;
	vector<int> ans(Q);
	for(int i=0; i<N; i++) points.emplace_back(g1.din[i], g2.din[i]);
	sort(points.begin(), points.end());
	sort(qr, qr + Q, [&](const queries &a, const queries &b){
		return g1.dout[a.rs] < g1.dout[b.rs];
	});
	seg.init(N);
	ptr = 0;
	for(int i=0; i<Q; i++){
		while(ptr < N && points[ptr].first < g1.dout[qr[i].rs]){
			seg.add(points[ptr].second, points[ptr].first);
			ptr++;
		}
		if(seg.query(g2.din[qr[i].re], g2.dout[qr[i].re] - 1) >= g1.din[qr[i].rs]){
			ans[qr[i].idx] = 1;
		}
	}
	return ans;
}
