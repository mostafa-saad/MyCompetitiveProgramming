/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos9.cpp                                        *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Ulepszone wyszukiwanie binarne.                  *
 *   Zlozonosc czasowa: O(m * n * log n)                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];
LL d[MAXN + 3];  // sumy częściowe
LL e[MAXN + 3];  // nadmiar z lewej strony

bool valid(int n, int ile) {
    for (int i = ile; i <= n; i++) {
        LL sum = d[i] - d[i - ile] + e[i - ile];
        if (sum >= 0) return true;
    }
    return false;
}

int solve(int n, int k)
{
    for (int i = 1; i <= n; i++) {
        d[i] = d[i-1] + t[i] - k;
        e[i] = e[i - 1] + t[i] - k;
        if (e[i] < 0) e[i] = 0;
    }
    int p = 0;
    int q = n;
    while (p < q) {
        int mid = (p + q + 1) / 2;
        if (valid(n, mid))
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
    }
    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        printf("%d ", solve(n, k));
    }
    printf("\n");
}

