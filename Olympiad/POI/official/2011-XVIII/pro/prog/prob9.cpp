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
vector<int> adj[N], old_adj[N];
int match[N],deg[N],vis[N],prev[N];
int ans_p[N],ans_t[N],ans_d[N],ans;
int penalty;
int best_p[N],best_t[N],best_deg[N],best;
int best_penalty;

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
      old_adj[m+a-1].push_back(b-1);
      old_adj[b-1].push_back(m+a-1);
   }
   int d = min(m,t/r);
   REP(phase,10) {
      REP(i,n+m) adj[i] = old_adj[i];
      REP(i,n+m) random_shuffle(adj[i].begin(), adj[i].end());
      REP(i,n+m) deg[i] = 0;
      ans = penalty = 0;
      REP(i,d) matching();
      if (ans > best || ans==best && penalty < best_penalty) {
	 best = ans;
	 best_penalty = penalty;
	 REP(i,n+m) {
	    best_p[i] = ans_p[i];
	    best_t[i] = ans_t[i];
	    best_deg[i] = deg[i];
	 }
      }
   }
   printf("%d %d\n", best, best_penalty);
   REP(i,best) {
      int person = best_p[i];
      int time = --best_deg[person];
      printf("%d %d %d\n",person+1-m, best_t[i]+1, time*r);
   }
}
