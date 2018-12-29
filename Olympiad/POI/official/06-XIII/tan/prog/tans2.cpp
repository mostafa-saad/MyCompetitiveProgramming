/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans2.cpp                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Z³o¿ono¶æ czasowa O(n^2 * k), pamiêciowa O(n^2)*
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

#define FOR(a,b,c) for(int a=(b);a<=(c);++a)
#define FORD(a,b,c) for(int a=(b);a>=(c);--a)
#define REP(a,b) FOR(a,0,(b)-1)

#define MOD 2005
#define MAXN 1000

int N, K, L;

int choose[MAXN+1][MAXN+1];

int tab[MAXN+1][MAXN+1];

int main()
{
  scanf("%d%d%d", &N, &K, &L);
  if (N>MAXN) for(;;);
  REP(n, N+1)
  {
    choose[n][1] = 1;
    FOR(i, 2, n)
      choose[n][i] = (n-i+1)*choose[n][i-1]%MOD;
  }
  REP(n, N+1)
    REP(k, K+1)
      tab[n][k] = 0;
  tab[0][0] = 1;
  FOR(k, 1, K)
    FOR(n, k*L, N)
    {
      tab[n][k] = 0;
      FOR(i, L, n-(k-1)*L)
        tab[n][k] = (tab[n][k]+choose[n][i]*tab[n-i][k-1])%MOD;
    }
  printf("%d\n", tab[N][K]);
}
