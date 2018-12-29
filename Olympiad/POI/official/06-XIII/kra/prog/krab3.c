/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                krab3.c                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Bledne rozwiazanie zadania Krazki,             *
 *                        Heurystyka: symulacja tylko dla 1000 ostatnich *
 *                                    krazkow                            *
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

/* Algorytm, dla kazdego krazka z 1000 ostatnich krazkow jedziemy od gory */
int compute() {
    int i, j, dno, krazek, skip;

    if (m < 2000) skip = 0;
    else skip = m - 1000;

    for(i = 0; i < skip; i++) scanf("%d", &krazek);

    dno = n + 1;
    for(i = skip; i < m; i++) {
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

