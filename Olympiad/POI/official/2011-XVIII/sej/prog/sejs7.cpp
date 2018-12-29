/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Pawel Parys, Tomasz Kociumaka                    *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n)+liczbadzielnikow(n)^2)        *
 *   Opis:              Rozwiazanie powolne                              *
 *                      przerywa po znalezieniu d i swiadka, kolejnosc   *
 *                      rosnace                                          *
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
LL gcd(LL a, LL b) {
    while(b != 0) {
        a %= b;
        swap(a,b);
    }
    return a;
}

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

int main() {
    scanf("%Ld%d", &N, &K);
    REP(a, K) {
        scanf("%Ld", &M[a]);
        M[a] = gcd(M[a],N);
    }
    sort(M, M+K-1);
    LL* end = unique(M,M+K-1);
    int L = end - M;
    M[L] = M[K-1];
    K = L+1;
    //for (int i = 0; i < K; ++i) printf("%lld\n",M[i]);
    vector<LL> dzielniki = znajdz_dzielniki(N);
    REP(a, size(dzielniki)) {
        LL d = dzielniki[a];
        bool ok = true;
        if (N%d || M[K-1]%d)
            continue;
        REP(a, K-1)
            if (M[a]%d==0) {
                ok = false;
                break;
            }
        if (ok) {
            printf("%lld\n",N/d);
            return 0;
        }
    }
    return 0;
}
