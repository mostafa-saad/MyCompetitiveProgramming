/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                ork.cpp                                        *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Program wzorcowy, o zlozonosci obliczeniowej   *
 *                        oraz pamieciowej O((n + m) ^ 2)                *
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

void transponuj()
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      dol[i][j] = t[i][j];

  swap(n, m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      t[i][j] = dol[j][i];
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

/*obliczanie minimalnej liczby skib, przy zalozeniu ze wykonamy n ciec        *
 *poziomych                                                                   */
int tnij()
{
  int wynik = n + m;
  licz_sumy();
  for (int i = 0; i < m; ++i)
  {
    int prawe_ciecia = i;
    int wa, wb, ka, kb; /*aktualne wymiary pola: gorny wiersz, dolny wiersz,  *
                         *lewa kolumna, prawa kolumna                         */
    wa = ka = 0;
    wb = n - 1;
    kb = m - 1;
    while (wa <= wb && ka <= kb)
    {
      if (prawo[wa][ka] - prawo[wa][kb+1] <= k)
      {
        /*mozna wykonac ciecie gorne  */
        if (wa++ == wb)
          wynik = min(wynik, n + m - (kb - ka + 1));
      } else
        if (prawo[wb][ka] - prawo[wb][kb+1] <= k)
        {
          /*mozna wykonac ciecie dolne*/
          if (wa == wb--)
            wynik = min(wynik, n + m - (kb - ka + 1));
        } else
          if (dol[wa][kb] - dol[wb+1][kb] <= k && prawe_ciecia)
          {
            /*mozna wykonac ciecie prawe*/
            kb--;
            prawe_ciecia--;
          }
          else
            if (dol[wa][ka] - dol[wb+1][ka] <= k)
              ka++; /*ciecie lewe*/
            else
              break; /*nie da sie wykonac zadnego ciecia*/

    }
  }
  return wynik;
}

void licz()
{
  int wynik;
  wynik = tnij();
  transponuj();
  wynik = min(wynik, tnij());
  printf("%d\n", wynik);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
