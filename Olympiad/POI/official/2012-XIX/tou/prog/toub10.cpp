/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Sprawdzenie wszystkich podzbiorow krawedzi       *
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
bool vis[MAXN+1];
int D[MAXN+1];

int n, m, k;

bool dfs(int v, int d, int lastk) {
  vis[v] = true;
  D[v] = d;
  for(int i=0;i<(int)G[v].size();++i)
  {
    int u = G[v][i];
    if(!vis[u]) {
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
  m = (int)edges.size();
  int ans = (1<<m)-1;
  for(int mask=0;mask<(1<<m);++mask)
  {
    if(__builtin_popcount(mask) >= __builtin_popcount(ans))
      continue;
    for(int i=0;i<m;++i)
      if(!((mask>>i)&1))
        G[edges[i].first].push_back(edges[i].second),
        G[edges[i].second].push_back(edges[i].first);
    bool cycle = false;
    memset(vis+1, false, n*sizeof(bool));
    for(int i=1;i<=k && !cycle;++i)
      if(!vis[i])
        cycle |= dfs(i, 1, i);
    if(!cycle)
      ans = mask;
    for(int i=0;i<m;++i)
      if(!((mask>>i)&1))
        G[edges[i].first].pop_back(),
        G[edges[i].second].pop_back();
  }
  printf("%d\n", __builtin_popcount(ans));
  for(int i=0;i<m;++i)
    if((ans>>i)&1)
      printf("%d %d\n", edges[i].first, edges[i].second);
  return 0;
}

