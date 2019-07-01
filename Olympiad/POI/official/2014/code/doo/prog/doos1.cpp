/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Jan Kanty Milczek                             *
 *   Zlozonosc czasowa:    O(sn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int MaxN = 1000000;

int n, l[MaxN], s, oile[MaxN], dotarlem[MaxN], tmp[MaxN];

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
        int wynik = 0, gdzie = 0;
        while (gdzie < n) {
            ++wynik;
            gdzie += oile[gdzie];
        }
        int mxwynik = wynik;
        --wynik;
        for (int i = 0; i < n; ++i)
            dotarlem[i] = i;
        while (wynik) {
            if (wynik & 1)
                for (int i = 0; i < n; ++i)
                    dotarlem[i] += oile[lmod(dotarlem[i])];
            wynik >>= 1;
            for (int i = 0; i < n; ++i)
                tmp[i] = oile[i] + oile[lmod(i + oile[i])];
            for (int i = 0; i < n; ++i)
                oile[i] = tmp[i];
        }
        int tak = false;
        for (int i = 0; i < n; ++i)
            if (dotarlem[i] >= i + n)
                tak = true;
        printf("%d\n", tak? mxwynik - 1 : mxwynik);
    }
}
