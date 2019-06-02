/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Program kilkakrotnie wykonuje zachlanny algorytm *
 *                      usuwania krawedzi powrotnych przy przegladaniu   *
 *                      dfs-em i wybiera najlepszy rezultat.             *
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
vector<PII> tmp;

int per[MAXN+1];
int vis[MAXN+1];

int n, m, k;

void dfs(int v, int lastk) {
  for(int i=0;i<(int)G[v].size();++i)
  {
    int u = G[v][i];
    if(!vis[u])
      vis[u] = vis[v] + 1,
      dfs(u, u <= k ? u : lastk);
    else if(vis[u] < vis[v]-1 && vis[u] <= vis[lastk])
     tmp.push_back(make_pair(min(u, v), max(u, v)));
  }
}

int main(int argc, char *argv[]) {
  srand(54113);
  scanf("%d %d %d", &n, &m, &k);
  ans.resize(m+1);
  for(int i=0;i<m;++i)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=1;i<=k;++i)
    per[i] = i;
  for(int foo=10000000/(n+m+m);foo;--foo)
  {
    random_shuffle(per+1, per+k+1);
    for(int i=1;i<=n;++i)
      random_shuffle(G[i].begin(), G[i].end());
    memset(vis+1, 0, n*sizeof(int));
    tmp.clear();
    for(int i=1;i<=k;++i)
      if(!vis[per[i]])
        vis[per[i]] = 1,
        dfs(per[i], per[i]);
    if(tmp.size() < ans.size())
      ans = tmp;
  }
  printf("%d\n", (int)ans.size());
  for(int i=0;i<(int)ans.size();++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}

