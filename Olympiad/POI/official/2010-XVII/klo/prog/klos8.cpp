/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos8.cpp                                        *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Brutalne rozwiązanie z preprocessingiem i BS.    *
 *   Zlozonosc czasowa: O(m * log n + n^2)                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define MAXN 1000000

int t[MAXN + 3];
LL d[MAXN + 3];

int solve(int n, int k)
{
    int p = 0;
    int q = n;
    while (p < q) {
        int mid = (p + q + 1) / 2;
        if (d[mid] >= k) p = mid;
        else q = mid - 1;
    }
    return p;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", t + i);
    }
    for (int i = 0; i < n; i++) {
        LL sum = 0;
        for (int j = i; j < n; j++) {
            sum += t[j];
            int ile = j - i + 1;
            d[ile] = max(d[ile], sum / ile);
        }
    }
    for (int i = n - 1; i >= 0; i--)
        d[i] = max(d[i], d[i + 1]);

    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        printf("%d ", solve(n, k));
    }
    printf("\n");
}

