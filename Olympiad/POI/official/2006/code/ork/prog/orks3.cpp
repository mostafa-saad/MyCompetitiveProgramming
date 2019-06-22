/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                orks3.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie nieoptymalne, o zlozonosci:        *
 *                        obliczeniowej O((n+m)^3)                       *
 *                        oraz pamieciowej O(n*m)                        *
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


/*czy da sie zaorac pole uprawne wykonujac dokladnie n ciec poziomych oraz    *
 *co najwyzej lewe_ciecia ciec lewych oraz co najwyzej prawe_ciecia ciec      *
 *prawych                                                                     */
int mozna_zaorac(int lewe_ciecia, int prawe_ciecia)
{
  int wa, wb, ka, kb; /*aktualne wymiary pola: gorny wiersz, dolny wiersz,    *
                       *lewa kolumna, prawa kolumna                           */
  wa = ka = 0;
  wb = n - 1;
  kb = m - 1;
  while (wa <= wb)
  {
    if (prawo[wa][ka] - prawo[wa][kb+1] <= k)
      /*mozna wykonac ciecie gorne  */
      wa++;
    else
       if (prawo[wb][ka] - prawo[wb][kb+1] <= k)
         /*mozna wykonac ciecie dolne*/
         wb--;
       else
         if (dol[wa][kb] - dol[wb+1][kb] <= k && prawe_ciecia)
         {
           /*mozna wykonac ciecie prawe*/
           kb--;
           prawe_ciecia--;
         } else
            if (dol[wa][ka] - dol[wb+1][ka] <= k && lewe_ciecia)
            {
              /*ciecie lewe*/
              ka++;
              lewe_ciecia--;
            }
            else
              return 0; /*nie da sie wykonac zadnego ciecia*/
  }
  return 1;
}

void licz()
{
  int wynik = INF;
  for (int i = 0; i < 2; ++i){
    /*wykonujemy dla pola oryginalnego oraz obroconego*/
    licz_sumy();
    for (int lewe_ciecia = 0; lewe_ciecia < m; ++lewe_ciecia)
      for (int prawe_ciecia = 0; prawe_ciecia + lewe_ciecia < m; ++prawe_ciecia)
        if (n + lewe_ciecia + prawe_ciecia < wynik && mozna_zaorac(lewe_ciecia, prawe_ciecia))
          wynik = n + lewe_ciecia + prawe_ciecia;
    transponuj();
  }
  printf("%d\n", wynik);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
