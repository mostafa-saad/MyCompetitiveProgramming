/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(m^2 n(m+n))                                    *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      przez przeplyw w sieci                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N=2+500*2, K=500*500, M=500+2*500*500, inf=1000000000;
int n,m,src,dst,p[N],d[N];
int b[M],e[M],powr[M],cost[M];
vector<int> adj[N];
int aa[K],bb[K],czas[N];

bool phase()
{
   REP(i,n) d[i]=inf;
   d[src]=0;
   int ch=0,ile=0;
   do {
      ch=0,ile++;
      REP(i,n) FORE(j,adj[i])
	 if (d[e[*j]] > d[i] + cost[*j]) {
	    d[e[*j]] = d[i] + cost[*j];
	    ch=1;
	    p[e[*j]] = *j;
	 }
   } while (ch && ile<n);
   return d[dst]<inf;
}

void solve()
{
   int flow=0,flowcost=0;
   while (phase()) {
      for (int v=dst; v!=src; ) {
	 int edge = p[v];
	 adj[b[edge]].erase(find(adj[b[edge]].begin(),adj[b[edge]].end(),edge));
	 adj[v].push_back(edge);
	 v = b[edge];
	 swap(b[edge],e[edge]);
	 flowcost += cost[edge];
	 cost[edge] *= -1;
	 powr[edge]^=1;
      }
      ++flow;
   }
   printf("%d %d\n",flow,flowcost);
}

#define v_source 0
#define v_task(i) (1+(i)) /* 0<=i<gm */
#define v_person(i) (1+gm+(i)) /* 0<=i<gn */
#define v_sink (1+gm+gn)
#define v_total (1+gm+gn+1)
#define e_solve(i) (gm+(i)) /* 0<=i<k */

void add_edge(int a, int B, int c)
{
   b[m]=a;
   e[m]=B;
   cost[m]=c;
   adj[a].push_back(m);
   m++;
}

int main()
{
   int gn,gm,r,t,k;
   scanf("%d%d%d%d%d",&gn,&gm,&r,&t,&k);
   int d=min(gm,t/r);
   REP(i,gm) add_edge(v_source, v_task(i), 0);
   REP(i,k) {
      scanf("%d%d",&aa[i],&bb[i]);
      add_edge(v_task(bb[i]-1), v_person(aa[i]-1), 0);
   }
   REP(i,gn) REP(j,d) add_edge(v_person(i), v_sink, (j+1)*r);

   n = v_total;
   src = v_source;
   dst = v_sink;
   solve();
   REP(i,k) {
      int edge = e_solve(i);
      if (powr[edge])
	 printf("%d %d %d\n", aa[i], bb[i], czas[aa[i]-1]++*r);
   }
}


