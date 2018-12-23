#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <ctime>
#include <iterator>
using namespace std;

#define ALL(c) (c).begin(),(c).end()
#define IN(x,c) (find(c.begin(),c.end(),x) != (c).end())
#define REP(i,n) for (int i=0;i<(int)(n);i++)
#define FOR(i,a,b) for (int i=(a);i<=(b);i++)
#define INIT(a,v) memset(a,v,sizeof(a))
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
template<class A, class B> A cvt(B x) { stringstream ss; ss<<x; A y; ss>>y; return y; }

typedef pair<int,int> PII;
typedef long long int64;

#define M 10000
#define INF 1000000000

int N,K,X;
vector<PII> adj[M+1];
int sz[M+1];
int f[M+1][M+1][2];
int g[2][M+1][2];

void solve(int x, int p=-1) {
	vector<PII> ch={{-1,-1}};
	int c=0;
	sz[x]=1;
	for (PII yt : adj[x]) if (yt.first!=p) {
		solve(yt.first, x);
		sz[x]+=sz[yt.first];
		ch.push_back(yt);
		c++;
	}
	FOR (k,0,K) REP (t,2) f[x][k][t]=INF;
	if (c==0) {
		f[x][1][0]=0;
		f[x][1][1]=0;
	} else {
		FOR (k,0,K) REP (t,2) { g[0][k][t]=INF; }
		g[0][0][0]=0;
		g[0][0][1]=0;
		int s=0;
		FOR (i,1,c) {
			FOR (k,0,K) REP (t,2) { g[i%2][k][t]=INF; }
			int si=sz[ch[i].first];
			FOR (k,0,min(s,K)) {
				// t=0
				g[i%2][k][0]=min(g[i%2][k][0], g[(i-1)%2][k][0]);
				FOR (h,1,min(si,K-k)) {
					g[i%2][k+h][0]=min(g[i%2][k+h][0], g[(i-1)%2][k][0]+2*ch[i].second+f[ch[i].first][h][0]);
				}
				// t=1 (wildcard)
				g[i%2][k][1]=min(g[i%2][k][1], g[(i-1)%2][k][1]);
				FOR (h,1,min(si,K-k)) {
					int score = min(g[(i-1)%2][k][1]+2*ch[i].second+f[ch[i].first][h][0], // don't use it
					                g[(i-1)%2][k][0]+1*ch[i].second+f[ch[i].first][h][1]); // use it
					g[i%2][k+h][1]=min(g[i%2][k+h][1], score);
				}
			}
			s+=si;
		}
		FOR (k,1,min(sz[x],K)) {
			REP (t,2) {
				f[x][k][t]=g[c%2][k-1][t];
			}
		}
	}
}

int main() {
	scanf("%d %d %d",&N,&K,&X);
	REP (i,N-1) {
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	solve(X);
	printf("%d\n",f[X][K][1]);
	return 0;
}
