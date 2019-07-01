/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Jan Kanty Milczek                             *
 *   Zlozonosc czasowa:    O(sn)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int MaxN = 1000000;

int n, l[MaxN], s, oile[MaxN];

int lmod(int x) {
    while (x >= n)
        x -= n;
    return x;
}

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; ++i)
        scanf("%d", l + i);
    while (s--) {
        int d;
        scanf("%d", &d);
        int j = 0, sum = 0;
        bool nie = false;
        for (int i = 0; i < n; ++i) {
            while (sum + l[lmod(j)] <= d) {
                sum += l[lmod(j)];
                ++j;
            }
            oile[i] = j - i;
            if (oile[i] == 0)
                nie = true;
            sum -= l[i];
        }
        if (nie) {
            printf("NIE\n");
            continue;
        }
        int start = 0;
        for (int i = 0; i < n; ++i)
            start = lmod(start + oile[start]);
        int wynik = 0, gdzie = start;
        while (gdzie < start + n) {
            ++wynik;
            gdzie += oile[lmod(gdzie)];
        }
        printf("%d\n", wynik);
    }
}
