/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(m^3 n)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      przez sciezki polepszajace koszt                 *
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


int dfs(int v, int d) {
   if (deg[v] < d-1) return true;
   FORE(i,adj[v]) if (!u_m[*i] && ma_m[*i] == v) {
      u_m[*i]=1;
      FORE(j,adj_m[*i]) if (!u[*j] && *j != v) {
	 u[*j]=1;
	 if (dfs(*j, d)) {
	    ma_m[*i] = *j;
	    ++deg[*j];
	    --deg[v];
	    return true;
	 }
      }
   }
   return false;
}

int rob() {
   REP(i,n) deg[i]=0;
   REP(i,m) ma_m[i]=-1;
   REP(i,m)
      if (!adj_m[i].empty()) {
	 ma_m[i]=adj_m[i][0];
	 ++deg[adj_m[i][0]];
      }

   int ch=1;
   while (ch) {
      ch=0;
      REP(j,n) u[j]=0;
      REP(j,m) u_m[j]=0;
      vector<pair<int,int> > vv;
      REP(i,n) vv.push_back(make_pair(-deg[i],i));
      sort(vv.begin(),vv.end());
      REP(i,n)
	 if (dfs(vv[i].second, -vv[i].first))
	    ch=1;
   }
   return 0;
}


int main() {
   scanf("%d%d%d%d%d",&n,&m,&r,&t,&k);
   REP(i,k) {
      int a,b;
      scanf("%d%d",&a,&b);
      --a;
      --b;
      adj[a].push_back(b);
      adj_m[b].push_back(a);
   }
   REP(i,m) random_shuffle(adj_m[i].begin(), adj_m[i].end());

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
