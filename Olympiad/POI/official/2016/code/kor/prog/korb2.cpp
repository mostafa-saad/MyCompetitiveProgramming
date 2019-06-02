/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Korale                                             *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie naiwne                                 *
 *                         oparte na wydawaniu reszty                         *
 *****************************************************************************/


#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 305;
const int MAXS = 100005;
const LL MAXK = 1000000000000000000LL;

int n, k, T[MAXN], sum = 0;
LL dp[MAXS];

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
        sum += T[i];
    }

    dp[0] = 1LL;
    for (int i = 0; i < n; i++)
        for (int j = sum; j >= T[i]; j--) {
            dp[j] += dp[j-T[i]];
            if (dp[j] >= MAXK)
                dp[j] = MAXK;
        }

    LL curSum = 0LL;
    for (int i = 0; i <= sum; i++) {
        curSum += dp[i];
        if (curSum >= k) {
            printf("%d\n", i);
            return 0;
        }
    }

    printf("NIE\n");
    return 0;
}
