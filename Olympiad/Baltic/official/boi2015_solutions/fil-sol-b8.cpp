// Tomasz Syposz, solution for subtask 2

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
vector<int> V[3030],A[3030];
int L[3030];

int Sum[3030];
set<int> Zaz;

vector<int> Path;
int Sum_tmp;

void dfs(int u){
	Path.pb(u);
	A[u] = Path;
	Sum_tmp += L[u];
	Sum[u] = Sum_tmp;
	Zaz.insert(Sum_tmp);
	FOR(i,SZ(V[u])){
		int v = V[u][i];
		dfs(v);
	}
	Sum_tmp -= L[u];
	Path.pop_back();
}

int main () {
	int n,m,k,slink;
	scanf("%d%d%d%d",&n,&m,&k,&slink);
	slink++;	
	FORI(i,n){
		int a,b;
		scanf("%d%d",&a,&b);
		Oj[i] = a;
		L[i] = b+1;
		V[a].pb(i);
	}
	L[0]=1;
	dfs(0);
	FOR(i,m){
		int a,b;
		scanf("%d%d", &a,&b);
		if(Sum[a]+b == k){
			printf("YES\n");
			continue;
		}
		int IF = true;
		FOR(i,SZ(A[a])){
                        int tmp = k-Sum[a]-slink-b+Sum[A[a][i]];        
			if(Zaz.find(tmp) != Zaz.end() ){
				printf("YES\n");
				IF=false;
				break;
			}
		}
		

		if(IF) printf("NO\n");
	}

	
}
