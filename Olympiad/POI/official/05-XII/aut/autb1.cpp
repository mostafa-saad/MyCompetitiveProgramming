/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: AUT (Autobus)                                  *
 *   Plik:                autb1.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Program daje poprawna odpowiedz, jesli         *
 *                        mapa miasta (wszystkie skrzyzowania)           *
 *                        miesci sie w pamieci. Zlozonosc obliczeniowa   *
 *                        oraz pamieciowa to O(n^2).                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
int n, m, k;
const int MAXK = 100000;
const int MAXN = 2000;
int t[MAXN][MAXN];

void czytaj()
{
  scanf("%d %d %d", &n, &m, &k);
  //wczytywanie przystankow
  for (int i = 0; i < k; ++i) {
    int x, y, p;
    scanf("%d %d %d", &x, &y, &p);
    t[x][y] += p;
  }
}

void licz()
{
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      int best = 0;
      if (i > 1)
        best >?= t[i - 1][j];
      if (j > 1)
        best >?= t[i][j - 1];
      t[i][j] += best;
    }
  printf("%d\n", t[n][m]);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
