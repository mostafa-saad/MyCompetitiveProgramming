#include "highway.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 90005;

vector<int> gph[MAXN];

lint cut_ask(int m, vector<int> &c, vector<int> &u, vector<int> &v){
	bitset<MAXN> vis;
	for(auto &i : c) vis[i] = 1;
	vector<int> query(m);
	for(int i=0; i<m; i++) if(vis[u[i]] != vis[v[i]]) query[i] = 1;
	return ask(query);
}

void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
	int M = U.size();
	for(int i=0; i<M; i++){
		gph[U[i]].emplace_back(V[i]);
		gph[V[i]].emplace_back(U[i]); 
	}
	vector<int> v(M);
	lint stdist = ask(v) / A;
	int s = 0, e = M - 1;
	while(s != e){
		int m = (s + e) / 2;
		fill(v.begin() + m + 1, v.end(), 0);
		fill(v.begin(), v.begin() + m + 1, 1);
		if(ask(v) != A * stdist) e = m;
		else s = m + 1;
	}
	vector<int> bord[2], dist(N, 1e9);
	queue<pi> que;
	que.emplace(0, U[s]);
	que.emplace(1, V[s]);
	dist[U[s]] = dist[V[s]] = 0;
	while(!que.empty()){
		auto x = que.front(); que.pop();
		bord[x.first].push_back(x.second);
		for(auto &i : gph[x.second]){
			if(dist[i] > dist[x.second] + 1){
				dist[i] = dist[x.second] + 1;
				que.emplace(x.first, i);
			}
		}
	}
	int S = -1, T = -1;
	for(int i=0; i<2; i++){
		int s = 0, e = (int)bord[i].size() - 1;
		while(s != e){
			int m = (s + e + 1) / 2;
			vector<int> C(bord[i].begin() + m, bord[i].end());
			if(cut_ask(M, C, U, V) != stdist * A) s = m;
			else e = m - 1;
		}
		if(i) S = bord[i][s];
		else T = bord[i][s];
	}
	answer(S, T);
}
