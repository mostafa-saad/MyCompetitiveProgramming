/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie oblicza funkcje low i probuje        *
 *                      otrzymac wlasnosc:                               *
 *                      low[u] > pre[v] dla v <= k oraz u-dziecko v      *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

#define MP make_pair
#define edge(a,b) MP(min(a, b), max(a, b))
#define PB push_back

typedef pair<int,int> PII;

const int MAXN = 1000000;

vector<int> G[MAXN+1];
vector<PII> ans;
int anssize;
int pre[MAXN+1];
int low[MAXN+1];
int t;

int n, m, k;

void dfs(int v, int parent) {
  pre[v] = low[v] = ++t;
  vector<PII>::iterator it;
  for(int i=0;i<(int)G[v].size();++i)
    if(G[v][i] != parent) {
      int u = G[v][i];
      if(!pre[u]) {
        dfs(u, v);
        if(low[u] < pre[v] && v <= k)
          ans.PB(edge(v, u));
        else
          low[v] = min(low[v], low[u]);
      }
      else if(pre[u] < pre[v]) {
        if(u <= k || v <= k)
          ans.PB(edge(v, u));
        else
          low[v] = min(low[v], pre[u]);
      }
    }
}

int main(int argc, char *argv[]) {
  scanf("%d %d %d", &n, &m, &k);
  while(m--)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].PB(b);
    G[b].PB(a);
  }
  while(1)
  {
    sort(ans.begin(), ans.end());
    anssize = ans.size();
    memset(pre+1, 0, n*sizeof(int));
    for(int i=1;i<=k;++i)
      if(!pre[i])
        dfs(i, -1);
    if(anssize == (int)ans.size())
      break;
    sort(ans.begin()+anssize, ans.end());
    ans.PB(MP(n+1, n+1));
    for(int i=1;i<=n;++i)
      for(int j=0;j<(int)G[i].size();)
        if(*(lower_bound(ans.begin()+anssize, ans.end(), edge(i, G[i][j]))) == edge(i, G[i][j]))
          G[i][j] = G[i].back(),
          G[i].pop_back();
        else
          ++j;
    ans.pop_back();
  }
  printf("%d\n", ans.size());
  for(int i=0;i<(int)ans.size();++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}

