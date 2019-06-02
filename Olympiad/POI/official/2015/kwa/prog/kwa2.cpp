/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kwadraty                                           *
 *   Autor programu:       Adam Karczmarz                                     *
 *   Zlozonosc czasowa:    O(1)                                               *
 *   Zlozonosc pamieciowa: O(1)                                               *
 *   Opis:                 Rozwiazanie wzorcowe, alternatywne                 *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

LL sumkw(int n) {
    return (LL)n * (2 * n + 1) * (n + 1) / 6;
}

const int K = 12, INF = 1000000000, MX = 1000;
int R[MX];

int gr(LL x) {
    int s = (int)pow(3 * x, 1.0 / 3.0);
    for (; sumkw(s) < x; ++s);
    return s;
}

int main(void) {
    LL n; scanf("%lld", &n);
    int M = (int)min((LL)sumkw(K), n), sum = 0, cur = 0;
    LL cnt = 0;
    vector<LL> bad;
    for (int i = 1; i <= M; ++i) {
        R[i] = INF;
        if (sum < i) {
            ++cur;
            sum += cur * cur;
        }
        // najwyzej 2 obroty
        for (int k = cur; k * k <= i; ++k) {
            if (R[i - k * k] < k) {
                R[i] = k;
                break;
            }
        }
        if (R[i] == INF) {
            bad.push_back(i);
        }
        if (R[i] > cur) {
            ++cnt;
        }
    }
    if (n <= M) {
        if (R[n] == INF) {
            printf("-");
        } else {
            printf("%d", R[n]);
        }
    } else {
        int s = gr(n); LL sq = sumkw(s);
        int res = s;
        if (find(bad.begin(), bad.end(), sq - n) != bad.end()) {
            ++res;
        }
        cnt += (LL)(s - K) * bad.size();
        for (vector<LL>::iterator it = bad.begin(); it != bad.end(); ++it) {
            if (sq - *it > n) {
                --cnt;
            }
        }
        printf("%d", res);
    }
    printf(" %lld\n", cnt);
    return 0;
}

