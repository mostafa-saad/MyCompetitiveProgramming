/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(m^2 n)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      przez sciezki powiekszajace                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N=600;
int n,m,r,t,k;
vector<int> adj[N],adj_m[N];
int deg[N],ma_m[N];
int u[N],u_m[N];
int em;
int nieidz[N];

int dfs(int v) {
   FORE(i,adj[v]) if (ma_m[*i] != v && !u_m[*i]) {
      u_m[*i]=1;
      if (ma_m[*i]==-1 || dfs(ma_m[*i])) {
	 if (ma_m[*i]!=-1) --deg[ma_m[*i]];
	 ++deg[v];
	 ma_m[*i]=v;
	 return 1;
      }
   }
   return 0;
}

void rob() {
   REP(i,m) ma_m[i]=-1;
   REP(i,n) nieidz[i]=0;
   REP(i,em) {
      vector<pair<int,int> > vv;
      REP(i,n) vv.push_back(make_pair(deg[i],i));
      sort(vv.begin(),vv.end());
      int ok=0;
      REP(i,n) u[i]=0;
      REP(i,m) u_m[i]=0;
      REP(i,n) {
	 if (!nieidz[i] && dfs(vv[i].second)) { ok=1; break; }
	 else nieidz[i]=1;
      }
   }
}


int main() {
   scanf("%d%d%d%d%d",&n,&m,&r,&t,&k);
   REP(i,k) {
      int a,b;
      scanf("%d%d",&a,&b); --a,--b;
      adj[a].push_back(b);
      adj_m[b].push_back(a);
   }
   REP(i,m) if (!adj_m[i].empty()) ++em;
   REP(i,n) random_shuffle(adj[i].begin(), adj[i].end());

   rob();
   
   int ile=0;
   int koszt=0;
   int degi[n];
   REP(i,n) {
      int w = degi[i] = min(deg[i], t/r);
      ile += w;
      koszt += (1+w)*w/2*r;
   }
   printf("%d %d\n",ile,koszt);
   REP(i,m) {
      if (ma_m[i]!=-1 && --degi[ ma_m[i] ] >= 0)
	 printf("%d %d %d\n",ma_m[i]+1,i+1,r*degi[ma_m[i]]);
   }
}
