/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 tel4.cpp                                      *
 *   Autor:                Mirosław Michalski                            *
 *   Opis:                 Rozwiazanie alternatywne.                     *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

#define REP(i,n) for(int i=0; i<(n); i++)
#define PB push_back
#define SIZE(x) ((int)x.size())
#define MAX_N 40000

const int INF = 1000000000;

int n,m;
vector<int> V[MAX_N];
int dist[2][MAX_N];
int que[MAX_N];

inline void bfs(int x) {
	int nr=x;
	REP(i,n) dist[x][i]=INF;
	dist[x][x]=0;

	int b,e;
	que[b=e=0]=x;
	while (b<=e) {
		x=que[b++];
		if (dist[nr][x]==2) break;
		REP(i,SIZE(V[x]))
			if (dist[nr][V[x][i]]==INF)
				dist[nr][V[x][i]]=dist[nr][x]+1,que[++e]=V[x][i];
	}
}


int main() {
	scanf("%d%d",&n,&m);
	int v1,v2;
	REP(i,m) {
		scanf("%d%d",&v1,&v2);
		v1--,v2--;
		V[v1].PB(v2),V[v2].PB(v1);
	}
	bfs(0);
	bfs(1);

	int a=0,b=0,c=0,d=0;
	REP(i,n) {
		if (dist[0][i]==1) a++;
		if (dist[0][i]==2) b++;
		if (dist[1][i]==1) c++;
		if (dist[1][i]==2) d++;
	}
	int e=n-2-a-b-c-d;

	int res=a+(a*(a-1))/2+a*b+(b*(b-1))/2+c+(c*(c-1))/2+c*d+(d*(d-1))/2+b*d+(b+d)*e+(e*(e-1))/2+max(a,c)*e;
	printf("%d\n",res-m);
	return 0;
}
