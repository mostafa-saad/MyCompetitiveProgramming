/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(k)                                             *
 *   Opis:              Rozwiazanie bledne, zwraca zwraca n/nwd(n,m_k)   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)
#define MP make_pair
#define PB push_back

using namespace std;

typedef long long LL;

template<class T> 
inline int size(const T &t) { return t.size(); }

const int MAXK = 250000;

/////////////////////////////////

LL NWD(LL a, LL b) {
	return b ? NWD(b, a%b) : a;
}

int K;
LL N, M[MAXK];

int main() {
    scanf("%Ld%d", &N, &K);
    REP(a, K)
        scanf("%Ld", &M[a]);
    printf("%Ld\n", N/NWD(N,M[K-1]));
}
