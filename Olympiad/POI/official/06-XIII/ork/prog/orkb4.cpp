/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                orkb4.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie niepoprawne, jesli to mozliwe,     *
 *                        to probuje ciac poziomo.                       *
 *                        Zlozonosc O((m + n) ^ 2)                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_N = 2000;      //maksymalny wymiar pola
const int INF = 2*MAX_N;     //maksymalna liczba skib
int n, m;                    //wymiary pola (liczba wierszy, liczba kolumn)
int k;                       //wytrzymalosc szkapy
int t[MAX_N][MAX_N];         //trudnosc pola
int prawo[MAX_N+1][MAX_N+1]; /*suma trudnosci pol od danego pola w prawo,     *
                              *do konca wiersza                               */
int dol[MAX_N+1][MAX_N+1];   /*suma trudnosci pol od danego pola d dol,       *
                              *do konca kolumny                               */

/*wczytywanie danych wejsciowych*/
void czytaj()
{
  scanf("%d %d %d", &k, &m, &n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &t[i][j]);
}

void licz_sumy()
{
  /*liczenie sum czesciowych*/
  for (int i = 0; i <= n; ++i)
    dol[i][m] = prawo[i][m] = 0;

  for (int j = 0; j <= m; ++j)
    dol[n][j] = prawo[n][j] = 0;

  for (int i = n - 1; i >= 0; --i)
    for (int j = m - 1; j >= 0; --j)
    {
      dol[i][j] = t[i][j] + dol[i+1][j];
      prawo[i][j] = t[i][j] + prawo[i][j+1];
    }
}

void licz()
{
  int wynik = 0;
  licz_sumy();
  int wa, wb, ka, kb; /*aktualne wymiary pola: gorny wiersz, dolny wiersz,  *
                       *lewa kolumna, prawa kolumna                         */
  wa = ka = 0;
  wb = n - 1;
  kb = m - 1;
  while (wa <= wb && ka <= kb)
  {
    wynik++;
    /*probujemy wykonac ciecie poziome*/
    if (prawo[wa][ka] - prawo[wa][kb+1] <= k)
      wa++;
    else
      if (prawo[wb][ka] - prawo[wb][kb+1] <= k)
        wb--;
      else
      /*probujemy wykonac ciecie pionowe*/
        if (dol[wa][kb] - dol[wb+1][kb] <= k)
          kb--;
        else
          ka++;
  }
  printf("%d\n",wynik);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
