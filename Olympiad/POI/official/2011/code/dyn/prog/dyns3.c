/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * n * lg(n))                                 *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Ukorzeniamy drzewo, binarnie wyszukujemy wynik,  *
 *                      symulujemy odpalenie lontu, wyznaczajac kolejne  *
 *                      optymalne pozycje (najnizej polozone poddrzewo   *
 *                      o wysokosci rownej wynikowi)                     *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300000

typedef struct kolejka_statyczna {
	int w[MAX_N];	/* wartosci kolejki */
	int p, k;		/* poczatek i koniec kolejki */
} kolejka_statyczna;

typedef struct stos {
	int w;	/* wartosc elementu stosu */
	struct stos *nx;	/* wskaznik na nastepny element stosu */
} stos;

void wrzuc (stos **s, int x) {
	stos *tmp = malloc (sizeof (stos));
	tmp->w = x;
	tmp->nx = *s;
	*s = tmp;
}

int zdejmij (stos **s) {
	stos *tmp;
	int z;

	if (*s != NULL) {
		tmp = *s;
		z = tmp->w;
		*s = tmp->nx;
		free (tmp);

		return z;
	}
	return -1;
}


int n, m;	/* ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont */
int d[MAX_N + 1];	/* d[i] == 0 wtw., gdy w i-tej komorze nie ma dynamitu */
stos *korytarze[MAX_N + 1];	/* listy sasiedztwa zrealizowane przy pomocy stosow */
int ilosc[MAX_N + 1];	/* ilosc elementow w i-tej liscie sasiedztwa */
int ojciec[MAX_N + 1];	/* ojciec w ukorzenionym drzewie */

kolejka_statyczna q;	/* pomocnicza kolejka */
int a, b, c, i, j, p, x;	/* zmienne pomocnicze */
int z[MAX_N + 1], v[MAX_N + 1];	/* tablice pomocnicze */
int dynamit[MAX_N + 1];	/* ktore komnaty juz przetworzone */
stos *wysokosc[MAX_N + 1];	/* stosy z wierzcholkami na wys. i */


void wczytaj() {
	scanf ("%d %d", &n, &m);

	for (i = 1; i <= n; ++i) {
		scanf ("%d", d + i);
		korytarze[i] = NULL;
		wysokosc[i] = NULL;
	}
	
	for (i = 1; i < n; ++i) {
		scanf ("%d %d", &a, &b);
		wrzuc (korytarze + a, b);
		wrzuc (korytarze + b, a);
		++ilosc[a];
		++ilosc[b];
	}
}


/* ukorzenia drzewo w wierzcholku nr 1, oblicza tablice ojciec i wysokosc */
void ukorzen() {
	stos *s = NULL;
	int z;
	for (i = 0; i <= n; ++i)
		dynamit[i] = -1;
	dynamit[1] = 0;
	/* tymczasowo do zapamietania wysokosci na jakiej sa wierzcholki */

	q.p = 0;
	q.k = 1;
	q.w[0] = 1;
	wrzuc (wysokosc, 1);
	while (q.p < q.k) {
		x = q.w[q.p++];
		s = korytarze[x];
		while (s != NULL) {
			z = s->w;
			s = s->nx;
			if (dynamit[z] == -1) {
				ojciec[z] = x;
				dynamit[z] = dynamit[x] + 1;
				q.w[q.k++] = z;
				wrzuc (wysokosc + dynamit[z], z);
			}
		}
	}
}


/* oznacza podpalenie w wierzcholku [w] dla czasu [czas] */
void oznacz (int w, int czas) {
	int x, k, z;
	stos *s = NULL;
	q.p = 0;
	q.k = 1;
	q.w[0] = w;
	v[w] = w;	/* v[x] == w oznacza juz przetworzylismy x */
	dynamit[w] = 0;
	while ((czas-- > 0) && (q.p < q.k)) {
		k = q.k;
		while (q.p < k) {
			x = q.w[q.p++];
			s = korytarze[x];
			while (s != NULL) {
				z = s->w;
				s = s->nx;
				if (v[z] != w) {
					v[z] = w;
					q.w[q.k++] = z;
					dynamit[z] = 0;
				}
			}
		}
	}
}


/* sprawdza czy w czasie czas mozna wysadzic wszystkie dynamity */
int sprawdz (int czas) {
	stos *s = NULL;
	int z = m;
	for (i = 0; i <= n; ++i) {
		dynamit[i] = d[i];
		v[i] = 0;
	}

	i = n;
	while ((i-- > 0) && (z > -1)) {
		s = wysokosc[i];
		while (s != NULL) {
			x = s->w;
			s = s->nx;
			if (dynamit[x] == 1) {
				j = czas;
				while ((x > 1) && (j-- > 0))
					x = ojciec[x];

				oznacz (x, czas);
				--z;
			}
		}
	}

	return (z >= 0);
}


int main () {
	wczytaj();
	ukorzen();

	a = 0;
	b = n / 2;
	while (a < b) {
		c = (a + b) / 2;

		if (sprawdz (c))
			b = c;
		else
			a = c + 1;
	}

	printf ("%d\n", a);

	for (i = 1; i <= n; ++i) {
		while (korytarze[i] != NULL) 
			zdejmij (korytarze + i);
		while (wysokosc[i] != NULL)
			zdejmij (wysokosc + i);
	}

	return 0;
}
