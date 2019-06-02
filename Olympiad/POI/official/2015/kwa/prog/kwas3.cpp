/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kwadraty                                           *
 *   Autor programu:       Adam Karczmarz                                     *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         Obliczanie za pomocą wzoru                         *
                           k(n) = min{l : s(n) 2 ≤ l 2 ≤ n ∧ k(n − l 2 ) < l} *
 *****************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

const int INF = 1000000000, S = 1 << 21, MD = S - 1;
int R[S];

int main(void) {
    LL n; scanf("%lld", &n);
    int sum = 0, cur = 0; 
    LL cnt = 0;
    for (LL i = 1; i <= n; ++i) {
        R[i & MD] = INF;
        if (sum < i) {
            ++cur;
            sum += cur * cur;
        }
        for (int k = cur; k * k <= i; ++k) {
            if (R[(i - k * k) & MD] < k) {
                R[i & MD] = k;
                break;
            }
        }
        if (R[i & MD] > cur) {
            ++cnt;
        }
    }
    if (R[n & MD] == INF) {
        printf("-");
    } else {
        printf("%d", R[n & MD]);
    }
    printf(" %lld\n", cnt);
    return 0;
}

