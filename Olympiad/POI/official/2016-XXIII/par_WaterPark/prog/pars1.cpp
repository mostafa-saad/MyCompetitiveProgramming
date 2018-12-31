/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Park wodny                                         *
 *   Autor programu:       Bartosz Kostka                                     *
 *   Zlozonosc czasowa:    O(n^6)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 2007;
char tab[MAXN][MAXN];
bool odw[MAXN][MAXN];

static int n;
int da[] = {0,0,-1,1}, db[] = {1,-1,0,0};

bool onboard(int a, int b)
{
  return 0 <= min(a,b) and max(a,b) < n;
}

int dfs(int a, int b)
{
  int cou = 1;
  odw[a][b] = true;
  for(int i=0; i<4; i++)
  {
    int na = a+da[i], nb = b+db[i];
    if(not(onboard(na,nb)))
      continue;
    if(odw[na][nb] == false and tab[na][nb] == 'B')
      cou += dfs(na,nb);
  }
  return cou;
}

int check()
{
  int res = 0;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      odw[i][j] = false;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(odw[i][j] == false and tab[i][j] == 'B')
        res = max(res, dfs(i,j));
  return res;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin >> n;
  for(int i=0; i<n; i++)
    cin >> tab[i];
  vector <pair <int, int>> A;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(tab[i][j] == 'A')
        A.emplace_back(i,j);
  int res = check();
  for(int i=0; i<(int)A.size(); i++)
  {
    auto p = A[i];
    tab[p.first][p.second] = 'B';
    res = max(res, check());
    tab[p.first][p.second] = 'A';
  }
  for(int i=0; i<(int)A.size(); i++)
    for(int j=i+1; j<(int)A.size(); j++)
    {
      auto p = A[i], q = A[j];

      tab[p.first][p.second] = 'B';
      tab[q.first][q.second] = 'B';
      res = max(res, check());
      tab[p.first][p.second] = 'A';
      tab[q.first][q.second] = 'A';
    }
  cout << res << "\n";
}
