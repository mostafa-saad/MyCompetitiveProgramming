/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                metb1.cpp                                      *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Prosta heurystyka - zlicza ilosc lisci i na    *
 *                        tej podstawie wypisuje odpowiedz.              *
 *                        Zlozonosc obliczeniowa: O(n)                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>

#define MAXN 1000000

using namespace std;

int deg[MAXN];
int n, l, sum = 0;

int main()
{
  scanf("%d %d", &n, &l);
  memset(deg, 0, sizeof(deg));
  for (int i = 0; i < 2*n-2; i++)
  {
    int a;
    scanf("%d", &a);
    deg[a-1]++;
  }
  for (int i = 0; i < n; i++)
    if (deg[i] == 1) sum++;
  if (sum <= 2 * l) printf("%d\n", n);
  else printf("%d\n", (int)(n / 2 + (long long)l * n / sum));
  return 0;
}
