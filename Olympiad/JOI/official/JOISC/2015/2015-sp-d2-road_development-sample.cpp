#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX_N=100000;
const int MAX_Q=300000;
const int MAX_LOG_N=20;
const int MAX_POW_2=262144;

int N,Q;

int T[MAX_Q];
int A[MAX_Q],B[MAX_Q];
bool is_edge[MAX_Q];
bool is_same_comp[MAX_Q];

struct UnionFind{
	int dep[MAX_N];
	int par[MAX_N];
	void init(int N){
		for(int i = 0; i < N; ++i) par[i] = i;
	}
	void init_with_depth(int N, int *a){
		for(int i = 0; i < N; ++i){
			dep[i] = a[i];
			par[i] = i;
		}
	}
	int find(int x){
		if(x == par[x]) return x;
		return par[x] = find(par[x]);
	}
	void unite(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y) return;
		if(dep[x] > dep[y]) par[x] = y;
		else par[y] = x;
	}
	bool same(int x, int y){
		return find(x) == find(y);
	}
};

UnionFind is_connected,is_zero;

struct Segtree{
	int N;
	int dat[MAX_POW_2];
	void init(int N_, int *a){
		N=1;
		while(N < N_) N *= 2;
		for(int i = 0; i < N_; ++i){
			dat[i + N] = a[i];
		}
		for(int i = N_; i < N; ++i){
			dat[i + N] = 0;
		}
		for(int i = N - 1; i >= 1; --i){
			dat[i] = 0;
		}
	}
	void update(int l, int r, int k, int a, int b){
		if(l <= a && b <= r){
			--dat[k];
			return;
		}else if(r <= a || b <= l){
			return;
		}else{
			update(l, r, k * 2, a, (a + b) / 2);
			update(l, r, k * 2 + 1, (a + b) / 2, b);
		}
	}
	void update(int l, int r){
		update(l, r, 1, 0, N);
	}
	int get(int id){
		id += N;
		int res = 0;
		while(id > 0){
			res += dat[id];
			id /= 2;
		}
		return res;
	}
};

Segtree seg;

int dep[MAX_N];
int par[MAX_N][MAX_LOG_N];
vector<int> G[MAX_N];
int pre[MAX_N], pos[MAX_N];
bool used[MAX_N];
int dep2[MAX_N];

int get_lca(int u, int v){
	if(u == v) return u;
	if(dep[u] < dep[v]) swap(u, v);
	int d = dep[u] - dep[v];
	for(int i = 0; i < MAX_LOG_N; ++i){
		if((d >> i) & 1){
			u = par[u][i];
		}
	}
	if(u == v) return u;
	for(int i = MAX_LOG_N - 1; i >= 0; --i){
		if(par[u][i] != par[v][i]){
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int c=0,d=0;
void dfs(int v, int p){
	used[v] = true;
	pre[v] = c;
	par[v][0] = p;
	dep[v] = d;
	++c;
	++d;
	for(int i = 0; i < G[v].size(); ++i){
		int u = G[v][i];
		if(u == p) continue;
		dfs(u, v);
	}
	--d;
	pos[v] = c;
}

void connect(int i, int u, int v){
	if(is_connected.same(u, v)){
		is_edge[i] = false;
	}else{
		is_edge[i] = true;
		G[u].push_back(v);
		G[v].push_back(u);
		is_connected.unite(u, v);
	}
}

int main(){
	scanf("%d%d", &N, &Q);
	for(int i = 0; i < Q; ++i){
		scanf("%d%d%d", T + i, A + i, B + i);
		--A[i]; --B[i];
	}
	is_connected.init(N);
	for(int i = 0; i < Q; ++i){
		if(T[i] == 1){
			connect(i, A[i], B[i]);
		}else{
			is_same_comp[i] = is_connected.same(A[i], B[i]);
		}
	}
	for(int i = 0; i < N; ++i){
		if(!used[i]){
			dfs(i,-1);
		}
	}
	is_zero.init_with_depth(N, dep);
	for(int i = 0; i < N; ++i) dep2[pre[i]] = dep[i];
	seg.init(N, dep2);
	for(int j = 1; j < MAX_LOG_N; ++j) for(int i = 0; i < N; ++i){
		if(par[i][j - 1] == -1) par[i][j] = -1;
		else par[i][j] = par[par[i][j - 1]][j - 1];
	}
	for(int i = 0; i < Q; ++i){
		if(T[i] == 1){
			if(is_edge[i]) continue;
			int u = A[i], v = B[i];
			int lca = get_lca(u, v);
			u = is_zero.find(u);
			while(dep[u] > dep[lca]){
				seg.update(pre[u], pos[u]);
				int p = par[u][0];
				is_zero.unite(u, p);
				u = is_zero.find(u);
			}
			v = is_zero.find(v);
			while(dep[v] > dep[lca]){
				seg.update(pre[v], pos[v]);
				int p = par[v][0];
				is_zero.unite(v, p);
				v = is_zero.find(v);
			}
		}else{
			if(!is_same_comp[i]){
				printf("-1\n");
				continue;
			}
			int u = A[i], v = B[i];
			int lca = get_lca(u,v);
			int ans = seg.get(pre[u]) + seg.get(pre[v]) - seg.get(pre[lca]) * 2;
			printf("%d\n", ans);
		}
	}
	return 0;
}
