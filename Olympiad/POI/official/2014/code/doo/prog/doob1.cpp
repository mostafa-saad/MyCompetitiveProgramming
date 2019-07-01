/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Jan Kanty Milczek                             *
 *   Zlozonosc czasowa:    O(snc)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Program liczący wynik dla c (tu: c=20)        *
 *                         losowo wybranych punktów startowych.          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

const int MaxN = 1000000;

int n, l[MaxN], s, oile[MaxN];

int lmod(int x) {
    while (x >= n)
        x -= n;
    return x;
}

int main() {
    scanf("%d%d", &n, &s);
    srand(13 * n + s * s - n*s % (n + s));
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
        int Wynik = 2000000000;
        for (int _c = 0; _c < 20; ++_c) {
            int start = rand() % n;
            int wynik = 0, gdzie = start;
            while (gdzie < start + n) {
                ++wynik;
                gdzie += oile[lmod(gdzie)];
            }
            if (wynik < Wynik)
                Wynik = wynik;
        }
        printf("%d\n", Wynik);
    }
}
