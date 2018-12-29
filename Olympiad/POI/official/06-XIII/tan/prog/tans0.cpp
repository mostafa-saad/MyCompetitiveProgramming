/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans0.cpp                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

#define FOR(a,b,c) for(int a=(b);a<=(c);++a)
#define FORD(a,b,c) for(int a=(b);a>=(c);--a)
#define REP(a,b) FOR(a,0,(b)-1)

#define MOD 2005
#define MAXN 2500000

int N,K,L;
int wyniki[2][MAXN+1], s = 0;
int mn[MAXN];

int calcul()
{
  if (K*L>N)
    return 0;
  if (N>MAXN) for(;;);
  FOR(n, L, N)
  {
    mn[n] = 1;
    FOR(a, n-L+1, n-1)
      mn[n] = mn[n]*a%MOD;
  }
  REP(n, N+1)
    wyniki[s][n] = 0;
  wyniki[s][0] = 1;
  FOR(k, 1, K)
  {
    s = !s;
    REP(n, k*L)
      wyniki[s][n] = 0;
    FOR(n, k*L, N)
      wyniki[s][n] = ((n-1)*wyniki[s][n-1]+mn[n]*wyniki[!s][n-L])%MOD;
  }
  return wyniki[s][N];
}

int main()
{
  scanf("%d%d%d", &N, &K, &L);
  printf("%d\n", calcul());
}
