/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     kons7.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie nieefektywne O(n^3*k).                        *
 *             Zamiast zrobic preprocesing, to za kazdym razem sumuje    *
 *             wartosci z wejscia.                                       *
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
int best[1010][1010]; // best[o][k] = ilu pasazerow maksymalnie skontroluje
    // na pierszych o stacjach przy k kontrolach, ostatnia kontrola po stacji o
int poprz[1010][1010]; // oraz kiedy poprzednia kontrola
int wyn[1010];

int main()
{
  scanf("%d%d", &N, &K);
  REP(a, N)
    FOR(b, a+1, N-1)
      scanf("%d", &pas[a][b]);
  /// liczenie najlepszych zarobkow
  FOR(o, 0, N-K-1) // dla pierwszej kontroli - gdzie ma byc
  {
    int suma = 0;
    FOR(ws, 0, o)
      FOR(wys, o+1, N-1)
        suma += pas[ws][wys];
    // suma = ile wsiadlo na <=o i wysiadlo na >=o+1
    best[o][1] = suma;  
  }
  FOR(k, 2, K) // kolejne kontrole
    FOR(o, k-1, N-K+k-2)
    {
      int suma = 0;
      best[o][k] = -1;
      FORD(op, o-1, k-2)
      {
        FOR(wys, o+1, N-1) // dodajemy wszystkich, ktorzy wsiedli na op+1
            suma += pas[op+1][wys];
        // suma = ile wsiadlo na >=op+1, <=o i wysiadlo na >=o+1
        if (best[op][k-1]+suma>best[o][k])
        {
            best[o][k] = best[op][k-1]+suma;
            poprz[o][k] = op;
        }
      }
    }
  // liczenie ogolnego wyniku
  int best_gl = -1;
  int ost = -1;
  FORD(o, N-2, K-1)
  {
    if (best[o][K]>best_gl)
    {
      best_gl = best[o][K];
      ost = o;
    }
  }
  // gdzie trzeba sprawdzac
  FORD(k, K-1, 0)
  {
    wyn[k] = ost;
    ost = poprz[ost][k+1];
  }
  REP(k, K)
    printf("%d%s", wyn[k]+1, k==K-1 ? "\n" : " ");
//  {int suma = 0; REP(a, N) FOR(b, a+1, N-1) suma += pas[a][b]; fprintf(stderr, "%d\n", suma-best_gl); }
}
