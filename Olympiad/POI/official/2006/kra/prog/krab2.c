/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                krab2.c                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Bledne rozwiazanie zadania Krazki,             *
 *                        Heurystyka: sprawdza tylko miejsce ladowania   *
 *                        pierwszego krazka i odejmuje liczbe krazkow.   *
 *                        Zlozonosc: O(n+m)                              *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define MAX_N 1000000

int n, m;

/* Szerokosci walcow w rurce */
int szer[MAX_N + 1];

/* Wczytanie danych */
void read() {
    int i;
    scanf("%d%d", &n, &m);

    for(i = 0; i < n; i++)
    scanf("%d", &(szer[i]));
}

/* Algorytm, dla pierwszego krazka sprawdz brutalnie */
int compute() {
    int j, pos, krazek;

    scanf("%d", &krazek);
    j = 0;
    while(j < n && szer[j] >= krazek) j++;
    pos = j - m;

    if (pos < 0) return 0;
    return pos + 1;
}

/* Program */
int main() {
    read();
    printf("%d\n", compute());
    return 0;
}

