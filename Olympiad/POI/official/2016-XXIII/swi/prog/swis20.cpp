/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n * log(n) + m)                                  *
 *   Zlozonosc pamieciowa: O(n * log(n))                                      *
 *   Opis:                 Rozwiazanie wzorcowe - brak optymalizacji          *
 *****************************************************************************/


#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

constexpr int podloga_z_logarytmu_dwojkowego(int n) {
	return (n <= 1) ? 0 : 1 + podloga_z_logarytmu_dwojkowego(n / 2);
}

constexpr int limit = 500 * 1000;
constexpr int logarytm = podloga_z_logarytmu_dwojkowego(limit) + 2;

int n, m;

struct {
	vector<pair<int, int>> krawedzie;
	vector<vector<int>> sasiedzi;
	vector<bool> odwiedzone;
	vector<bool> pierwsze;
	void wywal_niepotrzebne_krawedzie() {
		sasiedzi.resize(n + 5);
		odwiedzone.resize(n + 5);
		pierwsze.resize(n + 5);
		for (pair<int, int> krawedz : krawedzie) {
			sasiedzi[krawedz.first].push_back(krawedz.second);
			sasiedzi[krawedz.second].push_back(krawedz.first);
		}
		krawedzie.clear();
		for (int i = 1; i <= n; i++) {
			if (!odwiedzone[i]) {
				dfs(i);
				pierwsze[i] = true;
			}
		}
	}
	void dfs(int w) {
		odwiedzone[w] = true;
		for (int sasiad : sasiedzi[w]) {
			if (!odwiedzone[sasiad]) {
				dfs(sasiad);
				krawedzie.emplace_back(w, sasiad);
			}
		}
	}
} graf[logarytm + 5];

int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		const int potega_dwojki = podloga_z_logarytmu_dwojkowego(l);
		graf[potega_dwojki].krawedzie.emplace_back(a, b);
		graf[potega_dwojki].krawedzie.emplace_back(a + l - (1 << potega_dwojki), b + l - (1 << potega_dwojki));
	}
	for (int i = logarytm; i > 0; i--) {
		graf[i].wywal_niepotrzebne_krawedzie();
		for (pair<int, int> krawedz : graf[i].krawedzie) {
			graf[i - 1].krawedzie.push_back(krawedz);
			graf[i - 1].krawedzie.emplace_back(krawedz.first + (1 << (i - 1)), krawedz.second + (1 << (i - 1)));
		}
	}
	graf[0].wywal_niepotrzebne_krawedzie();
	int wynik = 0;
	for (int i = 1; i <= n; i++)
		if (graf[0].pierwsze[i])
			wynik++;
	printf("%d\n", wynik);
	return 0;
}
