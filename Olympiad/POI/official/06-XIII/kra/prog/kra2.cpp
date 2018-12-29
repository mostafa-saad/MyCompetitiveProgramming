/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kra2.cpp                                       *
 *   Autor:               Marek ¯ylak                                    *
 *   Opis:                Rozwiazanie alternatywne zadania Krazki.       *
 *                        Zlozonosc: O(n+m)                              *
 *                                                                       *
 *************************************************************************/

/* autor: Marek ¯ylak */

#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> w(n, 0);

  scanf("%d", &(w[0]));
  for (int i = 1; i < n; i++) {
    scanf("%d", &(w[i]));
    w[i] = min(w[i], w[i-1]);
  }

  int d = n;
  for (int i = 0; i < m; i++) {
    int x;
    scanf("%d", &x);
    while (d>0 && w[d-1]<x) d--;
    d--;
  }

  printf("%d\n", max(0, d + 1));
  return 0;
}
