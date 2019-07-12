#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

const int MAX_N = 100000;
const int MAX_M = 200000;

vector<int> G[MAX_N];
int dis[MAX_N];
int N;

int Q;

void bfs_all(int s){
	for(int i = 0; i < N; i++){
		dis[i] = -1;
	}
	dis[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int v = que.front();
		que.pop();
		for(int i = 0; i < G[v].size(); ++i){
			int u = G[v][i];
			if(dis[u] != -1 && dis[u] <= dis[v] + 1) continue;
			dis[u] = dis[v] + 1;
			que.push(u);
		}
	}
}

bool ok[MAX_N];

vector<int> G2[MAX_N];

int bfs(int u, int v){
	if(dis[u] == dis[v]){
		return 0;
	}
	if(dis[u] > dis[v]) swap(u, v);
	G2[u].push_back(v);
	int res = 0;
	if(ok[u]){
		queue<int> que;
		que.push(v);
		while(!que.empty()){
			int v = que.front();
			que.pop();
			if(ok[v]) continue;
			ok[v] = true;
			res++;
			for(int i = 0; i < G2[v].size(); ++i){
				int u = G2[v][i];
				que.push(u);
			}
		}
	}
	return res;
}

int qs[MAX_M];
int us[MAX_M],vs[MAX_M];
int M;

int ord[MAX_M];
bool used[MAX_M];

void init(){
	for(int i = 0; i < M; ++i){
		used[i] = false;
	}
	for(int q = 0; q < Q; ++q){
		ord[q] = qs[q];
		used[qs[q]] = true;
	}
	int c = Q;
	for(int i = 0; i < M; ++i){
		if(!used[i]){
			ord[c++] = i;
		}
	}
}

int cnt[MAX_M + 1];

int main(){
	scanf("%d%d%d", &N, &M, &Q);
	for(int i = 0; i < M; ++i){
		scanf("%d%d", us + i, vs + i);
		us[i]--;
		vs[i]--;
		G[us[i]].push_back(vs[i]);
		G[vs[i]].push_back(us[i]);
	}
	bfs_all(0);
	for(int q = 0; q < Q; ++q){
		scanf("%d", qs + q);
		qs[q]--;
	}
	init();
	int prv = 0;
	ok[0] = true;
	cnt[M] = 0;
	for(int i = M - 1; i >= 0; --i){
		int u = us[ord[i]], v = vs[ord[i]];
		int cur = bfs(u, v);
		cnt[i] = prv + cur;
		prv = cnt[i];
	}
	for(int q = 0; q < Q; ++q){
		printf("%d\n", N - 1 - cnt[q + 1]);
	}
	return 0;
}
