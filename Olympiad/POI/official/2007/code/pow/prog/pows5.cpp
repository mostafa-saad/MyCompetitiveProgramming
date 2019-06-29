/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pows5.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne. Zlozonosc: O(mn*max_h) - grube       *}
{*            szacowanie. Rozwiazanie osusza tylko te pola, ktore sa     *}
{*            na jakims ciagu o niemalejacej wysokosci, lub ewentualnie  *}
{*            niemniejszej wysokosci pola spoza Bajtogrodu.              *}
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
int c[MAX_N][MAX_N];

vector<pair<int, int> > tab[MAX_R + 1];

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

bool ins(int x, int n)
{
  return x>=0 && x<n;
}

void dfs(int i,int j,int pom)
{
  c[i][j] = min(c[i][j], pom);
  for (int poz = 0; poz <= 3; poz++)
    if (ins(i + x[poz], n) && ins(j + y[poz], m) &&
         ((c[i + x[poz]][j + y[poz]] == 1010 && abs(t[i + x[poz]][j + y[poz]]) >= pom) ||
         (pom < c[i + x[poz]][j + y[poz]] && t[i + x[poz]][j + y[poz]] < 0)))
      dfs(i + x[poz], j + y[poz], max(pom, abs(t[i + x[poz]][j + y[poz]])));
}

int main()
{
  odczyt();
  /* Sortowanie kubelkowe */
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      tab[abs(t[i][j])].push_back(make_pair(i,j));
      c[i][j] = 1010;
    }

  int wyn = 0;
  for (int k = 1; k <= MAX_R; k++)
  {
    for (vector<pair<int, int> >::iterator it = tab[k].begin(); it!=tab[k].end(); ++it)
    {
      pair<int, int> p = *it;
      if (t[p.first][p.second] > 0 && c[p.first][p.second] == 1010)
      {
        wyn++;
        dfs(p.first,p.second,t[p.first][p.second]);
      }
    }
  }
  printf("%d\n", wyn);
  return 0;
}
