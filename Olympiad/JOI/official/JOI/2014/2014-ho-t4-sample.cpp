#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
const long long INF = 100001000010000100ll; // >> 10^9*10^5

int H[MAXN];
long long dist[MAXN];
vector<int> to[MAXN], cost[MAXN];

struct Dat{
	long long d;
	int v;
	Dat(long long d, int v):d(d),v(v){}
	bool operator<(const Dat& a)const{ return d < a.d;}
};

int main(){
	int N, M, X, A, B, T;
	scanf("%d%d%d",&N,&M,&X);
	
	for(int i = 1; i <= N; i++) scanf("%d",&H[i]);
	for(int i = 0; i < M; i++){
		scanf("%d%d%d",&A,&B,&T);
		to[A].push_back(B);
		cost[A].push_back(T);
		to[B].push_back(A);
		cost[B].push_back(T);
	}
	
	for(int i = 1; i <= N; i++) dist[i] = -INF;
	
	priority_queue<Dat> q;
	q.push(Dat(X,1));
	
	while(!q.empty()){
		Dat now = q.top(); q.pop();
		if(dist[now.v] != -INF) continue;
		dist[now.v] = now.d;
		for(int i = 0; i < to[now.v].size(); i++){
			int u = to[now.v][i], c = cost[now.v][i];
			if(c > H[now.v]) continue;
			q.push(Dat(min(now.d-c, (long long)H[u]), u));
		}
	}
	
	if(dist[N] == -INF) puts("-1");
	else printf("%lld\n",X+H[N]-dist[N]*2);
	
	return 0;
}
