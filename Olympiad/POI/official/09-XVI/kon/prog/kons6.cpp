/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     kons6.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie nieefektywne O(n^4*k). Zamiast robic          *
 *             preprocesing, to za kazdym razem liczy sume.              *
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
int best[1010][1010]; // best[o][k] = ilu pasazerow co najmniej trzeba pominac
    // na pierszych o stacjach przy k kontrolach, ostatnia kontrola po stacji o
int poprz[1010][1010]; // oraz kiedy poprzednia kontrola
int wyn[1010];

int prost(int pocz, int kon) // ilu wsiadlo na >=pocz i wysiadlo <=kon
{
    int suma = 0;
    FOR(ws, pocz, kon-1)
      FOR(wys, ws+1, kon)
        suma += pas[ws][wys];
    return suma;
}

int main()
{
  scanf("%d%d", &N, &K);
  REP(a, N)
    FOR(b, a+1, N-1)
      scanf("%d", &pas[a][b]);
  /// liczenie najlepszych zarobkow
  FOR(k, 1, K)
    FOR(o, k-1, N-K+k-2)
      if (k==1)
        best[o][k] = prost(0, o);
      else
      {
        best[o][k] = 2000000001;
        FOR(op, k-2, o-1)
        {
          int nowy = best[op][k-1]+prost(op+1, o);
          if (nowy<best[o][k])
          {
              best[o][k] = nowy;
              poprz[o][k] = op;
          }
        }
      }
  // liczenie ogolnego wyniku
  int best_gl = 2000000001;
  int ost = -1;
  FOR(o, K-1, N-2)
  {
    int nowy = best[o][K]+prost(o+1, N-1);
    if (nowy<best_gl)
    {
      best_gl = nowy;
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
//  fprintf(stderr, "%d\n", best_gl);
}
