/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klo6.cpp                                         *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie alternatywne.                        *
 *   Zlozonosc czasowa: O(n * m)                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];
LL d[MAXN + 3];  // sumy częściowe
LL lewy[MAXN + 3];  // nadmiar z lewej strony
LL prawy[MAXN + 3];  // nadmiar z prawej strony

int solve(int n, int k)
{
    for (int i = 1; i <= n; i++) {
        d[i] = d[i - 1] + t[i] - k;
        lewy[i] = lewy[i - 1] + t[i] - k;
        if (lewy[i] < 0) lewy[i] = 0;
    }
    for (int i = n; i >= 0; i--) {
        prawy[i] = prawy[i + 1] + t[i] - k;
        if (prawy[i] < 0) prawy[i] = 0;
    }
    int p = 0, q = 0; // przedzial [p+1, q]
    int ret = 0;
    while (p < n) {
        while (q < n && (q < p || lewy[p] + d[q + 1] - d[p] + prawy[q + 2] >= 0)) q++;
        ret = max(ret, q - p);
        p++;
    }
    return ret;
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

