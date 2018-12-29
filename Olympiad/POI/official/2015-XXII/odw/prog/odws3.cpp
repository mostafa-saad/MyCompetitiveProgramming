/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Odwiedziny                                         *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Autor programu:       Jan Kanty Milczek                                  *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 100000;

int n, c[MaxN + 1], cel, t[MaxN], k[MaxN - 1];
vector<int> kra[MaxN + 1];
bool odw[MaxN + 1];
vector<int> stos, trasa;

void dfs(int x) {
	odw[x] = true;
	stos.push_back(x);
	if (x == cel)
		trasa = stos;
	for (vector<int>::iterator it = kra[x].begin(); it != kra[x].end(); ++it)
		if (!odw[*it])
			dfs(*it);
	stos.pop_back();
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", c + i);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		kra[u].push_back(v);
		kra[v].push_back(u);
	}
	for (int i = 0; i < n; ++i)
		scanf("%d", t + i);
	for (int i = 0; i < n - 1; ++i)
		scanf("%d", k + i);
	for (int i = 0; i < n - 1; ++i) {
		int wyn = 0;
		cel = t[i + 1];
		fill(odw, odw + n + 1, false);
		dfs(t[i]);
		for (unsigned j = 0; j < trasa.size(); j += k[i])
			wyn += c[trasa[j]];
		printf("%d\n", wyn);
	}
}
