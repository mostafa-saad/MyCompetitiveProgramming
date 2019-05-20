#include<bits/stdc++.h>
using namespace std;
const int MAXN = 70005;

int n, m;
vector<int> gph[MAXN];
map<int, int> mp;
int dep[MAXN], par[17][MAXN];
int emax[MAXN], emin[MAXN], cost[MAXN];
int s[MAXN], e[MAXN];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

struct edg{
	int s, e, x;
};

int pa[MAXN];

int paint(int s, int l, int v, int *ans){
	if(s != pa[s]) return pa[s] = paint(pa[s], l, v, ans);
	if(dep[s] <= dep[l]) return s;
	else{
		ans[s] = v;
		return pa[s] = paint(par[0][s], l, v, ans);
	}
}

struct bipartite_matching{ // unnecessary, but I'm too lazy
	vector<int> gph[MAXN];
	bitset<MAXN> vis;
	int l[MAXN], r[MAXN];
	int dis[MAXN];
	void init(){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
	}
	void add_edge(int s, int e){
		gph[s].push_back(e);
	}
	bool bfs(int k){
		queue<int> que;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<k; i++){
			if(l[i] == -1){
				dis[i] = 1;
				que.push(i);
			}
		}
		int ok = 0;
		while(!que.empty()){
			auto x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		if(vis[x]) return 0;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(r[i] == -1 || dfs(r[i])){
				r[i] = x;
				l[x] = i;
				return 1;
			}
		}
		return 0;
	}
	void match(int k){
		while(bfs(k)){
			vis = 0;
			for(int i=0; i<k; i++){
				if(l[i] == -1){
					dfs(i);
				}
			}
		}
	}
}bpm;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	bpm.init();
	memset(emin, -1, sizeof(emin));
	memset(emax, 0x3f, sizeof(emax));
	vector<edg> evmax, evmin;
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		char buf[5];
		int s, e, x;
		scanf("%s %d %d %d",buf,&s,&e,&x);
		cost[i] = x;
		mp[x] = i;
		int l = lca(s, e);
		if(*buf == 'M'){
			evmax.push_back({s, l, x});
			evmax.push_back({e, l, x});
		}
		else{
			evmin.push_back({s, l, x});
			evmin.push_back({e, l, x});
		}
	}
	sort(evmax.begin(), evmax.end(), [&](const edg &a, const edg &b){
		return a.x < b.x;
	});
	sort(evmin.begin(), evmin.end(), [&](const edg &a, const edg &b){
		return a.x > b.x;
	});
	iota(pa, pa + n + 1, 0);
	for(auto &i : evmax){
		paint(i.s, i.e, i.x, emax);
	}
	iota(pa, pa + n + 1, 0);
	for(auto &i : evmin){
		paint(i.s, i.e, i.x, emin);
	}
	for(int i=2; i<=n; i++){
		int l = -1, r = -1;
		if(mp.find(emin[i]) != mp.end()) l = mp[emin[i]];
		if(mp.find(emax[i]) != mp.end()) r = mp[emax[i]];
		if(~l) bpm.add_edge(l, i-2);
		if(~r) bpm.add_edge(r, i-2);
	}
	bpm.match(m);
	// l : left -> right fun
	// r : right -> left fun
	for(int i=2; i<=n; i++){
		printf("%d %d ", par[0][i], i);
		if(bpm.r[i-2] == -1) printf("%d\n", emin[i]);
		else printf("%d\n", cost[bpm.r[i-2]]);
	}
}
