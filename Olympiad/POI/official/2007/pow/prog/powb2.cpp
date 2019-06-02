/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    powb2.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Blad polega na tym, ze zakladamy koniecznosc osuszenia     *}
{*            calej kratownicy.                                          *}
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

int n, m;
int t[MAX_N][MAX_N];
/* Find & Union */
pair<int, int> p[MAX_N][MAX_N];
int rank[MAX_N][MAX_N];
bool pokr[MAX_N][MAX_N];

vector<pair<int, int> > tab[MAX_R + 1];

void odczyt()
{
  /* Odczyt */
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", t[i] + j);
}

void init()
{
  /* Inicjalizacja struktury Find & Union */
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      p[i][j] = make_pair(i, j);
      rank[i][j] = 0;
      pokr[i][j] = false;
    }
}

int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};

bool ins(int x, int n)
{
  return x>=0 && x<n;
}

/* Find & Union */
pair<int, int> findset(pair<int, int> x)
{
  if (p[x.first][x.second] != x)
    p[x.first][x.second] = findset(p[x.first][x.second]);
  return p[x.first][x.second];
}

void link(pair<int, int> x, pair<int, int> y)
{
  if (rank[x.first][x.second] < rank[y.first][y.second])
  {
    p[x.first][x.second] = y;
    pokr[y.first][y.second] |= pokr[x.first][x.second];
  }
  else
  {
    p[y.first][y.second] = x;
    pokr[x.first][x.second] |= pokr[y.first][y.second];
    if (rank[x.first][x.second] == rank[y.first][y.second])
      rank[x.first][x.second]++;
  }
}

int main()
{
  odczyt();
  init();
  /* Sortowanie kubelkowe */
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      tab[abs(t[i][j])].push_back(make_pair(i,j));

  int wyn = 0;
  for (int k = 1; k <= MAX_R; k++)
  {
    for (vector<pair<int, int> >::iterator it = tab[k].begin(); it!=tab[k].end(); ++it)
    {
      pair<int, int> p = *it;
      for (int poz = 0; poz <= 3; poz++)
        if (ins(p.first + x[poz], n) && ins(p.second + y[poz], m) &&
            abs(t[p.first + x[poz]][p.second + y[poz]]) <=
            abs(t[p.first][p.second]))
          link(findset(p), findset(make_pair(p.first + x[poz], p.second + y[poz])));
    }
    for (vector<pair<int, int> >::iterator it = tab[k].begin(); it!=tab[k].end(); ++it)
    {
      pair<int, int> p = *it;
      pair<int, int> par = findset(p);
      /* Tutaj jest blad: */
      if (/*t[p.first][p.second]>0 &&*/ !pokr[par.first][par.second])
      {
        pokr[par.first][par.second] = true;
        wyn++;
      }
    }
  }
  printf("%d\n", wyn);
  return 0;
}
