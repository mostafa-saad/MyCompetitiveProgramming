/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego zapytania oblicza ile jest        *
 *                         elementow kazdego typu.                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

const int MAXN = 500005;

int t[MAXN], count[MAXN];

int main() {
    int n, m;

    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &t[i]);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;

        std::fill(count+1, count+n+1, 0);
        for (int j = a; j <= b; j++)
            count[t[j]]++;

        int maxIdx = -1, maxCount = -1;
        for (int j = 1; j <= n; j++)
            if (count[j] > maxCount) {
                maxCount = count[j];
                maxIdx = j;
            }

        if (maxCount > (b-a+1)/2)
            printf("%d\n", maxIdx);
        else
            printf("0\n");
    }

    return 0;
}
