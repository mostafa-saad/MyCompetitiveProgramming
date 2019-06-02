/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     konb11.cpp                                                *
 *   Autor:    Jakub Radowszewski                                        *
 *   Opis:     Rozwiazanie bledne. Bierze k najwiekszych.                *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAX_N 600

int n, k;
int x[MAX_N][MAX_N];

void odczyt()
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      scanf("%d", x[i] + j);
}

pair<int, int> bilety[MAX_N];
int wynik[MAX_N];

int main()
{
  odczyt();

  for (int i = 0; i < n - 1; i++)
    bilety[i].second = i;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      for (int k = i; k < j; k++)
        bilety[k].first += x[i][j];

  sort(bilety, bilety + n - 1);
  reverse(bilety, bilety + n - 1);
  for (int i = 0; i < k; i++)
    wynik[i] = bilety[i].second + 1;
  sort(wynik, wynik + k);
  for (int i = 0; i < k; i++)
  {
    printf("%d", wynik[i]);
    if (i < k - 1)
      putchar(' ');
    else
      puts("");
  }
  return 0;
}
