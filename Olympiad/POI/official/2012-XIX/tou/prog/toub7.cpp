/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Usuwa krawedzie drzewowe z wyroznionych          *
 *                      wierzcholkow                                     *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

const int MAXN = 1000000;

typedef pair<int,int> PII;

vector<int> G[MAXN+1];
vector<PII> ans;

bool vis[MAXN+1];

int n, m, k;

void dfs(int v) {
  vis[v] = true;
  for(int i=0;i<(int)G[v].size();++i)
  {
    int u = G[v][i];
    if(!vis[u]) {
      if(v <= k)
        ans.push_back(make_pair(min(v, u), max(v, u)));
      dfs(u);
    }
  }
}

int main(int argc, char *argv[]) {
  scanf("%d %d %d", &n, &m, &k);
  for(int i=0;i<m;++i)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=1;i<=k;++i)
    if(!vis[i])
      dfs(i);
  printf("%d\n", (int)ans.size());
  for(int i=0;i<(int)ans.size();++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}

