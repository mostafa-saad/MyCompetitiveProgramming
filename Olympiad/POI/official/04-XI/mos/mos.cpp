/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Most                                           *
 *   Plik:                mos.cpp                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *************************************************************************/

#include <stdio.h>

/* Program glowny */
int main() {
    int n;
    int t1, t2, tx, ty;		/* Czasy dla A_1, A_2 oraz dwoch wczytanych */
    int wynik;
    int ile;			/* Ile osob wczytano */

    scanf("%d %d", &n, &t1);
    
    /* Przypadek szczegolny n==1 */
    wynik = t1;
    if (n >= 2) {
	scanf("%d", &t2);
	wynik = t2;  /* Ostatnie przejscie A_1 i A_2 */
	ile = 2;
	/* Jezeli n nieparzyste, to wczytamy A_3, ktore na pewno idzie pojedynczo */
	if (n % 2 == 1) {
	    scanf("%d", &tx);
	    wynik += tx + t1;
	    ile++;
	}
	/* Wczytujemy po 2... */
	while (ile < n) {
	    scanf("%d%d", &tx, &ty);
	    /* ... i patrzymy co wybrac */
	    if (tx <= 2 * t2 - t1)
		wynik += tx + ty + 2 * t1; /* kazde pojedynczo */
	    else wynik += ty + 2 * t2 + t1; /* podwojnie */
	    ile += 2;
	}
    }
    
    /* Koniec */
    printf("%d\n", wynik);
    return 0;
}
