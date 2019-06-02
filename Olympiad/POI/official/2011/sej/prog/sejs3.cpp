/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(k*nwd(n, m_k))                                 *
 *   Opis:              Rozwiazanie powolne                              *
 *                      brutalnie probuje wszystkie liczby po kolei      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)

using namespace std;

typedef long long LL;

/////////////////////////////////
const int MAXK = 250000;
int K;
LL N, M[MAXK];
int main()
{
    scanf("%Ld%d", &N, &K);
    REP(a, K)
        scanf("%Ld", &M[a]);
    FOR(d, 1, N) {
        if (N%d || M[K-1]%d)
            continue;
        REP(a, K-1) {
            if (M[a]%d==0)
                goto zle;
        }
        printf("%Ld\n", N/d);
        return 0;
zle:;
    }
}
