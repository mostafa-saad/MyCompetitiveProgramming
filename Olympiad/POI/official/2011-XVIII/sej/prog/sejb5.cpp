/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie bledne: wzorcowka z bledem:          *
 *                      zapomina czasem o long longach                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>

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


void factor(LL n) { //oblicza pDvs oraz pDvsMul w czasie O(sqrt(n))
    for (int d = 2; d*(LL)d <= n; ++d) { //dzielniki mniejsze niz sqrt(n)
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
    //i pozostale
    if (n != 1) {
        pDvs.PB(n);
        pDvsMlt.PB(1);
    }
}
// generuje wszystkie dzielniki; czas: wynik*log(wynik) + factor
void computeDivisors(LL n) {   
    factor(n);
    vector<int> deg(pDvs.size(),0);
    int val = 1; //  <---------------- tu brakuje LL
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

    map<LL, bool> good; //czy dzielnik nie dzieli zadnej z liczb m_i
    FORE(it, dvs) good[*it] = true;
    REP(i,k - 1) good[m[i]] = false;

    LL best = -1;

    //sprawdzaj od gory dzielniki
    FORED(it, dvs) {
        if (!good[*it]) continue;
        FORE(jt, pDvs) {
            if ((n/(*it)) % (*jt) != 0) continue; //tak napisane nie spowoduje overflowa
            if (!good[*it * (*jt)]) {
                good[*it] = false;
                break;
            }
        }
        if (good[*it] && m[k-1] % (*it) == 0) {
            best = max(best, n / (*it));
        }
    }
    printf("%Ld\n",best);
    delete[] m;
    return 0;
}
