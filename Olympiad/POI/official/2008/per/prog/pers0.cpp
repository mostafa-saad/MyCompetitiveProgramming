/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     pers0.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Generuje kolejne permutacje.                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 500000

int n, m;
int t[MAX_N], tab[MAX_N];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", t + i);
  for (int i = 0; i < n; i++)
    tab[i] = t[i];
  sort(tab, tab + n);
  int wyn = 1;
  do
  {
    bool ok = true;
    for (int i = 0; i < n; i++)
      if (tab[i] != t[i])
      {
        ok = false;
        break;
      }
    if (ok)
      break;
    wyn++;
  } while (next_permutation(tab, tab + n));
  printf("%d\n", wyn % m);
  return 0;
}
