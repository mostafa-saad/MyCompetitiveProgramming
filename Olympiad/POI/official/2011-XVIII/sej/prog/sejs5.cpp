/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(sqrt(n)+k*liczba_dzielnikow(n))                *
 *   Opis:              Rozwiazanie powolne                              *
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

vector<pair<LL, int> > rozloz(LL N) { // zwraca liste dzielnikow pierwszych+liczba wielokrotnosci
    vector<pair<LL, int> > ret;
    for (int p = 2; p*(LL)p<=N; ++p) {
        int ile = 0;
        while (N%p==0) {
            ++ile;
            N /= p;
        }
        if (ile)
            ret.PB(MP(p, ile));
    }
    if (N>1)
        ret.PB(MP(N, 1));
    return ret;
}

vector<LL> znajdz_dzielniki(LL N) { // zwraca posortowana liste dodatnich dzielnikow liczby N (w tym 1 i N)
    vector<pair<LL, int> > dziel_pier = rozloz(N);
    vector<int> ile(size(dziel_pier)); // ile razy bierzemy ktora liczbe pierwsza
    vector<LL> ret;
    for (LL dz = 1;;) {
        ret.PB(dz);
        for (int a = 0;; ++a)
            if (a>=size(ile)) {
                sort(ret.begin(), ret.end());
                return ret;
            }
            else
            if (ile[a]<dziel_pier[a].second) {
                ++ile[a];
                dz *= dziel_pier[a].first;
                break;
            }
            else
                while (ile[a]) {
                    --ile[a];
                    dz /= dziel_pier[a].first;
                }
    }
}
int K;
LL N, M[MAXK];
void permutuj() { // permutuje kolejnosc m_1,...,m_{k-1}
    srand(K*35326+53435353);
    REP(a, K-1) {
        int x = rand()%(K-1-a);
        swap(M[x], M[K-1-a-1]);
    }
}

LL NWD(LL a, LL b) {
	return b ? NWD(b, a%b) : a;
}



int main()
{
    scanf("%Ld%d", &N, &K);
    REP(a, K)
        scanf("%Ld", &M[a]);
    permutuj();
    vector<LL> dzielniki = znajdz_dzielniki(NWD(M[K-1],N));
    REP(a, size(dzielniki)) {
        LL d = dzielniki[a];
        REP(a, K-1){
            if (M[a]%d==0)
                goto zle;

        }

            printf("%Ld\n", N/d);
            return 0;
zle:;
    }
}
