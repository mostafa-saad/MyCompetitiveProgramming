/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gass0.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^n). Kazdemu wierzcholkowi    *
 *             przporzadkowuje wierzcholek w ktorym bedzie gasnica       *
 *             ktora go zabezpiecza.                                     *
 *                                                                       *
 *************************************************************************/

// Headers {{{
#include<iostream>
#include<assert.h>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<bitset>
#include<numeric>
using namespace std;


#define FOR(I,A,B) for(int I=(A);I<=(B);++I)
#define FORD(I,A,B) for(int I=(A);I>=(B);--I)
#define REP(I,N) for(int I=0;I<(N);++I)
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();++I)
#define CLR(A,v) memset((A),v,sizeof((A)))

#define SIZE(x) ((int)((x).size()))
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second

typedef vector<int> VI;
typedef pair<int,int> PI;
typedef long long LL;
typedef vector<string> VS;
// }}}

const int nmx=100;
int E[nmx][nmx],n,s,k;
int S[nmx];
int result;

void fun(int x,int u){
	if(result<=u) return;
	if(x==n){
		result=u;
		return;
	}
	REP(t,n)if(E[x][t]<=k){
		S[t]++;
		fun(x+1,u+(((S[t]-1)%s==0)?1:0));
		S[t]--;
	}
}

int main()
{
	scanf("%d%d%d",&n,&s,&k);
	result=n;
	REP(i,n)REP(j,n) E[i][j]=n+1;
	REP(i,n) E[i][i]=1;
	int a,b;
	REP(i,n-1){
		scanf("%d%d",&a,&b); --a; --b;
		E[b][a]=E[a][b]=1;
	}
	REP(p,n)REP(a,n)REP(b,n) E[a][b]=min(E[a][b],E[a][p]+E[p][b]);
	if(s>1) fun(0,0);
	printf("%d\n",result);
	return 0;
}
