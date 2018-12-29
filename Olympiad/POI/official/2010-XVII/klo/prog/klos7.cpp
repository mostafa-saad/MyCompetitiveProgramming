/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos7.cpp                                        *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie powolne - brutalne.                  *
 *   Zlozonosc czasowa: O(m * n^2)                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];

int solve(int n, int k)
{
    int ret = 0;
    for (int i = 0; i < n; i++)
    {
        LL sum = 0;
        for (int j = i; j < n; j++) {
            sum += t[j];
            LL ile = j - i + 1;
            if (sum >= k * ile && ret < ile)
                ret = ile;
        }
    }
    return ret;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", t + i);
    }
    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        printf("%d ", solve(n, k));
    }
    printf("\n");
}

