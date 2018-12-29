/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     kons8.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wykladnicze                                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)
#define FORD(a,b,c) for (int a=(b); a>=(c); --a)

using namespace std;

int N, K;
int pas[1010][1010]; // tablica z wejscia
int prost[1010][1010]; // ilu wsiadlo na >=a i wysiadlo <=b
int best = 2000000001;
int cur_tab[1010]; // aktualnie wybrane stacje do kontroli
int best_tab[1010]; // stacje do kontroli w najlepszym rozwiazaniu

void licz(int ile, int poprz, int wynik) {
    if (wynik>=best) // obcinamy jak juz teraz gorzej niz najlepszy
        return;
    if (ile==K) { // jest K konroli
        wynik += prost[poprz+1][N-1]; // nieskontrolowani po ostatniej kontroli
        if (wynik<best) {
            REP(a, K)
              best_tab[a] = cur_tab[a];
            best = wynik;
        }
        return;
    }
    FOR(gdzie, poprz+1, N-K+ile-1)
    {
        cur_tab[ile] = gdzie;
        licz(ile+1, gdzie, wynik+prost[poprz+1][gdzie]);
    }
}

int main()
{
  scanf("%d%d", &N, &K);
  REP(a, N)
    FOR(b, a+1, N-1)
      scanf("%d", &pas[a][b]);
  /// preprocesing - liczenie tablicy prost
  REP(b, N)
    FORD(a, b-1, 0)
      prost[a][b] = pas[a][b]+prost[a][b-1]+prost[a+1][b]-prost[a+1][b-1];
  // rekurencyjne szukanie rozwiazania
  licz(0, -1, 0);
  // wypisywanie wyniku
  REP(k, K)
    printf("%d%s", best_tab[k]+1, k==K-1 ? "\n" : " ");
//  fprintf(stderr, "%d\n", best);
}
