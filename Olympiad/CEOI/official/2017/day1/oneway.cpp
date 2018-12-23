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

#define N 100000
#define M 100000
#define P 100000

mt19937 rnd(time(0));

int n,m,q;
vector<PII> adj[N];
int edge[M][2];
int path[P][3];

int bridge[M];
int comp[N];
char label[M+1];
vector<PII> adjc[N];

int t=0;
int lo[N],ind[N];

void tarjan(int x, int par=-1) {
	ind[x]=t; lo[x]=t;
	t++;
	for (PII yi : adj[x]) {
		int y=yi.first, i=yi.second;
		if (i==par) continue;
		if (ind[y]==-1) {
			tarjan(y,i);
			lo[x]=min(lo[x], lo[y]);
			if (lo[y]>ind[x]) bridge[i]=1;
		} else {
			lo[x]=min(lo[x], ind[y]);
		}
	}
}

int v[N];

void components(int x, int c) {
	v[x]=1;
	comp[x]=c;
	for (PII yi : adj[x]) {
		int y=yi.first, i=yi.second;
		if (!v[y] && !bridge[i]) components(y,c);
	}
}

int depth[N];
int parent[N][2];

void dfs(int x, int d=0, int par=-1, int pari=-1) {
	depth[x]=d;
	parent[x][0]=par; parent[x][1]=pari;
	for (PII yi : adjc[x]) {
		int y=yi.first, i=yi.second;
		if (y!=par) dfs(y,d+1,x,i);
	}
}

#define K 18
int p[N][K];

void LCA_init(int c) {
	INIT(p,-1);
	REP (i,c) p[i][0]=parent[i][0];
    FOR (k,1,K-1) {
    	REP (i,c) {
    		if (p[i][k-1]!=-1) {
				p[i][k]=p[p[i][k-1]][k-1];
    		}
    	}
    }
}

int LCA_query(int a, int b) {
	if (depth[a] < depth[b]) swap(a,b);
	for (int k=K-1;k>=0;k--) {
		if (depth[a]-(1<<k)>=depth[b]) {
			a=p[a][k];
		}
	}
	if (a==b) return a;
	for (int k=K-1;k>=0;k--) {
		if (p[a][k]!=p[b][k]) {
			a=p[a][k];
			b=p[b][k];
		}
	}
	return parent[a][0];
}

int ok=1;
int direction[N];

void direct(int x, int z, int dir) {
	if (x==z) return;
	if (direction[x]==0) {
		direction[x]=dir;
		int y=parent[x][0], i=parent[x][1];
		int a=comp[edge[i][0]], b=comp[edge[i][1]];
		if (dir==-1) {
			if (a==x && b==y) label[i]='R'; else label[i]='L';
		} else {
			if (a==y && b==x) label[i]='R'; else label[i]='L';
		}
		direct(y, z, dir);
	} else {
		if (direction[x]!=dir) ok=0;
	}
}

int main() {
	scanf("%d %d",&n,&m);
	assert(n<=100000 && m<=100000);
	REP (i,m) {
		int a,b;
		scanf("%d %d",&a,&b);
		assert(1<=a && a<=n); assert(1<=b && b<=n);
		a--; b--;
		edge[i][0]=a; edge[i][1]=b;
		adj[a].push_back({b,i});
		adj[b].push_back({a,i});
	}
	INIT(ind,-1);
	REP (i,n) if (ind[i]==-1) {
		tarjan(i);
	}
	int c=0;
	INIT(comp,-1);
	INIT(v,0);
	REP (i,n) if (!v[i]) {
		components(i,c);
		c++;
	}
	REP (i,m) if (bridge[i]) {
		int ca=comp[edge[i][0]], cb=comp[edge[i][1]];
		//assert(ca!=cb);
		adjc[ca].push_back({cb,i});
		adjc[cb].push_back({ca,i});
	}
	INIT(depth,-1);
	REP (i,n) if (depth[i]==-1) {
		dfs(i);
	}
	LCA_init(c);
	REP (i,m) label[i]='B';
	label[m]=0;
	scanf("%d",&q);
	assert(q<=100000);
	vector<PII> ord;
	REP (i,q) {
		int a,b;
		scanf("%d %d",&a,&b);
		assert(1<=a && a<=n); assert(1<=b && b<=n);
		a--; b--;
		path[i][0]=comp[a]; path[i][1]=comp[b]; path[i][2]=LCA_query(comp[a], comp[b]);
		assert(path[i][2]!=-1);
		ord.push_back({depth[path[i][2]],i});
	}
	sort(ALL(ord));
	INIT(direction,0);
	for (PII di : ord) {
		int i=di.second;
		int a=path[i][0], b=path[i][1], l=path[i][2];
		direct(a,l,-1);
		direct(b,l,1);
	}
	printf("%s\n",label);
	assert(ok);
	return 0;
}
