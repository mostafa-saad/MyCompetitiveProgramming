/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe - trudniejsze               *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000000;

int n;

vector<int> kra[MAXN]; // Wektor krawedzi.

int poddrzewo[MAXN], najglebszy_dol[MAXN], najglebszy_gora[MAXN], p[MAXN];
long long suma[MAXN];

// Dfs liczacy wielkosci poddrzew, sume odleglosci od potomkow oraz najdalszego potomka. Idzie od lisci do korzenia.
void dfs(int u) {
	poddrzewo[u] = 1;
	najglebszy_dol[u] = 0;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			p[kra[u][i]] = u;
			dfs(kra[u][i]);
			poddrzewo[u] += poddrzewo[kra[u][i]];
			najglebszy_dol[u] = max(najglebszy_dol[u], najglebszy_dol[kra[u][i]] + 1);
			suma[u] += suma[kra[u][i]] + poddrzewo[kra[u][i]];
		}
	}
}

// Dfs liczacy sume odleglosci od wszystkich wierzcholkow oraz najdalszy wierzcholek, do ktorego sciezka prowadzi przez ojca. Idzie od korzenia do lisci.
void dfs2(int u) {
	int mx1 = -1, mx2 = -1;
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			if(najglebszy_dol[kra[u][i]] > mx1) {
				mx2 = mx1;
				mx1 = najglebszy_dol[kra[u][i]];
			} else if(najglebszy_dol[kra[u][i]] > mx2) {
				mx2 = najglebszy_dol[kra[u][i]];
			}
		}
	}
	// Magia :)
	for(int i=0; i<int(kra[u].size()); ++i) {
		if(kra[u][i] != p[u]) {
			suma[kra[u][i]] = suma[u] - 2*poddrzewo[kra[u][i]] + n;
			int best = mx1;
			if(najglebszy_dol[kra[u][i]] == mx1) {
				best = mx2;
			}
			najglebszy_gora[kra[u][i]] = max(najglebszy_gora[u]+1, max(1, best+2));
			dfs2(kra[u][i]);
		}
	}
}

int l;
int wiel[MAXN], najgl[MAXN];

int main() {
	scanf("%d", &n);
	// Budujemy graf.
	for(int i=0; i<n-1; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		kra[u].push_back(v);
		kra[v].push_back(u);
	}
	p[0] = -1;
	// Liczymy odpowiednie wartosci dla kazdego wierzcholka.
	dfs(0);
	dfs2(0);
	
	// Jezeli ktos nie wierzy, to moze odkomentowac i zobaczyc, ze program dobrze liczy.
	/* for(int u=0; u<n; ++u) {
		printf("poddrzewo[%d] = %d\n",u+1,poddrzewo[u]);
		printf("najglebszy_dol[%d] = %d\n",u+1,najglebszy_dol[u]);
		printf("najglebszy_gora[%d] = %d\n",u+1,najglebszy_gora[u]);
		printf("suma_odleglosci[%d] = %lld\n",u+1,suma[u]);
	} */
	
	// Zgodnie z opracowaniem odpowiadamy na pytanie dla kazdego wierzcholka.
	for(int u=0; u<n; ++u) {
		l = 0;
		for(int i=0; i<int(kra[u].size()); ++i) { // Dla wygody dodajemy informacje o poddrzewach do osobnej tablicy.
			if(kra[u][i] != p[u]) {
				wiel[l] = poddrzewo[kra[u][i]];
				najgl[l] = najglebszy_dol[kra[u][i]];
				++l;
			} else {
				wiel[l] = n - poddrzewo[u];
				najgl[l] = najglebszy_gora[u] - 1;
				++l;
			}
		}
		long long best = 2*suma[u]; // W najgorszym razie przebedziemy dwa razy suma[u] (tak wlasciwie to 2*suma[u] - 1).
		bool ok=true; // ok <-> mozemy skonczyc w dowolnym poddrzewie 
		for(int i=0; i<l; ++i) {
			if(2*wiel[i] > n) { // Nie istnieje przechadzka, wynik ustawiamy na 0.
				best = -1;
				ok = false;
				break;
			}
			if(2*wiel[i] == n) { // Przechadzka istnieje, ale musimy skonczyc w najwiekszym poddrzewie, wiec ustawiamy odpowiednio wynik.
				best = 2*suma[u] - najgl[i] - 1;
				ok = false;
				break;
			}
		}
		if(ok) { // Jezeli mozemy skonczyc gdziekolwiek, to sprawdzamy, gdzie jest najlepiej.
			for(int i=0; i<l; ++i) {
				best = min(best, 2*suma[u] - najgl[i] - 1);
			}
		}
		printf("%lld\n",best); // Pamietamy o typie 64-bitowym :) i wypisujemy wynik.
	}
	return 0;
}
