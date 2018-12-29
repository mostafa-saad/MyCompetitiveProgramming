/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs0.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wykladnicze                                   *
 *                                                                       *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_N 100010

int k, n, m;
int x[MAX_N], y[MAX_N];

inline int p(int pocz, const set<int> &z, int *u)
{
  set<int> z1;
  while (z1 != z)
    z1.insert(u[pocz++]);
  return pocz - 2;
}

inline int s(int kon, const set<int> &z, int *u)
{
  set<int> z1;
  while (z1 != z)
    z1.insert(u[kon--]);
  return kon + 2;
}

/* Funkcja f, liczona z definicji. */
int f(int px, int kx, int py, int ky)
{
  set<int> zx, zy;
  for (int i = px; i <= kx; i++)
    zx.insert(x[i]);
  for (int i = py; i <= ky; i++)
    zy.insert(y[i]);
  if (zx != zy)
    return 0;
  if (zx.size() == 1 && zy.size() == 1 && *(zx.begin()) == *(zy.begin()))
    return 1;
  return f(px, p(px, zx, x), py, p(py, zy, y)) &&
         f(s(kx, zx, x), kx, s(ky, zy, y), ky);
}

int main()
{
  scanf("%d", &k);
  while (k--)
  {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
      scanf("%d", x + i);
    for (int i = 0; i < m; i++)
      scanf("%d", y + i);
    printf("%d\n", f(0, n - 1, 0, m - 1));
  }
  return 0;
}
