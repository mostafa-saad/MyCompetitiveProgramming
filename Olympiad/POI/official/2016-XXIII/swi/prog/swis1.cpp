/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Swiateczny lancuch                                 *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(s * find_union), O(nm * find_union),             *
 *                         gdzie s = l_1 + l_2 + ... + l_m.                   *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

const int limit = 500 * 1000;

int fut[limit + 5];

int fuf(int w) {
	if (fut[w] == w)
		return w;
	return fut[w] = fuf(fut[w]);
}

void fuu(int u, int v) {
	fut[fuf(u)] = fuf(v);
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		fut[i] = i;
	for (int i = 1; i <= m; i++) {
		int a, b, l;
		scanf("%d%d%d", &a, &b, &l);
		for (int j = 0; j < l; j++)
			fuu(a + j, b + j);
	}
	int wynik = 0;
	for (int i = 1; i <= n; i++)
		if (fuf(i) == i)
			wynik++;
	printf("%d\n", wynik);
	return 0;
}
