/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kwadraty                                           *
 *   Autor programu:       Adam Karczmarz                                     *
 *   Zlozonosc czasowa:    O(n ^ 4/3)                                         *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         Obliczanie za pomoca wzoru                         *
                           k(n) = min{l : 1 ≤ l 2 ≤ n ∧ k(n − l 2 ) < l}      *
 *****************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long LL;

const int INF = 1000000000, MAXN = 5000000;
int R[2 * MAXN + 1];

int main(void) {
    LL n; scanf("%lld", &n);
    assert(n <= MAXN);
    for (int i = 1; i <= 2 * n; ++i) {
        R[i] = INF;
        for (int k = 1; k * k <= i; ++k) {
            if (R[i - k * k] < k) {
                R[i] = k;
                break;
            }
        }
    }
    if (R[n] == INF) {
        printf("-");
    } else {
        printf("%d", R[n]);
    }
    int cnt = 0, mn = INF;
    for (int i = 2 * n; i > 0; --i) {
        mn = min(mn, R[i]);
        if (i <= n) {
            if (mn < R[i]) {
                ++cnt;
            }
        }
    }
    printf(" %d\n", cnt);
    return 0;
}

