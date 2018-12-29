/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * wynik)                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzamy kolejne mozliwe wartosci wyniku       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 300000

int n, m;	/* ilosc komor i liczba miejsc, w ktorych mozemy podpalic lont */
int d[MAX_N + 1];	/* d[i] == 0 wtw., gdy w i-tej komorze nie ma dynamitu */
vector<int> korytarze[MAX_N + 1];	/* opis siec komor */ 

queue<int> q;	/* pomocnicza kolejka */
int a, b, c, i, j, p, x;	/* zmienne pomocnicze */
int z[MAX_N + 1];	/* tablice pomocnicze */
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
		korytarze[i].clear();
		x += d[i];
	}
	
	for (i = 1; i < n; ++i) {
		scanf ("%d %d", &a, &b);
		korytarze[a].push_back(b);
		korytarze[b].push_back(a);
	}
}


/* sprawdz(x) - sprawdza, czy jestesmy w stanie wysadzic wszystkie   *
 * dynamity w x jednostkach czasu.                                   */
int sprawdz(int czas) {
	/* wyznaczamy liscie i wrzucamy na statyczna kolejke q */
	//printf ("czas :%d\n", czas);
	while (!q.empty())
		q.pop();
	for (i = 1; i <= n; ++i) {
		min_tab[i] = 0;
		max_tab[i] = 0;
		z[i] = korytarze[i].size();
		if (z[i] == 1)
			q.push(i);
	}
	
	j = m;
	/* wyznaczamy miejsca, w ktorych musimy podpalic lont */
	while ((j >= 0) && (!q.empty())) {
		p = q.front();
		q.pop();
		if (max_tab[p] > -min_tab[p]) /* zapali sie od poprzedniego lontu */
			min_tab[p] = 0;
		else if (min_tab[p] == -czas) { /* musimy podpalic lont */
	//		printf("zapalamy: %d\n", p);
			--j;
			max_tab[p] = czas + 1;
			min_tab[p] = 0;
		}

		for (size_t i = 0; i < korytarze[p].size(); ++i) {
			x = korytarze[p][i];
			if (z[x] > 0) {
				if (max_tab[x] < max_tab[p] - 1)
					max_tab[x] = max_tab[p] - 1;
				if ((min_tab[p] < 0) || ((max_tab[p] == 0) && (d[p] == 1)))
					if (min_tab[x] > min_tab[p] - 1)
						min_tab[x] = min_tab[p] - 1;

				if (--z[x] == 1)
					q.push(x);
			}
		}
	}

	/* sprawdzamy, czy w ostatnim rozwazanym wierzcholku nalezy zapalic lont */
	if (j >= 0)
		if ((min_tab[p] < 0) || ((max_tab[p] == 0) && (d[p] == 1)))
			--j;
	
	/* jezeli nie podpalilismy za duzo lontow i przetworzylismy cale drzewo *
	 * to mozna w [czas] jednostek czasu podpalic wszystkie dynamity        */
	return ((j >= 0) && (q.empty())); 
}


/*****************************  MAIN  ************************************/
int main() {
	wczytaj();
	
	if (x <= m) {
		printf ("0\n");
		return 0;
	}
	
	/* sprawdzamy kolejne wartosci poczynajac od 1 */
	a = 1;
	while (!sprawdz (a))
		++a;

	printf ("%d\n", a);

	return 0;
}
