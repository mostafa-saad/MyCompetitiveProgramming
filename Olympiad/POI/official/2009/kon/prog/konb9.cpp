/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     konb9.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Bledne rozwiazanie zachlanne, przestawia kontrole         *
 *             tak dlugo jak to cos poprawia.                            *
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
int wyn[1010];
int best;

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
  // poczatkowe rownomierne rozwiazanie
  wyn[0] = -1;
  wyn[K+1] = N-1;
  REP(a, K)
    wyn[a+1] = a;//(2*a+1)*(N-1)/2/K;
  best = 0;
  REP(a, K+1)
    best += prost[wyn[a]+1][wyn[a+1]];
  // poprawianie
//  fprintf(stderr, "best=%d\n", best);
  bool ch = true; // czy trzeba dalej poprawiac
  while (ch)
  {
      ch = false;
      FOR(k, 1, K)
      {
        bool bylo = false;
        while (wyn[k]>wyn[k-1]+1) // posuwaj ta kontrole wczesniej
        {
          int popr = -prost[wyn[k-1]+1][wyn[k]  ]-prost[wyn[k]+1  ][wyn[k+1]]
                     +prost[wyn[k-1]+1][wyn[k]-1]+prost[wyn[k]+1-1][wyn[k+1]];
          if (popr<0) // bedzie lepiej
          {
              --wyn[k];
              best += popr;
//              fprintf(stderr, " %d leci w lewo, best=%d\n", k, best);
              ch = true;
              bylo = true;
          }
          else break;
        }
        if (bylo) // jak sie oplacaco posuwac w lewo, to nie ma po co znowu w prawo
           continue;
        while (wyn[k]<wyn[k+1]-1) // posuwaj ta kontrole dalej
        {
          int popr = -prost[wyn[k-1]+1][wyn[k]  ]-prost[wyn[k]+1  ][wyn[k+1]]
                     +prost[wyn[k-1]+1][wyn[k]+1]+prost[wyn[k]+1+1][wyn[k+1]];
          if (popr<0) // bedzie lepiej
          {
              ++wyn[k];
              best += popr;
//              fprintf(stderr, " %d leci w prawo, best=%d\n", k, best);
              ch = true;
          }
          else break;
        }
      }
  }
  // wypisywanie wyniku
  REP(k, K)
    printf("%d%s", wyn[k+1]+1, k==K-1 ? "\n" : " ");
//  fprintf(stderr, "%d\n", best);
}
