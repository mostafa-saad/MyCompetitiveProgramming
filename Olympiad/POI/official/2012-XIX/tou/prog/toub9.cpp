/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne i powolne zarazem             *
 *                      Dla kazdej kolejnej krawedzi sprawdzenie, czy    *
 *                      tworzy ona cykl z wyroznionym wierzcholkiem.     *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

const int MAXN = 1000000;

vector<int> G[MAXN+1];
vector< pair<int,int> > ans;
int vis[MAXN+1];
int D[MAXN+1];
int t;

int S[MAXN+1];
int R[MAXN+1];
int K[MAXN+1];

int n, m, k;

int findSet(int x) {
  return S[x] == x ? x : S[x] = findSet(S[x]);
}
bool link(int x, int y) {
  x = findSet(x);
  y = findSet(y);
  if(x == y)
    return false;
  if(R[x] < R[y])
    swap(x, y);
  S[y] = x;
  R[x] += R[y];
  K[x] = max(K[x], K[y]);
  return true;
}

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
  for(int i=1;i<=n;++i)
    S[i] = i,
    R[i] = 1,
    K[i] = i <= k ? i : 0;
  while(m--)
  {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].push_back(b);
    G[b].push_back(a);
    ++t;
    if(!link(a, b) && K[S[a]] && dfs(K[S[a]], 1, K[S[a]]))
      G[a].pop_back(),
      G[b].pop_back(),
      ans.push_back(make_pair(a, b));
  }
  printf("%d\n", ans.size());
  for(int i=0;i<(int)ans.size();++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}

