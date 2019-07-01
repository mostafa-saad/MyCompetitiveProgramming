/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Algorytm wyszukiwania lidera zastosowany dla  *
 *                         kazdego zapytania.                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

const int MAXN = 500005;

int t[MAXN];

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

        int leader = -1, leaderCount = 0;
        for (int j = a; j <= b; j++) {
            if (leaderCount == 0) {
                leader = t[j];
                leaderCount = 1;
            }
            else {
                if (leader == t[j])
                    leaderCount++;
                else
                    leaderCount--;
            }
        }

        int realCount = 0;
        for (int j = a; j <= b; j++)
            if (t[j] == leader)
                realCount++;

        if (realCount > (b-a+1)/2)
            printf("%d\n", leader);
        else
            printf("0\n");
    }

    return 0;
}
