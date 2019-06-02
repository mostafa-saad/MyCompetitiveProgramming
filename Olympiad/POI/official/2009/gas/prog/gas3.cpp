/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gas3.cpp                                                  *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie wzorcowe O(n*k)                               *
 *                                                                       *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<int> VI;
typedef long long ll;

#define FOR(I,A,B) for(int I=(A);I<=(B);++I)
#define FORD(I,A,B) for(int I=(A);I>=(B);--I)
#define REP(I,N) for(int I=0;I<(N);++I)
#define MINN(a,b) ((a)>(b)?(b):(a))
#define MAXX(a,b) ((a)<(b)?(b):(a))
#define PB push_back

#define MAX_N 100000
#define MAX_K 20

int n,k,s,a,b,is,result,gas[MAX_N],iedge[MAX_N],stack[MAX_N],deg[MAX_N];
ll need[MAX_N][MAX_K+1],have[MAX_N][MAX_K+1];
VI graf[MAX_N];

void dfs(int a,int b)
{
	FOR(e,iedge[a],deg[a]-1)
	{
		iedge[a]++;
		if(graf[a][e]!=b)
		{
			stack[is++]=graf[a][e];
			return;
		}
	}
	REP(c,deg[a])
	{
		int v=graf[a][c];
		if(v!=b)
		{
			gas[a]+=gas[v];
			REP(d,k+1)
			{
				have[a][d]+=have[v][d];
				need[a][d]+=need[v][d];
			}
		}
	}
	REP(c,k)
	{
		have[a][c]=have[a][c+1];
		need[a][k-c]=need[a][k-1-c];
	}
	have[a][k]=0;
	need[a][0]=1;
	int g=need[a][k]/s;
	if(need[a][k]%s!=0)
		g++;
	gas[a]+=g;
	have[a][k]+=(ll)g*(ll)s;
	REP(c,k+1)
	{
		ll m=MINN(have[a][c],need[a][c]);
		have[a][c]-=m;
		need[a][c]-=m;
	}
	REP(c,k)
	{
		ll m=MINN(have[a][c+1],need[a][c]);
		have[a][c+1]-=m;
		need[a][c]-=m;
	}
	is--;
}

int main()
{
	scanf("%d%d%d",&n,&s,&k);
	REP(i,n-1)
	{
		scanf("%d%d",&a,&b);
		a--; b--;
		graf[a].PB(b);
		graf[b].PB(a);
		deg[a]++; deg[b]++;
	}
	is=2;
	stack[0]=-1;
	stack[1]=0;
	while(is>1)
		dfs(stack[is-1],stack[is-2]);
	result=gas[0];
	FORD(i,k,0)
	{
		ll m=MINN(have[0][i],need[0][i]);
		have[0][i]-=m;
		need[0][i]-=m;
		int g=need[0][i]/s;
		if(need[0][i]%s!=0)
			g++;
		result+=g;
		have[0][i]+=(ll)g*(ll)s-need[0][i];
		if(i>0)
			have[0][i-1]+=have[0][i];
	}
	printf("%d\n",result);
}
