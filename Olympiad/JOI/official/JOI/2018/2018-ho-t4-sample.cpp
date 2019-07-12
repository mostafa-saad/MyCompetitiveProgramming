#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef pair<long long, int> P;

const long long inf = 1e18;

struct Edge{
	int to;
	int cost;
	Edge(){}
	Edge(int a, int b):to(a), cost(b){}
};

const int MAX_N = 100000;

int N;
vector<Edge> G[MAX_N];

int S, T;
int U, V;

void input(){
	int M;
	scanf("%d%d", &N, &M);
	scanf("%d%d", &S, &T);
	S--; T--;
	scanf("%d%d", &U, &V);
	U--; V--;
	for(int i = 0; i < M; ++i){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--; b--;
		G[a].push_back(Edge(b, c));
		G[b].push_back(Edge(a, c));
	}
}

long long dist[2][MAX_N];

long long dp[MAX_N][4];
long long dist2[MAX_N];
P ps[MAX_N];

priority_queue<P, vector<P>, greater<P> > que;
void dijkstra(int s, long long *res){
	while(!que.empty()) que.pop();
	for(int i = 0; i < N; ++i){
		res[i] = inf;
	}
	res[s] = 0;
	que.push(P(0, s));
	while(!que.empty()){
		P p = que.top();
		que.pop();
		long long c = p.first;
		int v = p.second;
		for(Edge e : G[v]){
			int u = e.to;
			long long nc = c + e.cost;
			if(res[u] <= nc) continue;
			res[u] = nc;
			que.push(P(nc, u));
		}
	}
}

long long get(int v, int id){
	long long res = 0;
	if(id & 1) res += dist[0][v];
	if(id & 2) res += dist[1][v];
	return res;
}

long long solve(){
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < 4; ++j){
			dp[i][j] = inf;
		}
	}
	dijkstra(U, dist[0]);
	dijkstra(V, dist[1]);
	dijkstra(S, dist2);
	for(int i = 0; i < N; ++i){
		ps[i] = P(dist2[i], i);
	}
	sort(ps, ps + N);
	dp[S][0] = 0;
	dp[S][1] = dist[0][S];
	dp[S][2] = dist[1][S];
	dp[S][3] = dist[0][S] + dist[1][S];
	for(int i = 0; i < N; ++i){
		int v = ps[i].second;
		for(int j = 0; j < G[v].size(); ++j){
			int u = G[v][j].to;
			if(dist2[v] != dist2[u] + G[v][j].cost) continue;
			for(int k = 0; k < 4; ++k){
				for(int l = 0; l < 4; ++l){
					dp[v][k | l] = min(dp[v][k | l], dp[u][k] + get(v, l));
				}
			}
		}
	}
	long long ans = dp[T][3];
	ans = min(ans, dist[0][V]);
	return ans;
}

int main(){
	input();
	long long ans = solve();
	printf("%lld\n", ans);
	return 0;
}
