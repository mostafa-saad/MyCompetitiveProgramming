/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n^n)                                           *
 *   Opis:              Rozwiazanie powolne, wykladnicze                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAXN 1000001

int n;
int przelozony[MAXN], pensja[MAXN];
int ile_podwladnych[MAXN];
int uzyte[MAXN];
int rozwiazanie[MAXN];

void policz_podwladnych() {
    int kolejka[MAXN], pocz = 0, kon = 0;
    int stopien[MAXN];
    for (int i = 0; i <= n; ++i) stopien[i] = 0;
    for (int i = 1; i <= n; ++i)
        if (przelozony[i] != i)
            ++stopien[przelozony[i]]; // zliczamy bezposrednich
    for (int i = 1; i <= n; ++i)
        if (stopien[i] == 0)
            kolejka[kon++] = i;
    while (pocz < kon) {
        int akt = kolejka[pocz++];
        int przel = przelozony[akt];
        if (akt != przel) {
            if (!--stopien[przel]) kolejka[kon++] = przel;
            ile_podwladnych[przel] += ile_podwladnych[akt] + 1;
        }
    }
}

void zapisz_rozwiazanie() {
    for (int i = 1; i <= n; ++i)
        if (rozwiazanie[i] == 0) rozwiazanie[i] = pensja[i];
        else if (rozwiazanie[i] != pensja[i]) rozwiazanie[i] = -1;
}

void iteruj_pensje(int p) {
    while (p > 0 && uzyte[p]) --p;
    if (p == 0) zapisz_rozwiazanie();
    else {
        for (int j = 1; j <= n; ++j)
            if (ile_podwladnych[j] <= p && pensja[j] == 0
            && (przelozony[j] == j || pensja[przelozony[j]] > p)) {
                pensja[j] = p;
                iteruj_pensje(p-1);
                pensja[j] = 0;
            }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", przelozony + i, pensja + i);
        rozwiazanie[i] = pensja[i];
    }
    policz_podwladnych();
    for (int i = 1; i <= n; ++i) uzyte[pensja[i]] = i;
    iteruj_pensje(n);
    for (int i = 1; i <= n; ++i)
        if (rozwiazanie[i] != -1)
            printf("%d\n", rozwiazanie[i]);
        else
            printf("0\n");
    return 0;
}
