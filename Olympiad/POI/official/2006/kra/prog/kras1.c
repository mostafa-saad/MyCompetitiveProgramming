/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kras1.c                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Nieoptymalne rozwiazanie zadania Krazki,       *
 *                        Wyszukiwanie binarne pozycj nastepnego krazka. *
 *                        Zlozonosc: O(m*log(n))                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define MAX_N 1000000
#define min(a,b) ((a)<(b)?(a):(b))
#define INF 2000000000

int n, m;

/* Najwieksza szerokosc krazka jaki moze
   doleciec do danej glebokosci */
int szer[MAX_N + 2];

/* Wczytanie danych i obliczenie minimalnych szerokosci */
void read() {
    int i, sz;
    scanf("%d%d", &n, &m);

    szer[0] = INF;
    for(i = 1; i <= n; i++) {
    scanf("%d", &sz);
    szer[i] = min(szer[i-1], sz);
    }
    szer[n + 1] = 0;
}

/* Wyszukiwanie binarne */
int binary(int pocz, int kon, int krazek) {
    if (pocz == kon) return pocz;

    int half = (pocz + kon + 1) / 2;
    if (szer[half] >= krazek) return binary(half, kon, krazek);
    else return binary(pocz, half - 1, krazek);
}

/* Algorytm, zaczynamy od dolu rurki, przy dodawaniu
   kolejnego kraza wyszukujemy binarnie jego pozycje */
int compute() {
    int i, pos, krazek;

    pos = n + 1;
    for(i = 0; i < m; i++) {
    scanf("%d", &krazek);
    pos = binary(0, pos - 1, krazek);
    if (pos == 0) return 0;
    }

    return pos;
}

/* Program */
int main() {

    read();
    printf("%d\n", compute());

    return 0;
}

