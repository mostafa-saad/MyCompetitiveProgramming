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

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 300000

int n, m;	/* ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont */
int d[MAX_N + 1];	/* d[i] == 0 wtw., gdy w i-tej komorze nie ma dynamitu */
vector<int> korytarze[MAX_N + 1];	/* listy sasiedztwa */
int ojciec[MAX_N + 1];	/* ojciec w ukorzenionym drzewie */

queue<int> q[2];	/* pomocnicza kolejka */
int a, b, c, i, j, p, x;	/* zmienne pomocnicze */
int z[MAX_N + 1], v[MAX_N + 1];	/* tablice pomocnicze */
int dynamit[MAX_N + 1];		/* ktore komnaty juz przetworzone */
vector<int> wysokosc[MAX_N + 1];	/* wierzcholki na wysokosci i */


void wczytaj() {
	scanf ("%d %d", &n, &m);

	for (i = 1; i <= n; ++i) {
		scanf ("%d", d + i);
		korytarze[i].clear();
		while (!q[0].empty()) q[0].pop();
		while (!q[1].empty()) q[1].pop();
	}
	
	for (i = 1; i < n; ++i) {
		scanf ("%d %d", &a, &b);
		korytarze[a].push_back(b);
		korytarze[b].push_back(a);
	}
}


/* ukorzenia drzewo w wierzcholku nr 1, oblicza tablice ojciec i wysokosc */
void ukorzen() {
	int z;
	for (i = 0; i <= n; ++i)
		dynamit[i] = -1;
	dynamit[1] = 0;
	/* tymczasowo do zapamietania wysokosci na jakiej sa wierzcholki */

	while (!q[0].empty()) q[0].pop();
	q[0].push(1);
	wysokosc[0].push_back(1);
	while (!q[0].empty()) {
		x = q[0].front();
		q[0].pop();

		for (size_t j = 0; j < korytarze[x].size(); ++j) {
			z = korytarze[x][j];
			if (dynamit[z] == -1) {
				ojciec[z] = x;
				dynamit[z] = dynamit[x] + 1;
				q[0].push(z);
				wysokosc[dynamit[z]].push_back(z);
			}
		}
	}
}


/* oznacza podpalenie w wierzcholku [w] dla czasu [czas] */
void oznacz (int w, int czas) {
	int x, k, z;
	while (!q[0].empty()) q[0].pop();
	while (!q[1].empty()) q[1].pop();
	q[0].push(w);
	v[w] = w;	/* v[x] == w oznacza juz przetworzylismy x */
	dynamit[w] = 0;
	k = 0;
	while ((czas-- > 0) && (!q[k].empty())) {
		while (!q[k].empty()) {
			x = q[k].front();
			q[k].pop();

			for (size_t j = 0; j < korytarze[x].size(); ++j) {
				z = korytarze[x][j];
				if (v[z] != w) {
					v[z] = w;
					q[1-k].push(z);
					dynamit[z] = 0;
				}
			}
		}
		k = 1 - k;
	}
}


/* sprawdza czy w czasie czas mozna wysadzic wszystkie dynamity */
int sprawdz (int czas) {
	int z = m, l;
	for (i = 0; i <= n; ++i) {
		dynamit[i] = d[i];
		v[i] = 0;
	}

	i = n;
	while ((i-- > 0) && (z > -1)) {
		for (size_t j = 0; j < wysokosc[i].size(); ++j) {
			x = wysokosc[i][j];
			if (dynamit[x] == 1) {
				l = czas;
				while ((x > 1) && (l-- > 0))
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

	return 0;
}
