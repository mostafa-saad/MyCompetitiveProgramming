/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb9.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Bledna wersja rozwiazania sprowadzajacego do postaci      *
 *             kanonicznej. Porownuje pierwsze elementy wierszy a nie    *
 *             najmniejsze.                                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 1000

int ile, n, m;
int t1[MAX_N][MAX_N], t2[MAX_N][MAX_N];

int tp[MAX_N][MAX_N];

/* Sprowadzenie do postaci kanonicznej: wiersze posortowane po
 * najmniejszych elementach, pierwszy wiersz posortowany. */
void sprowadz(int t[MAX_N][MAX_N])
{
  /* Pierwszy krok */
  vector<pair<int, int> > pom;
  for (int i = 0; i < n; i++)
    pom.push_back(make_pair(t[i][0], i));  // BLAD: tu powinno byc minimum z wiersza!
  sort(pom.begin(), pom.end());
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      tp[i][j] = t[pom[i].second][j];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      t[i][j] = tp[i][j];

  /* Drugi krok */
  pom.clear();
  for (int j = 0; j < m; j++)
    pom.push_back(make_pair(t[0][j], j));
  sort(pom.begin(), pom.end());
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      tp[i][j] = t[i][pom[j].second];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      t[i][j] = tp[i][j];
}

void zam(int t[MAX_N][MAX_N])
{
  for (int i = 0; i < max(n, m); i++)
    for (int j = 0; j < i; j++)
      swap(t[i][j], t[j][i]);
}

int main()
{
  scanf("%d", &ile);
  while (ile--)
  {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        scanf("%d", t1[i] + j);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        scanf("%d", t2[i] + j);
    zam(t1);
    zam(t2);
    swap(n,m);
    sprowadz(t1);
    sprowadz(t2);
    bool ok = true;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (t1[i][j] != t2[i][j])
          ok = false;
    puts(ok ? "TAK" : "NIE");
  }
  return 0;
}
