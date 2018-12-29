/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     posb6.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne.                                       *
 *                                                                       *
 *************************************************************************/

#include "poslib.h"
#include <algorithm>
using namespace std;

int n, a, b;

/* Programowanie dynamiczne */
#define MX 1000000
int t[MX + 1];

void dp()
{
  for (int i = 0; i < max(a, b); i++)
    t[i] = 1;
  for (int i = max(a, b); i <= MX; i++)
  {
    t[i] = t[i - a] + t[i - b];
    t[i] = min(t[i], n + 1);
  }
}

int main()
{
  inicjuj(&n, &a, &b);
  if (n == 1)
    odpowiedz(1);

  dp();
  int l = 1, h = n;
  int akt = MX;
  while (t[akt] >= n)
    akt--;
  akt++;
  while (l < h)
  {
    int poz = t[akt - b];
    if (pytaj('W', l + poz - 1))
    {
      akt -= a;
      l = l + poz;
    } else
    {
      akt -= b;
      h = l + poz - 1;
    }
  }
  odpowiedz(l);
  return 0;
}
