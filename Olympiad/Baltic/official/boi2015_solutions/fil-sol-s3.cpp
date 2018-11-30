// Tomasz Syposz, O(n^2 m)

#include <bits/stdc++.h>
using namespace std;
#define REP(i,a,b) for(int i=(a);i<=(b);++i)
#define FORI(i,n) REP(i,1,n)
#define FOR(i,n) REP(i,0,int(n)-1)
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define ll long long
#define SZ(x) int((x).size())
#define DBG(v) cerr << #v << " = " << (v) << endl;
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define SORT(X) sort(X.begin(),X.end())
#define fi first
#define se second

int Oj[3030];
int L[3030];
vector<int> V[3030];

int Sd[3030];
int In[3030];
int Out[3030];
int T,tmp_sd;

void dfs(int u){
	In[u] = ++T;
	tmp_sd += L[u];
	FOR(i,SZ(V[u]))
		dfs(V[u][i]);
	
	Sd[u] = tmp_sd;
	Out[u] = ++T;
	tmp_sd -= L[u];
//	printf("%d: %d %d %d\n", u,Sd[u],In[u],Out[u]);
}

int mxLen,slink,n;

bool below(int a, int b){
	if(In[a] > In[b]) return 0;
	if(Out[a] < Out[b]) return 0;
	return 1;
}

bool check(int a,int b){
//	cout<<Sd[a]+b<<endl;
	if(Sd[a] + b == mxLen) return 1;
	
	int j = a;	
	FOR(i,n+1){
		if(Sd[a]+Sd[i]-Sd[j]+slink+b == mxLen) return 1;
		if(!below(j,i)) continue;
		if((mxLen - b-Sd[a]) % (slink+Sd[i]-Sd[j]) == 0) return 1;
	}
	do{
		j = Oj[j];
		FOR(i,n+1){
			if(Sd[a]+Sd[i]-Sd[j]+slink+b == mxLen) return 1;
			if(!below(j,i)) continue;
			if((mxLen - b-Sd[a]) % (slink+Sd[i]-Sd[j]) == 0) return 1;
		}
	}while(j != 0);
	return 0;
}

int main () {
	int m,k;
	scanf("%d%d%d%d",&n,&m,&k,&slink);
	mxLen = k;
	slink++;
	FORI(i,n){
		int a,b;
		scanf("%d%d",&a,&b);
		Oj[i] = a;
		L[i] = b+1;
		V[a].pb(i);
	}
	L[0] = 1;
	dfs(0);
	FOR(i,m){
		int a,b;
		scanf("%d%d",&a,&b);
		
		bool IF = check(a,b);

		if(IF) puts("YES");
		else puts("NO");
	}
}
