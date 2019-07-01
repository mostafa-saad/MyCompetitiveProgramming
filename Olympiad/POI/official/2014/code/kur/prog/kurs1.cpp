/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(mn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Kopiuje i sortuje przedzial, a nastepnie      *
 *                         sprawdza maksymalna liczbe wystapien.         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 500005;

int t[MAXN], p[MAXN];

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

        for (int j = a; j <= b; j++)
            p[j] = t[j];
        sort(p+a, p+b+1);

        int maxIdx = p[a], maxOccur = 1, curOccur = 1;
        for (int j = a+1; j <= b; j++) {
            if (p[j] == p[j-1]) {
                curOccur++;
                if (curOccur > maxOccur) {
                    maxIdx = p[j];
                    maxOccur = curOccur;
                }
            }
            else
                curOccur = 1;
        }
        maxOccur = max(maxOccur, curOccur);

        if (maxOccur > (b-a+1)/2)
            printf("%d\n", maxIdx);
        else
            printf("0\n");
    }

    return 0;
}
