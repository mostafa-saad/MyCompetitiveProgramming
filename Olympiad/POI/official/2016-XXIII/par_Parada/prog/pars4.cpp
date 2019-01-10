/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Parada                                             *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O(n^3)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1000007;
vector <int> G[MAXN];
int poziom[MAXN], przodek[MAXN];

int stopien(int v)
{
  return (int)G[v].size();
}

int check(int a, int b)
{
  if(poziom[a] > poziom[b])
    swap(a,b);
  int na = a, nb = b;
  int res = 0;
  while(poziom[a] != poziom[b])
  {
    res += max(0, stopien(b) - 1);
    b = przodek[b];
  }
  while(a != b)
  {
    res += max(0, stopien(a) - 1);
    res += max(0, stopien(b) - 1);
    a = przodek[a];
    b = przodek[b];
  }
  res += max(0, stopien(a));
  res -= (poziom[na] + poziom[nb] - 2 * poziom[a]);
  return res;
}

void dfs(int v, int d = 1)
{
  poziom[v] = d;
  for(auto w : G[v])
    if(poziom[w] == 0)
    {
      przodek[w] = v;
      dfs(w, d+1);
    }
}

int main()
{
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;

  for(int i=1; i<n; i++)
  {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  dfs(1);

  vector <int> I;
  for(int i=1; i<=n; i++)
    I.push_back(i);
  sort(I.begin(), I.end(), [](int a, int b){ return stopien(a) < stopien(b); });
  reverse(I.begin(), I.end());
  int res = 0;
  for(int i=0; i<n; i++)
    for(int j=i+1; j<n; j++)
      res = max(res, check(I[i], I[j]));
  cout << res << "\n";
  return 0;
}
