/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     konb3.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie niepoprawne prawie wzorcowe, O(n^2*k).        *
 *             W pewnym miejscu przepelnia sie zakres.                   *
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
int best[1010][1010]; // best[o][k] = ilu pasazerow co najmniej trzeba pominac
    // na pierszych o stacjach przy k kontrolach, ostatnia kontrola po stacji o
int poprz[1010][1010]; // oraz kiedy poprzednia kontrola
int wyn[1010];

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
  /// liczenie najlepszych zarobkow
  FOR(k, 1, K)
    FOR(o, 0, N-2)
      if (k==1)
        best[o][k] = prost[0][o];
      else
      {
        best[o][k] = 2000000001;
        FOR(op, 0, o-1)
          if (best[op][k-1]+prost[op+1][o]<best[o][k])
          {  // BLAD - tutaj moze sie przepelnic, bo best[op][k-1] moze byc 2000000001, do niego mozna dodac duzo z prost[op+1][o]
              best[o][k] = best[op][k-1]+prost[op+1][o];
              poprz[o][k] = op;
          }
      }
  // liczenie ogolnego wyniku
  int best_gl = 2000000001;
  int ost = -1;
  FOR(o, 0, N-2)
    if (best[o][K]+prost[o+1][N-1]<best_gl)
    { // BLAD - tutaj rowniez moze sie przepelnic
      best_gl = best[o][K]+prost[o+1][N-1];
      ost = o;
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
