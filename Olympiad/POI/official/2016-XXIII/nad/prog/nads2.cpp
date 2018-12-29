/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nadajniki                                          *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O(3^n * n^2)                                       *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 200007;
vector <int> G[MAXN];
vector <pair <int, int>> E;
int blo[MAXN];

bool check(int n)
{
  for(auto ele : E)
  {
    int a, b;
    tie(a,b) = ele;
    int ile = 0;
    if(blo[a] or blo[b])
      continue;
    for(auto t : G[a])
      ile += blo[t];
    for(auto t : G[b])
      ile += blo[t];
    if(ile < 2)
      return false;
  }
  return true;
}

int main()
{
  int n;
  cin >> n;
  assert(n <= 30);
  for(int i=1; i<n; i++)
  {
    int a, b;
    cin >> a >> b;
    a--; b--;
    G[a].push_back(b);
    G[b].push_back(a);
    E.emplace_back(a,b);
  }
  int res = n;
  int en = 1;
  for(int i=0; i<n; i++)
    en *= 3;
  for(int mas=0; mas<en; mas++)
  {
    int tn = 1;
    for(int i=0; i<n; i++)
    {
      blo[i] = (mas/tn)%3;
      tn *= 3;
    }
    if(check(n))
    {
      int cn = 0;
      for(int i=0; i<n; i++)
        cn += blo[i];
      res = min(res, cn);
    }
  }
  cout << res << "\n";
  return 0;
}
