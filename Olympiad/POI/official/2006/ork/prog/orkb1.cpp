/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ORK (Orka)                                     *
 *   Plik:                orkb1.cpp                                      *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wolne o zlozonosci obliczeniowej   *
 *                        oraz pamieciowej O(n^2 * m^2)                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_N = 85;       /*maksymalny wymiar pola, zmniejszony z powodu   *
                             *wiekszego zapotrzebowania na pamiec            */
const unsigned char INF = 2*MAX_N;     //maksymalna liczba skib
int n, m;                    //wymiary pola (liczba wierszy, liczba kolumn)
int k;                       //wytrzymalosc szkapy
int t[MAX_N][MAX_N];         //trudnosc pola
int prawo[MAX_N+1][MAX_N+1]; /*suma trudnosci pol od danego pola w prawo,     *
                              *do konca wiersza                               */
int dol[MAX_N+1][MAX_N+1];   /*suma trudnosci pol od danego pola d dol,       *
                              *do konca kolumny                               */
unsigned char mem[MAX_N][MAX_N][MAX_N][MAX_N];      /*tablica do spamietywania*/

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

int val(int wa,int wb,int ka, int kb){
  if (wa>wb || ka>kb) return 0;
  if (mem[wa][wb][ka][kb]<INF) return mem[wa][wb][ka][kb];
  int wynik=INF;
  if (prawo[wa][ka] - prawo[wa][kb+1] <= k)
    /*mozna wykonac ciecie gorne  */
    wynik=min(wynik,val(wa+1,wb,ka,kb)+1);
  if (prawo[wb][ka] - prawo[wb][kb+1] <= k)
    /*mozna wykonac ciecie dolne*/
    wynik=min(wynik,val(wa,wb-1,ka,kb)+1);
  if (dol[wa][kb] - dol[wb+1][kb] <= k)
    /*mozna wykonac ciecie prawe*/
    wynik=min(wynik,val(wa,wb,ka,kb-1)+1);
  if (dol[wa][ka] - dol[wb+1][ka] <= k)
    /*mozna wykonac ciecie lewe*/
    wynik=min(wynik,val(wa,wb,ka+1,kb)+1);
  return mem[wa][wb][ka][kb]=wynik;
}

void licz()
{
  licz_sumy();
  for (int a=0; a<n; ++a)
    for (int b=a; b<n; ++b)
      for (int c=0; c<m; ++c)
        for (int d=c; d<m; ++d)
          mem[a][b][c][d]=INF;
  printf("%d\n",val(0,n-1,0,m-1));
}

int main()
{
  czytaj();
  licz();
  return 0;
}
