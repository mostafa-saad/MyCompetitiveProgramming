/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Modyfikacje:       Jacek Tomasiewicz                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Binarnie wyszukujemy minimalnego czasu, w ktorym *
 *                      mozemy wysadzic ladunki                          *
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
int a, b, c, i, p, x, lonty;	/* zmienne pomocnicze */
int z[MAX_N + 1];	/* tablice pomocnicze */
int ogien[MAX_N + 1], dynamit[MAX_N + 1]; 
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
	while (!q.empty())
		q.pop();
	for (i = 1; i <= n; ++i) {
        dynamit[i] = d[i] - 1;
		ogien[i] = -1;
		z[i] = korytarze[i].size();
		if (z[i] == 1)
			q.push(i);
	}
	
	lonty = 0;
	/* wyznaczamy miejsca, w ktorych musimy podpalic lont */
	while (!q.empty()) {
		p = q.front();
		q.pop();
		if (ogien[p] >= dynamit[p]) /* zapali sie od poprzedniego lontu */
			dynamit[p] = -1;
		
        if (dynamit[p] == czas) { /* musimy podpalic lont */
			lonty++;
			ogien[p] = czas;
			dynamit[p] = -1;
		}

		for (size_t i = 0; i < korytarze[p].size(); ++i) {
			x = korytarze[p][i];
			if (z[x] > 0) {
			    ogien[x] = max(ogien[x], ogien[p] - 1);

				if (dynamit[p] >= 0)
				    dynamit[x] = max(dynamit[x], dynamit[p] + 1);

				if (--z[x] == 1)
					q.push(x);
			}
		}
	}

	/* sprawdzamy, czy w ostatnim rozwazanym wierzcholku nalezy zapalic lont */
	if (dynamit[p] >= 0)
		lonty++;
	
	/* jezeli nie podpalilismy za duzo lontow                               *
	 * to mozna w [czas] jednostek czasu podpalic wszystkie dynamity        */
	return lonty <= m; 
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
