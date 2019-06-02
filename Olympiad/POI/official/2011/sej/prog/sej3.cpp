/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      nie korzysta z mapy, lecz z pozycyjnej           *
 *                      reprezentacji dzielnikow - zyskujemy czynnik     *
 *                      log(liczba dzielnikow), ale w fazie              *
 *                      asymptotycznie zdominowanej przez faktoryzacje   *
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

LL gcd(LL a, LL b) {
    while(b != 0) {
        a %= b;
        swap(a,b);
    }
    return a;
}


vector<int> pDvsMlt; //dzielniki pierwsze z krotnosciami
vector<LL> pDvs;
int P; //ile jest tych dzielników

vector<bool> good; //dobre dzielniki

// dzielniki liczby n utożsamiamy z wektorami wykładników w rozkładzie na czynniki,
// a te zaś mają indeks w porządku lex, konwertery poniżej

LL indexToValue(int pos) {
    LL res = 1;
    REP(i, P) {
        int dig = pos % (pDvsMlt[i] + 1);
        pos /= (pDvsMlt[i] + 1);
        REP(j, dig) res *= pDvs[i];
    }
    return res;
}

int valueToIndex(LL d) {
    int index = 0;
    FORD(i, P-1, 0) {
        index *= (pDvsMlt[i] + 1);
        while(d % pDvs[i] == 0) {
            d /= pDvs[i];
            ++index;
        }
    }
    return index;

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
    P = pDvs.size();
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

    factor(n);
    
    int *offset = new int[P+1]; 
    int off = 1;
    offset[0] = 1;
    REP(i, P) {
        off *= (pDvsMlt[i]+1);
        offset[i+1] = off;
    }

    good = vector<bool>(off,true);
    REP(i, k - 1) good[valueToIndex(m[i])] = false;

    LL best = -1; //najlepszy dotychczas znaleziony wynik
    
    //sprawdzaj od gory dzielniki
    FORD(i, off - 1, 0) {
        if (!good[i]) continue;
        REP(j, P) {
            if ((i + offset[j])/offset[j+1] == i/offset[j+1] && !good[i+offset[j]]) {
                good[i] = false;
                break;
            }
        }
        if (good[i]) {
            LL val = indexToValue(i);
            if (m[k-1]%val == 0) best = max(best, n / val);
        }
    }
    printf("%lld\n",best);
    delete[] offset;
    delete[] m;
    return 0;
}
