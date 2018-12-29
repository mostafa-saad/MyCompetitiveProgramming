/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tan2.cpp                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

#define FOR(a,b,c) for(int a=(b);a<=(c);++a)
#define FORD(a,b,c) for(int a=(b);a>=(c);--a)
#define REP(a,b) FOR(a,0,(b)-1)

#define F1 5
#define F2 401
#define MAXN F2

int comb[F1][F2];

int N,K,L;
int wyniki[2][MAXN+1], s = 0;
int mn[MAXN];

int calcul(int MOD, int N, int K)
{
  if (N>MAXN || ((long long)K)*L>N)
    return 0;
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

int calc(int MOD)
{
  int cp = N/MOD;
  int nK = K-cp;
  if (nK<0 || MOD<L) return 0;
  int res = calcul(MOD, N%MOD, nK);
  if (cp&1)
    res = res*(MOD-1)%MOD;
  return res;
}

int main()
{
  REP(a, F1*F2)
    comb[a%F1][a%F2] = a;
  scanf("%d%d%d", &N, &K, &L);
  printf("%d\n", comb[calc(F1)][calc(F2)]);
}
