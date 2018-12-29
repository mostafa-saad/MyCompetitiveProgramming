/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * (n po m)                                   *
 *   Opis:              Rozwiazanie powolne, silowe                      *
 *                      Ustawiamy punkty zapalenia lontow i sprawdzamy   *
 *                      czas podpalenia dynamitow                        *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

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

int podpalone[MAX_N + 1];	/* komory, ktorych lonty beda podpalona */
int w, x;	/* dotychczasowe minimum i czas aktualnie rozwazanego ustawienia */
int i, l, k;	/* zmienne pomocnicze */
kolejka_statyczna q[2];	/* kolejka pomocnicza */
int uzyte[MAX_N + 1]; /* uzyte[i]==0 gdy nie zapalil sie lont do i-tej komory */
int z[MAX_N + 1]; /* tablica pomocnicza */
int dil; /* ilosc dynamitow */

/* wczytaj() - wczytuje dane i zmienia reprezentacje sieci komor.   * 
 * t[] bedzie zawierala listy sasiedztw kolejnych komor.            * 
 * Konce kolejnych list zapamietamy w k[].                          */
void wczytaj() {
	scanf ("%d %d", &n, &m);
	dil = 0;
	for (i = 1; i <= n; ++i) {
		scanf ("%d", &d[i]);
		ilosc[i] = 0;
		dil += d[i];
	}
	
	for (i = 1; i < n; ++i) {
		scanf ("%d %d", &podpalone[i], &uzyte[i]);
		++ilosc[podpalone[i]];
		++ilosc[uzyte[i]];
	}

	koniec[0] = 0;
	for (i = 1; i <= n; ++i) {
		koniec[i] = ilosc[i] + koniec[i - 1];
		z[i] = koniec[i - 1];
	}

	for (i = 1; i < n; ++i) {
		korytarze[z[podpalone[i]]++] = uzyte[i];
		korytarze[z[uzyte[i]]++] = podpalone[i];
	}
}

/* generuj() - generuje nastepna kombinacje podpalen lontow */
int generuj() {
	i = 1;
	while ((i <= m) && (podpalone[m - i] == n - i + 1))
		++i;
	
	if (i > m)
		return 0;
	else {
		++podpalone[m - i];
		while (i-- > 0)
			podpalone[m - i] = podpalone[m - i - 1] + 1;

		return 1;
	}
}


/* oblicz_czas() - oblicza czas po jakim wszystkie ladunki wybuchna *
 * przy aktualnej kombinacji podpalen lontow                        */
int oblicz_czas (int ilosc) {
	int v = 0, z = 0;

	for (i = 1; i <= n; ++i)
		uzyte[i] = 0;

	for (i = 0; i < m; ++i) {
		q[0].w[i] = podpalone[i];
		uzyte[podpalone[i]] = 1;
	}

	q[0].p = 0;
	q[0].k = m;

	k = 0;
	while ((ilosc > 0) && (q[k].p < q[k].k)) {
		k = 1 - k;
		++z;
		q[k].p = 0;
		q[k].k = 0;
		for (i = q[1-k].p; i < q[1-k].k; ++i)
			for (l = koniec[q[1-k].w[i] - 1]; l < koniec[q[1-k].w[i]]; ++l)
				if (uzyte[x = korytarze[l]] == 0) {
					uzyte[x] = 1;
					q[k].w[q[k].k++] = x;
					if (d[x] == 1) {
						--ilosc;
						v = z;
					}
				}
	}
	
	return v;
}


int main() {
	wczytaj ();

	if (dil <= m) {
		printf ("0\n");

		return 0;
	}

	for (i = 0; i < m; ++i)
		podpalone[i] = i + 1;

	--podpalone[m - 1];
	
	w = n;
	while ((w > 1) && (generuj() != 0))
		if ((x = oblicz_czas(dil)) < w)
			w = x;

	printf ("%d\n", w);

	return 0;
}
