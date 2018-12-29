/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Weryfikator odpowiedzi                           *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>

#include "oi.h"
using namespace std;

const int MAXN = 1000000;
const int MAXM = 2000000;

typedef pair<int,int> PII;

void wrong(const char* msg, int line=0, int position=0) {
  printf("WRONG\n");
  printf("%s\n", msg);
  exit(1);
}
void wrongCycle(int v) {
  char* msg = new char[100];
  sprintf(msg, "Wyscig moze przechodzic przez miasto %d.", v);
  wrong(msg);
}
void wrongRoads(int opt, int ans) {
  char* msg = new char[100];
  sprintf(msg, "Zablokowano niepoprawna liczbe drog: %d, optymalnie: %d.", ans, opt);
  wrong(msg);
}

vector<PII> edges;
vector<PII> deletedEdges;
vector<int> G[MAXN+1];
int vis[MAXN+1];

int res;

int n, m, k;

void read_data(oi::Scanner &in, oi::Scanner &out, oi::Scanner &popr_out) {
  n = in.readInt(1, MAXN);
  in.readSpace();
  m = in.readInt(0, MAXM);
  in.readSpace();
  k = in.readInt(1, n);
  in.readEoln();
  edges.reserve(m);
  for(int i=0;i<m;++i)
  {
    int a = in.readInt(1, n-1);
    in.readSpace();
    int b = in.readInt(a+1, n);
    in.readEoln();
    edges.push_back(make_pair(a, b));
  }
  in.readEof();
  res = popr_out.readInt(0, m);
  out.skipWhitespaces();
  int ans = out.readInt(0, m);
  if(res != ans)
    wrongRoads(res, ans);
  out.skipWhitespaces();
  deletedEdges.reserve(res);
  for(int i=0;i<res;++i)
  {
    int a = out.readInt(1, n-1);
    out.skipWhitespaces();
    int b = out.readInt(a+1, n);
    out.skipWhitespaces();
    deletedEdges.push_back(make_pair(a, b));
  }
  out.readEof();
  
  sort(edges.begin(), edges.end());
  sort(deletedEdges.begin(), deletedEdges.end());
  deletedEdges.erase(unique(deletedEdges.begin(), deletedEdges.end()), deletedEdges.end());
  if((int)deletedEdges.size() != res)
    wrong("Na wyjsciu zostala podana wielokrotnie ta sama droga.");
  int j = 0;
  for(int i=0;i<res;++i)
  {
    while(j < m && edges[j] < deletedEdges[i])
    {
      G[edges[j].first].push_back(edges[j].second);
      G[edges[j].second].push_back(edges[j].first);
      ++j;
    }
    if(j == m || edges[j] != deletedEdges[i])
      wrong("Usunieto nieistniejaca droge.");
    ++j;
  }
  while(j < m)
  {
    G[edges[j].first].push_back(edges[j].second);
    G[edges[j].second].push_back(edges[j].first);
    ++j;
  }
}

void dfs(int v, int d, int lastk) {
  vis[v] = d;
  for(int i=0;i<(int)G[v].size();++i)
  {
    int u = G[v][i];
    if(!vis[u])
      dfs(u, d+1, (u <= k) ? u : lastk);
    else if(vis[u] < vis[v]-1 && vis[u] <= vis[lastk])
      wrongCycle(lastk);
  }
}

int main(int argc, char *argv[]) {
  oi::Scanner in(argv[1], wrong, oi::PL);
  oi::Scanner out(argv[2], wrong, oi::PL);
  oi::Scanner popr_out(argv[3], wrong, oi::PL);
  
  read_data(in, out, popr_out);
  
  for(int i=1;i<=k;++i)
    if(!vis[i])
      dfs(i, 1, i);
  
  printf("OK\n");
  return 0;
}

