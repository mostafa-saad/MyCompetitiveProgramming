/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Binarnie wyszukujemy minimalnego czasu, w ktorym *
 *                      mozemy wysadzic ladunki                          *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300000

typedef struct kolejka_statyczna {
	int w[MAX_N];	/* wartosci kolejki */
	int p, k;		/* poczatek i koniec kolejki */
} kolejka_statyczna;

int n, m;	/* ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont */
int d[MAX_N + 1];	/* d[i] == 0 wtw., gdy w i-tej komorze nie ma dynamitu */
int korytarze[2 * MAX_N + 1];	/* tablica opisujaca siec komor */ 
int koniec[MAX_N + 1];	/* koniec listy sasiedztwa dla i-tej komory */
int ilosc[MAX_N + 1];	/* ilosc elementow w i-tej liscie sasiedztwa */

kolejka_statyczna q;	/* pomocnicza kolejka */
int a, b, c, i, j, p, x;	/* zmienne pomocnicze */
int z[MAX_N + 1], v[MAX_N + 1];	/* tablice pomocnicze */
int min_tab[MAX_N + 1], max_tab[MAX_N + 1]; 
/* ile minimalnie w dol, ile maksymalnie w gore */

/* wczytaj() - wczytuje dane i zmienia reprezentacje sieci komor.   * 
 * t[] bedzie zawierala listy sasiedztw kolejnych komor.            * 
 * Konce kolejnych list zapamietamy w k[].                          */
void wczytaj() {
	scanf ("%d %d", &n, &m);
	x = 0;
	for (i = 1; i <= n; ++i) {
		scanf ("%d", &d[i]);
		ilosc[i] = 0;
		x += d[i];
	}
	
	for (i = 1; i < n; ++i) {
		scanf ("%d %d", &min_tab[i], &max_tab[i]);
		++ilosc[min_tab[i]];
		++ilosc[max_tab[i]];
	}

	koniec[0] = 0;
	for (i = 1; i <= n; ++i) {
		koniec[i] = ilosc[i] + koniec[i - 1];
		z[i] = koniec[i - 1];
	}

	for (i = 1; i < n; ++i) {
		korytarze[z[min_tab[i]]++] = max_tab[i];
		korytarze[z[max_tab[i]]++] = min_tab[i];
	}
}


/* sprawdz(x) - sprawdza, czy jestesmy w stanie wysadzic wszystkie   *
 * dynamity w x jednostkach czasu.                                   */
int sprawdz(int czas) {
	/* wyznaczamy liscie i wrzucamy na statyczna kolejke q */
	q.p = 0;	q.k = 0;
	for (i = 1; i <= n; ++i) {
		min_tab[i] = 0;
		max_tab[i] = 0;
		z[i] = ilosc[i];
		if (z[i] == 1)
			q.w[q.k++] = i;
	}
	
	j = m;
	/* wyznaczamy miejsca, w ktorych musimy podpalic lont */
	while ((j >= 0) && (q.p < q.k)) {
		p = q.w[q.p++];
		if (max_tab[p] > -min_tab[p]) /* zapali sie od poprzedniego lontu */
			min_tab[p] = 0;
		else if (min_tab[p] == -czas) { /* musimy podpalic lont */
			--j;
			max_tab[p] = czas + 1;
			min_tab[p] = 0;
		}

		for (i = koniec[p - 1]; i < koniec[p]; ++i) {
			x = korytarze[i];
			if (z[x] > 0) {
				if (max_tab[x] < max_tab[p] - 1)
					max_tab[x] = max_tab[p] - 1;
				if ((min_tab[p] < 0) || ((max_tab[p] == 0) && (d[p] == 1)))
					if (min_tab[x] > min_tab[p] - 1)
						min_tab[x] = min_tab[p] - 1;

				if (--z[x] == 1)
					q.w[q.k++] = x;
			}
		}
	}

	/* sprawdzamy, czy w ostatnim rozwazanym wierzcholku nalezy zapalic lont */
	if (j >= 0) {
		p = q.w[q.p - 1];
		if ((min_tab[p] < 0) || ((max_tab[p] == 0) && (d[p] == 1)))
			--j;
	}
	
	/* jezeli nie podpalilismy za duzo lontow i przetworzylismy cale drzewo *
	 * to mozna w [czas] jednostek czasu podpalic wszystkie dynamity        */
	return ((j >= 0) && (q.p == q.k)); 
}


/*****************************  MAIN  ************************************/
int main() {
	wczytaj();
	
	if (x <= m) {
		printf ("0\n");
		return 0;
	}

	/* binarne wyszukiwanie wyniku */
	a = 1;
	b = n / 2;
	while (a < b) {
		c = (a + b) / 2;

		if (sprawdz (c))
			b = c;
		else
			a = c + 1;
	}

	printf ("%d\n", a);

	return 0;
}
