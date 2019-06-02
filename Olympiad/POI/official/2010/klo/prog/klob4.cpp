/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klob4.cpp                                        *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Naiwny binary search.                            *
 *   Zlozonosc czasowa: O(m * n * log n)                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];
LL d[MAXN + 3];

bool valid(int n, int ile, int limit) {
    for (int i = ile; i <= n; i++) {
        LL sum = d[i] - d[i - ile];
        if (sum >= limit) return true;
    }
    return false;
}

int solve(int n, int k)
{
    int p = 0;
    int q = n;
    while (p < q) {
        int mid = (p + q + 1) / 2;
        LL limit = (LL) mid * k;
        if (valid(n, mid, limit))
            p = mid;
        else q = mid - 1;
    }
    return p;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", t + i);
        d[i] = t[i] + d[i - 1];
    }
    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        printf("%d ", solve(n, k));
    }
    printf("\n");
}

