/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kra.c                                          *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Rozwiazanie wzorcowe zadania Kr±zki,           *
 *                        Zlozonosc: O(n+m)                              *
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

/* Algorytm, zaczynamy od dolu rurki, i dodajemy
   kolejne krazki posuwajac sie do gory */
int compute() {
    int i, pos, krazek;
    
    pos = n + 1;
    for(i = 0; i < m; i++) {
    scanf("%d", &krazek);
    if (pos > 0) pos--;
    while (szer[pos] < krazek) pos--;
    }
    
    return pos;
}

/* Program */
int main() {

    read();
    printf("%d\n", compute());
    
    return 0;
}

