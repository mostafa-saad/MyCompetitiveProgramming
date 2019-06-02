/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

int n, q, t[MAXN], prefSum[MAXN], maxLength = 0;

void ReadData() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
        maxLength = max(maxLength, t[i]);
    }
}

void ComputePrefixSums() {
    prefSum[0] = 0;
    for (int i = 1; i <= n; i++)
        prefSum[i] = prefSum[i-1]+t[i-1];
}

int main() {
    ReadData();
    ComputePrefixSums();

    while (q--) {
        int x, result;
        scanf("%d", &x);
        if (maxLength > x) {
            printf("NIE\n");
            continue;
        }
        if (x >= prefSum[n]) {
            printf("1\n");
            continue;
        }
        result = (prefSum[n]+x-1)/x;
        printf("%d\n", result);
    }

    return 0;
}
