/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kras3.c                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Nieoptymalne rozwiazanie zadania Krazki,       *
 *                        Brutalna symulacja.                            *
 *                        Zlozonosc: O(m*n)                              *
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

/* Algorytm, dla kazdego krazka jedziemy od gory */
int compute() {
    int i, j, dno, krazek;

    dno = n + 1;
    for(i = 0; i < m; i++) {
    scanf("%d", &krazek);
    j = 0;
    while(j < dno && szer[j] >= krazek) j++;
    dno = j - 1;
    }

    return dno + 1;
}

/* Program */
int main() {

    read();
    printf("%d\n", compute());

    return 0;
}
