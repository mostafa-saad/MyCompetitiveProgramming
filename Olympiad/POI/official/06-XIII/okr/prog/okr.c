/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okr.c                                          *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie optymalne.                         *
 *                        Zlozonosc obliczeniowa O(n)                    *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int n, p[1000001], s[1000001];
long long sum = 0;
char t[1000001];

int main()
{
  int i, j;

  scanf("%d %s", &n, t);
  p[0] = -1;
  s[0] = 0;
  for (i = 0, j = -1; i <= n-1; i++,j++,p[i]=j)
    while (j >= 0 && t[i] != t[j]) j = p[j];
  for (i = 1; i <= n; i++)
  {
    s[i] = p[p[i]] <= 0 ? p[i] : s[p[i]];
    sum += s[i] + (!p[i] ? i : 0);
  }
  
  printf("%lld\n", (long long)n * (n + 1) / 2 - sum);
  return 0;
}
