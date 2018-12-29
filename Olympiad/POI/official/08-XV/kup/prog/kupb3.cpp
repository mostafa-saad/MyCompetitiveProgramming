/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kupb3.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie niepoprawne. Generuje duzo losowych           *
 *             prostokatow i sprawdza, czy ktorys z nich nie spelnia     *
 *             wymagan.                                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX_N = 2000;

int k, n;
int mapa[MAX_N][MAX_N];

inline int los(int m)
{
  return (int)(double(m) * (rand() / (RAND_MAX + 1.0)));
}

long long sumy[MAX_N][MAX_N];

void licz_sumy()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      sumy[i][j] = mapa[i][j] + (j > 0 ? sumy[i][j - 1] : 0);
  for (int j = 0; j < n; j++)
    for (int i = 0; i < n; i++)
      sumy[i][j] += (i > 0 ? sumy[i - 1][j] : 0);
}

inline long long suma(int x1, int y1, int x2, int y2)
{
  long long wyn = sumy[x2][y2];
  if (x1 > 0)
    wyn -= sumy[x1 - 1][y2];
  if (y1 > 0)
    wyn -= sumy[x2][y1 - 1];
  if (x1 > 0 && y1 > 0)
    wyn += sumy[x1 - 1][y1 - 1];
  return wyn;
}

int main()
{
  srand(214565);
  scanf("%d%d", &k, &n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      scanf("%d", mapa[i] + j);
  int x1, y1, x2, y2;
  licz_sumy();
  for (int krok = 0; krok < 10000000; krok++)
  {
    x1 = los(n); x2 = los(n);
    if (x1 > x2)
      swap(x1, x2);
    y1 = los(n); y2 = los(n);
    if (y1 > y2)
      swap(y1, y2);
    long long s = suma(x1, y1, x2, y2);
    if (s >= (long long)k && s <= 2LL * k)
    {
      x1++; y1++; x2++; y2++;
      printf("%d %d %d %d\n", y1, x1, y2, x2);
      return 0;
    }
  }
  puts("NIE");
  return 0;
}
