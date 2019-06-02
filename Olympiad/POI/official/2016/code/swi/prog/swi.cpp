/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O((n * log(n) + m) * find_union)                   *
 *   Zlozonosc pamieciowa: O(n * log(n))                                      *
 *   Opis:                 Rozwiazanie wzorcowe                               *
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

template<int max_elements>
struct FU {
	int fut[max_elements + 5];
	int fuf(int w) {
		if (fut[w] == w)
			return w;
		return fut[w] = fuf(fut[w]);
	}
	void fuu(int u, int v) {
		fut[fuf(u)] = fuf(v);
	}
};

FU<limit> rownosci[logarytm + 5];

int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= logarytm; i++)
		for (int j = 1; j <= n; j++)
			rownosci[i].fut[j] = j;
	while (m--) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		const int potega_dwojki = podloga_z_logarytmu_dwojkowego(l);
		rownosci[potega_dwojki].fuu(a, b);
		rownosci[potega_dwojki].fuu(a + l - (1 << potega_dwojki), b + l - (1 << potega_dwojki));
	}
	for (int i = logarytm; i > 0; i--) {
		for (int a = 1; a <= n; a++) {
			const int b = rownosci[i].fuf(a);
			rownosci[i - 1].fuu(a, b);
			if (max(a, b) + (1 << (i - 1)) <= n)
				rownosci[i - 1].fuu(a + (1 << (i - 1)), b + (1 << (i - 1)));
		}
	}
	int wynik = 0;
	for (int i = 1; i <= n; i++)
		if (rownosci[0].fuf(i) == i)
			wynik++;
	printf("%d\n", wynik);
	return 0;
}
