/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      proste szukanie dzielnikow, faktoryzacja bez     *
 *                      optymalizacji symuluje mape przez wyszukiwanie   *
 *                      binarne, nwd(n,m_k) zamiast n                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <cassert>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)
#define FORD(a,b,c) for (int a=(b); a>=(c); --a)
#define FORE(i, cnt) for(__typeof((cnt).begin()) i = (cnt).begin(); i != (cnt).end(); ++i)
#define FORED(i, cnt) for(__typeof((cnt).rbegin()) i = (cnt).rbegin(); i != (cnt).rend(); ++i)
#define MP make_pair
#define PB push_back

using namespace std;

typedef long long LL;

template<class T> 
inline int size(const T &t) { return t.size(); }


LL gcd(LL a, LL b) {
    while(b != 0) {
        a %= b;
        swap(a,b);
    }
    return a;
}

vector<LL> dvs; //dzielniki
vector<LL> pDvs; //dzielniki pierwsze
vector<bool> _good; //dobre dzielniki

vector<bool>::iterator good(LL d) {  // emuluje mapę, klucze w dvs, wartości w _good
    int beg = 0, end = size(_good) - 1;
    int med;
    while(end >= beg) {
        med = (beg + end)/2;
        if (dvs[med] == d) return _good.begin()+med;
        else if (dvs[med] < d) beg = med + 1;
        else end = med - 1; 
    }
    assert(false);
}


void computeDivisors(LL n) { //oblicza dvs i pDvs w czasie O(sqrt(n))
    LL m  = n; //do obliczania pDiv
    dvs.PB(1);
    for (int d = 2; d*(LL)d <= n; ++d) { //dzielniki mniejsze niz sqrt(n)
        if (n%d == 0) {
            dvs.PB(d);
            if (m%d == 0) {
                pDvs.PB(d);
                do m/=d; while (m%d == 0);
            }
        }
    }
    //i pozostale
    if (m != 1) pDvs.PB(m);
    int i = size(dvs) - 1;
    if (dvs[i]*dvs[i] == n) --i; //nie wstawiaj sqrt(n) dwa razy
    for (; i >= 0; --i) dvs.PB(n/dvs[i]);
}

int main() {
    LL n;
    int k;
    LL *m;
    scanf("%lld%d", &n, &k);
    m = new LL[k];
    REP(i, k) {
        scanf("%lld", &m[i]);
    }
    m[k-1] = gcd(n,m[k-1]);
    REP(i, k-1) {
        m[i] = gcd(m[k-1],m[i]);
    }
    computeDivisors(m[k-1]);

    _good = vector<bool>(dvs.size(),true);
    REP(i,k - 1) *good(m[i]) = false;

    LL best = -1; //najlepszy dotychczas znaleziony wynik

    //sprawdzaj od gory dzielniki
    FORED(it, dvs) {
        vector<bool>::iterator git(good(*it));
        if (!*git) continue;
        FORE(jt, pDvs) {
            if ((m[k-1] / (*it)) % (*jt) != 0) continue; //tak napisane nie spowoduje overflowa
            if (!*good(*it * (*jt))) {
                *git = false;
                break;
            }
        }
        if (*git && m[k-1] % (*it) == 0) {
            best = max(best, n / (*it));
        }
    }


    printf("%lld\n",best);
    delete[] m;
    return 0;
}
