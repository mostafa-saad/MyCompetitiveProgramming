/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Drogi zmiennokierunkowe                            *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n + m)                                           *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;
int n, m;
// G[0] - graf normalny
// G[1] - graf obrocony
vector <int> G[2][MAXN], P[2][MAXN], TOP[2];
int scc[2][MAXN], sto[2][MAXN], top[2][MAXN], J[2][MAXN];
vector <int> SCC[2][MAXN];
bool czy[MAXN], good[MAXN];
stack <int> S;

void dfs(int v, int a, int nscc = -1)
{
  czy[v] = true;
  for(auto w : G[a][v])
    if(not(czy[w]))
      dfs(w, a, nscc);
  if(nscc == -1)
    S.push(v);
  else
  {
    scc[0][v] = nscc;
    SCC[0][nscc].push_back(v);
  }
}

int findscc()
{
  memset(czy, false, sizeof(czy));
  while(not(S.empty()))
    S.pop();
  for(int i=1; i<=n; i++)
    if(not(czy[i]))
      dfs(i,0);
  memset(czy, false, sizeof(czy));
  int licscc = 0;
  while(not(S.empty()))
  {
    int v = S.top();
    S.pop();
    if(czy[v] == false)
      dfs(v, 1, ++licscc);
  }
  return licscc;
}

void addedges(int scca)
{
  for(int i=1; i<=n; i++)
    for(auto j : G[0][i])
      if(scc[0][i] != scc[0][j])
        P[0][scc[0][i]].push_back(scc[0][j]);
  for(int i=1; i<=scca; i++)
    for(auto j : P[0][i])
      P[1][j].push_back(i);
  for(int i=1; i<=scca; i++)
    P[0][i].clear();
  for(int i=1; i<=scca; i++)
    for(auto j : P[1][i])
      if(P[0][j].empty() or P[0][j].back() != i)
      {
        P[0][j].push_back(i);
        sto[0][i]++;
      }
}

void sorttop(int scca)
{
  queue <int> Q;
  for(int i=1; i<=scca; i++)
      if(sto[0][i] == 0)
        Q.push(i);
  int cza = 0;
  while(!Q.empty())
  {
    int v = Q.front();
    Q.pop();
    top[0][v] = ++cza;
    TOP[0].push_back(v);
    for(auto w : P[0][v])
    {
      sto[0][w]--;
      if(sto[0][w] == 0)
        Q.push(w);
    }
  }
  TOP[1] = TOP[0];
  reverse(TOP[1].begin(), TOP[1].end());
  for(int i=0; i<(int)TOP[1].size(); i++)
    top[1][TOP[1][i]] = i+1;
}

void calculatej(int a, int scca)
{
  for(int i=1; i<=scca; i++)
    J[a][i] = scca+1;
  for(int i=1; i<=scca; i++)
    for(auto j : P[a][i])
      J[a][i] = min(J[a][i], top[a][j]);
}

void checkgoodness(int a, int scca)
{
  int left = scca+1;
  int right = -1;
  for(int i=0; i<scca; i++)
  {
    int ak = TOP[a][i];
    if(left < i+1 and i+1 < right)
    {
      for(auto e : SCC[0][ak])
        good[e] = false;
    }
    left = min(left, i+1);
    right = max(right, J[a][ak]);
  }
}

int main()
{
  cin >> n >> m;
  while(m--)
  {
    int a, b;
    cin >> a >> b;
    G[0][a].push_back(b);
    G[1][b].push_back(a);
  }
  for(int i=1; i<=n; i++)
    good[i] = true;
  int noscc = findscc();
  addedges(noscc);
  sorttop(noscc);
  for(int a=0; a<2; a++)
  {
    calculatej(a, noscc);
    checkgoodness(a, noscc);
  }
  int ile = 0;
  for(int i=1; i<=n; i++)
    if(good[i])
      ile++;
  cout << ile << "\n";
  bool isfirst = true;
  for(int i=1; i<=n; i++)
  {
    if(good[i])
    {
      if(isfirst)
        isfirst = false;
      else
        cout << " ";
      cout << i;
    }
  }
  cout << "\n";
  return 0;
}
