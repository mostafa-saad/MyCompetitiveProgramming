/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Turystyka                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(2^n * (n+m))                                *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
typedef long long LL;
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin(); i != (x).end(); ++i)

const int MAXN = 20000;

int n,m,c[MAXN + 10],sas[MAXN + 10],cov,res=1000000000;

int main() {
    std::ios_base::sync_with_stdio(0);
    // wczytanie wejscia
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> c[i];
    while(m--) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        sas[a] |= 1 << b;
        sas[b] |= 1 << a;
    }
    n = min(n, 30);
    // rozwiazanie
    for(int mask = 0; mask < (1 << n); mask++) {
        int act = 0;
        cov = mask;
        for(int i=0; i<n; i++)
            if(mask & (1 << i)) {
                cov |= sas[i];
                act += c[i];
            }
        if(cov == (1 << n) - 1)
            res = min(res, act);
    }
    // wypisanie wyniku
    cout << res << endl;
}
