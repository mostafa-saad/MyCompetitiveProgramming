/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Odwiedziny                                         *
 *   Zlozonosc czasowa:    O(n * sqrt(q) + q * log n)                         *
 *   Autor programu:       Jan Kanty Milczek                                  *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <vector>
#include <algorithm>
#include <cstdio>
#define FOR(_it, _cont) for (__typeof((_cont).begin()) _it = (_cont).begin(); _it != (_cont).end(); ++_it)
#define scanf(Args...) (scanf(Args)?:0)
using namespace std;

const int MaxN = 100000;
const int MaxLogN = 18;

int n, c[MaxN], t[MaxN], k[MaxN - 1], wynik[MaxN - 1];
vector<int> kra[MaxN];

struct Ojcostwo {
	int preO[MaxN], postO[MaxN], time, skok[MaxN][MaxLogN], gle[MaxN];
	void dfs(int x) {
		preO[x] = time++;
		FOR(it, kra[x])
			if (!gle[*it]) {
				skok[*it][0] = x;
				gle[*it] = gle[x] + 1;
				dfs(*it);
			}
		postO[x] = time;
	}
	bool przodek(int x, int y) {
		return preO[x] <= preO[y] && postO[x] >= postO[y];
	}
	int lca(int x, int y) {
		if (przodek(x, y))
			return x;
		for (int s = MaxLogN - 1; s >= 0 && !przodek(y, x); --s)
			if (!przodek(skok[y][s], x))
				y = skok[y][s];
		if (!przodek(y, x))
			y = skok[y][0];
		return y;
	}
	int odleglosc(int x, int y) {
		return gle[x] + gle[y] - (gle[lca(x, y)] << 1);
	}
	int skokO(int x, int o) {
		for (int s = 0; s < MaxLogN; ++s) {
			if (o&1)
				x = skok[x][s];
			o >>= 1;
		}
		return x;
	}
	void preparuj() {
		gle[0] = 1;
		skok[0][0] = 0;
		dfs(0);
		for (int s = 1; s < MaxLogN; ++s)
			for (int i = 0; i < n; ++i)
				skok[i][s] = skok[skok[i][s - 1]][s - 1];
	}
} LCA;

struct DuzeK {
	int zbieraj(int x, int cel, int k) {
		int wyn = 0;
		while (!LCA.przodek(x, cel)) {
			wyn += c[x];
			x = LCA.skokO(x, k);
		}
		return wyn;
	}
	int solve(int x, int y, int k) {
		int cel = LCA.lca(x, y);
		return zbieraj(x, cel, k) + zbieraj(y, cel, k);
	}
} duzeK;

struct MaleK {
	vector<int> pytanie[MaxN];
	int sum[MaxN], K;
	void solveAll(int K) {
		this->K = K;
		for (int i = 0; i < n; ++i) {
			pytanie[i].clear();
			sum[i] = 0;
		}
		for (int i = 0; i < n - 1; ++i)
			if (k[i] == K) {
				pytanie[t[i]].push_back(i);
				pytanie[t[i + 1]].push_back(i);
			}
		dfs(0);
	}
	void dfs(int x) {
		sum[x] = c[x] + sum[LCA.skokO(x, K)];
		FOR(it, kra[x])
			if (!sum[*it])
				dfs(*it);
		FOR(it, pytanie[x]) {
			int odl = LCA.odleglosc(x, LCA.lca(t[*it], t[*it + 1]));
			odl = (odl + K - 1) / K * K;
			wynik[*it] += sum[x] - sum[LCA.skokO(x, odl)];
		}
	}
} maleK;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", c + i);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		kra[u].push_back(v);
		kra[v].push_back(u);
	}
	LCA.preparuj();
	for (int i = 0; i < n; ++i) {
		scanf("%d", t + i);
		--t[i];
	}
	for (int i = 0; i < n - 1; ++i)
		scanf("%d", k + i);
	int klimit;
	for (klimit = 1; klimit * klimit < n; ++klimit)
		maleK.solveAll(klimit);
	for (int i = 0; i < n - 1; ++i)
		if (!wynik[i])
			wynik[i] = duzeK.solve(t[i], t[i + 1], k[i]);
	for (int i = 0; i < n - 1; ++i)
		if (LCA.odleglosc(t[i], LCA.lca(t[i], t[i + 1])) % k[i] == 0)
			wynik[i] += c[LCA.lca(t[i], t[i + 1])];
	for (int i = 0; i < n - 1; ++i)
		printf("%d\n", wynik[i]);
};
