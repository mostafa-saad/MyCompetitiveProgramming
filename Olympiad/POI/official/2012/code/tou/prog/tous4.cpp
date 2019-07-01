/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n^2 + m)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Budowa drzewa realizowane poprzez silowe         *
 *                      sprawdzanie dfsem czy nie powstal cykl           *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

const int MAXN = 1000000;

vector<int> G[MAXN+1];
vector< pair<int,int> > edges;
vector< pair<int,int> > ans;
int vis[MAXN+1];
int t;
int D[MAXN+1];

int n, m, k;

bool dfs(int v, int d, int lastk) {
  vis[v] = t;
  D[v] = d;
  for(int i=0;i<(int)G[v].size();++i)
  {
    int u = G[v][i];
    if(vis[u] != t) {
      if(dfs(u, d+1, u <= k ? u : lastk))
        return true;
    }
    else if(D[u] < D[v]-1 && D[u] <= D[lastk])
      return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  scanf("%d %d %d", &n, &m, &k);
  while(m--)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    if(a <= k)
      edges.push_back(make_pair(a, b));
    else {
      G[a].push_back(b);
      G[b].push_back(a);
    }
  }
  for(int i=0;i<(int)edges.size();++i)
  {
    G[edges[i].first].push_back(edges[i].second);
    G[edges[i].second].push_back(edges[i].first);
    ++t;
    if(dfs(edges[i].first, 1, edges[i].first)) {
      ans.push_back(edges[i]);
      G[edges[i].first].pop_back();
      G[edges[i].second].pop_back();
    }
  }
  printf("%d\n", ans.size());
  for(int i=0;i<(int)ans.size();++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}

