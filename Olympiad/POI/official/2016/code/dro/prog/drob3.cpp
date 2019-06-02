/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Drogi zmiennokierunkowe                            *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n + m)                                           *
 *   Opis:                 Rozwiazanie czesciowe + heura                      *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;
int n, m;
// G[0] - graf normalny
// G[1] - graf obrocony
vector <int> G[2][MAXN], P[2][MAXN], Q[2][MAXN];
int scc[2][MAXN], sto[2][MAXN];
vector <int> SCC[2][MAXN];
bool czy[MAXN];
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
    scc[1-a][v] = nscc;
    SCC[1-a][nscc].push_back(v);
  }
}

int findscc(int a)
{
  memset(czy, false, sizeof(czy));
  //dlaczego stos nie ma clear?
  while(not(S.empty()))
    S.pop();
  for(int i=1; i<=n; i++)
    if(not(czy[i]))
      dfs(i,a);
  memset(czy, false, sizeof(czy));
  int licscc = 0;
  while(not(S.empty()))
  {
    int v = S.top();
    S.pop();
    if(czy[v] == false)
      dfs(v, 1-a, ++licscc);
  }
  return licscc;
}

void addedges(int a, int scca)
{
  for(int i=1; i<=n; i++)
    for(auto j : G[a][i])
      if(scc[a][i] != scc[a][j])
        P[a][scc[a][i]].push_back(scc[a][j]);
  for(int i=1; i<=scca; i++)
    for(auto j : P[a][i])
      Q[a][j].push_back(i);
  for(int i=1; i<=scca; i++)
    P[a][i].clear();
  for(int i=1; i<=scca; i++)
    for(auto j : Q[a][i])
      if(P[a][j].empty() or P[a][j].back() != i)
      {
        P[a][j].push_back(i);
        sto[a][i]++;
      }
  if(a)
  {
    for(int i=1; i<=scca; i++)
      reverse(P[a][i].begin(), P[a][i].end());
  }
}

vector <int> ZN[2];

void dziwnydfs(int v, int a)
{
  ZN[a].push_back(v);
  if(P[a][v].size() == 1)
    dziwnydfs(P[a][v].front(), a);
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
  vector <int> X[2];
  for(int a=0; a<2; a++)
  {
    int e = findscc(a);
    addedges(a, e);
    for(int i=1; i<=e; i++)
      if(sto[a][i] == 0)
        X[a].push_back(i);
  }
  vector <bool> ok(n+1, false);
  if(X[0].size() != 1 or X[1].size() != 1)
    cout << 0 << "\n\n";
  else
    for(int a=0; a<2; a++)
    {
      dziwnydfs(X[a].front(), a);
      for(auto sss : ZN[a])
        for(auto ele : SCC[a][sss])
          ok[ele] = true;
    }
  int ile = 0;
  for(int i=1; i<=n; i++)
    if(ok[i] == true)
      ile++;
  cout << ile << "\n";
  bool isfirst = true;
  for(int i=1; i<=n; i++)
  {
    if(ok[i])
    {
      if(isfirst)
        isfirst = false;
      else
        cout << " ";
      cout << i;
    }
  }
  cout << "\n";
}
