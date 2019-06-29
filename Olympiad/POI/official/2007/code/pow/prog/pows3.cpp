/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pows3.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne.                                      *}
{*            Zlozonosc: b. pesymistycznie O(mn*max_h).                  *}
{*                                                                       *}
{*************************************************************************/
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<utility>
using namespace std;

#define MAX_N 1000
#define MAX_R 1000
#define INFTY 10000 /* nieskonczonosc */

int n, m;
int t[MAX_N][MAX_N];
vector<pair<int, int> > tab[MAX_R + 1];
bool col[MAX_N][MAX_N];
int wys[MAX_N][MAX_N];

void odczyt()
{
  /* Odczyt */
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", t[i] + j);
}

int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};

inline bool ins(int x, int n)
{
  return x>=0 && x<n;
}

void dfs(int first, int second, int w)
{
  wys[first][second] = w;
  if (w == abs(t[first][second]))
    col[first][second] = true;
  
  int pomx, pomy;
  for (int poz = 0; poz <= 3; poz++)
    if (ins(pomx = first + x[poz], n) && ins(pomy = second + y[poz], m))
    {
      if (col[pomx][pomy] || w >= wys[pomx][pomy])
        continue;
      dfs(pomx, pomy, max(w, abs(t[pomx][pomy])));
    }
}

int main()
{
  odczyt();
  /* Sortowanie kubelkowe */
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      tab[abs(t[i][j])].push_back(make_pair(i,j));
      col[i][j] = false;
      wys[i][j] = INFTY;
    }

  int first, second;
  int wyn = 0;
  for (int k = 1; k <= MAX_R; k++)
    for (vector<pair<int, int> >::iterator it = tab[k].begin(); it != tab[k].end(); ++it)
    {
      first = (*it).first; second = (*it).second;
      if (col[first][second])
        continue;
      if (t[first][second] > 0)
      {
        wyn++;
        dfs(first, second, t[first][second]);
      }
    }
  printf("%d\n", wyn);
  return 0;
}
