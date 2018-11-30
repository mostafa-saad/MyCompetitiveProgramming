// Tomasz Syposz

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
#define eb emplace_back
#define fi first
#define se second

int n,mxLen,slink;
vector<int> V[3001];
vector<pair<int,int> > Z[3001],Ans;
int Cy[2000001],L[3001],Zaz[1000001];
int Sc_null;

vector<int> D,Path;
void dziel(int a){
	D.clear();
	for(int i = 1; i*i <= a; i++) if(a%i==0){
		D.pb(i);
		D.pb(a/i);
	}
}

void update(int u, int Ld, int w){
  Cy[L[u]-Ld+slink] += w;
	FOR(v,SZ(V[u])) update(V[u][v],Ld,w);
}

void solve(int u){
	Path.pb(u);
	update(u,L[u],1);
	FOR(z, SZ(Z[u])){
		dziel(mxLen - L[u] - Z[u][z].fi);
		int tmp_ans = 0;
		FOR(d, SZ(D)){
			if(Cy[D[d]] > 0) tmp_ans = 1;
		}
		FOR(p, SZ(Path))  if(mxLen - (L[u]-L[Path[p]]+slink+Z[u][z].fi) >= 0)
			if(Zaz[mxLen - (L[u]-L[Path[p]]+slink+Z[u][z].fi)]) tmp_ans = 1;
    if(L[u]+Z[u][z].fi == mxLen) tmp_ans = 1;
		Ans.pb(mp(Z[u][z].se,tmp_ans));
	}
	FOR(v,SZ(V[u]))
		solve(V[u][v]);
	Path.pop_back();
	update(u,L[u],-1);
}

int main () {
	int m,k;
	Sc_null = scanf("%d%d%d%d",&n,&m,&k,&slink);
	slink++;
	mxLen = k;
	L[0] = 1;
	Zaz[1] = 1;
	FORI(i,n){
		int a,b;
		Sc_null =  scanf("%d%d",&a,&b);
		L[i] = b+1+L[a];
		Zaz[L[i]] = 1;
		V[a].pb(i);
	}

	FOR(i,m){
		int a,b;
		Sc_null = scanf("%d%d",&a,&b);
		Z[a].pb(mp(b,i));
	}
	solve(0);
	SORT(Ans);
	FOR(i,SZ(Ans)){
		printf(Ans[i].se?"YES\n":"NO\n");
	}
}
