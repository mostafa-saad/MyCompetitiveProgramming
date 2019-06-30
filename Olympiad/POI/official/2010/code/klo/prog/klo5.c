/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo5.c                                           *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie weryfikujace (bez uzycia STLa).      *
 *   Zlozonosc czasowa: O(n * m)                                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];
LL a[MAXN + 3];  // sumy częściowe
int lewy[MAXN + 3];
int prawy[MAXN + 3];

int solve(int n, int k)
{
    int i;
    int lp = 0;  // wskazuje na ostatni element tablicy `lewy`
    for (i = 1; i <= n; i++) {
        a[i] = a[i - 1] + t[i] - k;
        if (a[i] < a[lewy[lp]])
            lewy[++lp] = i;
    }
    int pp = 0;
    prawy[0] = n;
    for (i = n - 1; i >= 1; i--) {
        if (a[i] > a[prawy[pp]])
            prawy[++pp] = i;
    }
    int p = 0;
    int ret = 0;
    for (i = pp; i >= 0; i--) {
        while (a[lewy[p]] > a[prawy[i]]) p++;
        if (prawy[i] - lewy[p] > ret) ret = prawy[i] - lewy[p];
    }
    return ret;
}

int main()
{
    int n, m, i;
    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", t + i);
    }
    for (i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        printf("%d ", solve(n, k));
    }
    printf("\n");
    return 0;
}

