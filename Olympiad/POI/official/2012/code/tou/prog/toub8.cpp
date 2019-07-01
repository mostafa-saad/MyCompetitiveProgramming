/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Rozwiazanie dla kazdej dwuspojnej wybiera lepsza *
 *                      z dwoch strategii: zrobienie z niej drzewa badz  *
 *                      z kazdego wyroznionego wierzcholka usuniecie     *
 *                      wszystkich krawedzi procz jednej.                *
 *                                                                       *
 *************************************************************************/


#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;

#define MP make_pair
#define PB push_back

typedef pair<int,int> PII;

const int MAXN = 1000000;

vector<int> G[MAXN+1];
vector<PII> ans;
vector<PII> S;

int pre[MAXN+1];
int low[MAXN+1];
int t;
int pom[MAXN+1];
int p = 1;

vector<int> vertices;
vector<PII> edges;

int Set[MAXN+1];
int R[MAXN+1];

int findSet(int x) {
  return Set[x] == x ? x : Set[x] = findSet(Set[x]);
}
bool link(int x, int y) {
  x = findSet(x);
  y = findSet(y);
  if(x == y)
    return false;
  if(R[x] < R[y])
    swap(x, y);
  Set[y] = x;
  R[x] += R[y];
  return true;
}

int n, m, k;

void dfs(int v, int parent) {
  pre[v] = low[v] = ++t;
  for(int i=0;i<(int)G[v].size();++i)
    if(G[v][i] != parent) {
      int u = G[v][i];
      if(!pre[u]) {
        S.PB(MP(v, u));
        dfs(u, v);
        low[v] = min(low[v], low[u]);
        if(pre[v] <= low[u]) {
          if(S.back() == MP(v, u))
            S.pop_back();
          else {
            PII e;
            int del = 0;
            vertices.clear();
            edges.clear();
            do
            {
              e = S.back();
              S.pop_back();
              edges.PB(e);
              vertices.PB(e.first);
              vertices.PB(e.second);
              if(e.first <= k || e.second <= k) {
                if(e.first > k) {
                  if(pom[e.second] != p)
                    pom[e.second] = p;
                  else
                    ++del,
                    ans.PB(MP(min(e.first, e.second), max(e.first, e.second)));
                }
                else if(e.second > k) {
                  if(pom[e.first] != p)
                    pom[e.first] = p;
                  else
                    ++del,
                    ans.PB(MP(min(e.first, e.second), max(e.first, e.second)));
                }
                else {
                  if(pom[e.first] == p || pom[e.second] == p)
                    ++del,
                    ans.PB(MP(min(e.first, e.second), max(e.first, e.second)));
                  else
                    pom[e.first] = pom[e.second] = p;
                }
              }
            }
            while(e != MP(v, u));
            ++p;
            sort(vertices.begin(), vertices.end());
            vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());
            if((int)edges.size() - ((int)vertices.size() - 1) < del) {
              for(int j=0;j<(int)vertices.size();++j)
                R[vertices[j]] = 1, Set[vertices[j]] = vertices[j];
              while(del--)
                ans.pop_back();
              for(int j=0;j<(int)edges.size();++j)
                if(!link(edges[j].first, edges[j].second))
                  ans.PB(MP(min(edges[j].first, edges[j].second), max(edges[j].first, edges[j].second)));
            }
          }
        }
      }
      else if(pre[u] < pre[v]) {
        S.PB(MP(v, u));
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
  for(int i=1;i<=k;++i)
    if(!pre[i])
      dfs(i, -1);
  printf("%d\n", ans.size());
  for(int i=0;i<(int)ans.size();++i)
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}

