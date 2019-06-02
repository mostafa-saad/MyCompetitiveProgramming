/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Opis:              Rozwiazanie bledne                               *
 *                      za pomoca maksymalnych skojarzen w grafie        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N=2*500+10;
int n,m,r,t,k;
vector<int> adj[N];
int match[N],deg[N],vis[N],prev[N];
int ans_p[N],ans_t[N],ans_d[N],ans;
int penalty;

int rek(int v)
{
   FORE(i,adj[v]) if (!vis[*i]) {
      vis[*i]=1;
      if (match[*i]==-1 || rek(match[*i])) {
	 match[v]=*i;
	 match[*i]=v;
	 return 1;
      }
   }
   return 0;
}

void matching()
{
   REP(i,n+m) match[i] = -1;
   bool change = 1;
   while (change) {
      change = 0;
      REP(j,n+m) vis[j] = 0;
      REP(j,m) if (match[j] == -1 && rek(j)) change = 1;
   }
   REP(i,m) if (match[i] != -1) {
      int pers = match[i];
      ans_t[ans] = i;
      ans_p[ans] = pers;
      ans_d[ans] = ++deg[pers];
      penalty += deg[pers]*r;
      ans++;
      adj[i].clear();
      adj[pers].erase(find(adj[pers].begin(),adj[pers].end(),i));
   }
}

int main()
{
   scanf("%d%d%d%d%d",&n,&m,&r,&t,&k);
   REP(i,k) {
      int a,b;
      scanf("%d%d",&a,&b);
      adj[m+a-1].push_back(b-1);
      adj[b-1].push_back(m+a-1);
   }
   int d = min(m,t/r);
   REP(i,d) matching();
   printf("%d %d\n", ans, penalty);
   REP(i,ans) {
      int person = ans_p[i];
      int time = --deg[person];
      printf("%d %d %d\n",person+1-m, ans_t[i]+1, time*r);
   }
}
