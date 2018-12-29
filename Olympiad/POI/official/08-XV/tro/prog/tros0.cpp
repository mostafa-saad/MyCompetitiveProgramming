/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tros0.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie nieoptymalne.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define MAX_N 3000

int n;
struct punkt
{
  unsigned int x, y;
} t[MAX_N];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u%u", &(t[i].x), &(t[i].y));
  unsigned long long wyn = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      for (int k = j + 1; k < n; k++)
        wyn += abs((t[j].x - t[i].x) * (t[k].y - t[i].y) -
                   (t[k].x - t[i].x) * (t[j].y - t[i].y));
  if (wyn & 1)
    printf("%llu.5\n", wyn >> 1);
  else
    printf("%llu.0\n", wyn >> 1);
  return 0;
}
