/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      szybkie generowanie dzielnikow i faktoryzacja    *
 *                      symuluje mapę przez wyszukiwanie binarne         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
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
vector<int> pDvsMlt; //dzielniki pierwsze z krotnosciami
vector<LL> pDvs;
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


void factor(LL n) { //oblicza pDvs oraz pDvsMul w czasie O(sqrt(n))
    for (int d = 2; d*(LL)d <= n; ++d) { 
        if (n%d == 0) {
            int cnt = 0;
            do {
                n/=d;
                ++cnt;
            } while (n%d == 0);
            pDvs.PB(d);
            pDvsMlt.PB(cnt);
        }
    }
    if (n != 1) {
        pDvs.PB(n);
        pDvsMlt.PB(1);
    }
}

// generuje wszystkie dzielniki; czas: wynik*log(wynik) + factor
void computeDivisors(LL n) {   
    factor(n);
    vector<int> deg(pDvs.size(), 0);
    LL val = 1;
    while(true) {
        dvs.PB(val);
        if (val == n) break;
        for (int i = size(pDvs) - 1; i>= 0; --i) {
            if (deg[i] < pDvsMlt[i]) {
                ++deg[i];
                val *= pDvs[i];
                break;
            } else {
                for (int j = deg[i]; j>0; --j) {
                    --deg[i];
                    val /= pDvs[i];
                }
            }
        }
    }
    sort(dvs.begin(), dvs.end());
}

int main() {
    LL n;
    int k;
    LL *m;
    scanf("%lld%d", &n, &k);
    m = new LL[k];
    REP(i, k) {
        scanf("%lld", &m[i]);
        m[i] = gcd(m[i], n);
    }
    computeDivisors(n);

    _good = vector<bool>(dvs.size(),true);
    REP(i,k - 1) *good(m[i]) = false;

    LL best = -1; //najlepszy dotychczas znaleziony wynik

    //sprawdzaj od gory dzielniki
    FORED(it, dvs) {
        vector<bool>::iterator git(good(*it));
        if (!*good(*it)) continue;
        FORE(jt, pDvs) {
            if ((n / (*it)) % (*jt) != 0) continue; //tak napisane nie spowoduje overflowa
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
