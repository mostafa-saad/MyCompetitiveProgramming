/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gas.cpp                                                   *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n*k)                               *
 *                                                                       *
 *                                                                       *
 *************************************************************************/

// Headers {{{
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);++I)
#define FORD(I,A,B) for(int I=(A);I>=(B);--I)
#define REP(I,N) for(int I=0;I<(N);++I)
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();++I)
#define PB push_back
typedef vector<int> VI;
typedef long long LL;
// }}}

const int nmx=100000;
const int kmx=21;
int n,s,k,result;
LL up[nmx][kmx],need[nmx][kmx];
VI E[nmx];

void dfs(int v,int p){
	FORE(t,E[v]) if(*t!=p){
		dfs(*t,v);
		REP(i,k) up[v][i]+=up[*t][i+1],need[v][i+1]+=need[*t][i];
	}
	need[v][0]=1;
	LL x;
	x=(need[v][k]+s-1)/s;
	up[v][k]=x*s;
	result+=x;
	REP(i,k+1){ x=min(up[v][i],need[v][i]); up[v][i]-=x,need[v][i]-=x;}
	REP(i,k){ x=min(up[v][i+1],need[v][i]); up[v][i+1]-=x,need[v][i]-=x;}
}


int main()
{
	scanf("%d%d%d",&n,&s,&k);
	int a,b;
	REP(i,n-1){
		scanf("%d%d",&a,&b); --a;--b;
		E[a].PB(b); E[b].PB(a);
	}
	dfs(0,-1);
	LL h=0,x;
	FORD(i,k,0){
		h+=up[0][i];
		if (h < need[0][i]){
			x=(need[0][i]-h+s-1)/s;
			result+=x;
			h+=x*s;
		}
		h-=need[0][i];		
	}
	printf("%d\n",result);
	return 0;
}
