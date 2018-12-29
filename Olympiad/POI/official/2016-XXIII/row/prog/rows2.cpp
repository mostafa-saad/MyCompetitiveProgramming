/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Rownowazne programy                                *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(nm + nk + km)                                    *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 100007;
const int MAXK = 1007;
vector <int> G[MAXN], W[2][MAXK];
int cia[2][MAXN], pref[2][MAXN];
int n, k, m;

bool czy()
{

  for(int i=1; i<=k; i++)
  {
    if((int)W[0][i].size() != (int)W[1][i].size())
      return false;
    for(auto wrog : G[i])
    {
      for(int e=0; e<2; e++)
      {
        for(int p=1; p<=n; p++)
        {
          pref[e][p] = pref[e][p-1];
          if(cia[e][p] == wrog)
            pref[e][p]++;
        }
        pref[e][n+1] = pref[e][n];
      }
      vector<int> poprz = {0, 0};
      for(int j=1; j<(int)W[0][i].size(); j++)
      {
        vector<int> akt = {W[0][i][j], W[1][i][j]};
        for(int k=0; k<(int)G[i].size(); k++)
          if(pref[0][akt[0]] - pref[0][poprz[0]] != pref[1][akt[1]] - pref[1][poprz[1]])
            return false;
        poprz = akt;
      }
    }
  }
  return true;
}

int main()
{
  cin >> n >> k >> m;
  while(m--)
  {
    int a, b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  for(int i=1; i<=k; i++)
  {
    W[0][i].push_back(0);
    W[1][i].push_back(0);
  }
  for(int e=0; e<2; e++)
    for(int i=1; i<=n; i++)
    {
      cin >> cia[e][i];
      W[e][cia[e][i]].push_back(i);
    }
  for(int i=1; i<=k; i++)
  {
      W[0][i].push_back(n+1);
      W[1][i].push_back(n+1);
  }
  puts(czy() ? "TAK" : "NIE");
}
