#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

constexpr int INF = 2001001001;
constexpr int MAX_N = 200;

template <class T> bool chmin(T &a, T b) {
	if (b < a) {
		a = b;
		return true;
	}
	return false;
}

struct edge {
	int v, c, i;
	edge(int iv, int ic, int ii) {
		v = iv;
		c = ic;
		i = ii;
	}
};

void dijkstra(int n, const vector<edge> *e, int *w, bool *used, int s, int t) {
	int pv[n], pe[n];
	fill(w, w + n, INF);
	w[s] = 0;
	bool fin[n];
	fill(fin, fin + n, false);
	for (;;) {
		int p = -1;
		int mn = INF;
		for (int j = 0; j < n; j++) {
			if (!fin[j] && chmin(mn, w[j])) p = j;
		}
		if (p == -1) break;
		for (edge g : e[p]) {
			if (chmin(w[g.v], w[p] + g.c)) {
				pv[g.v] = p;
				pe[g.v] = g.i;
			}
		}
		fin[p] = true;
	}
	if (w[t] < INF) {
		for (; t != s; t = pv[t]) {
			used[pe[t]] = true;
		}
	}
}

int W[MAX_N + 1];
int dijkstra(int n, const vector<edge> *e, const vector<edge> *f, int i, int s, int t) {
	fill(W, W + n, INF);
	W[s] = 0;
	for (;;) {
		int p = -1;
		int mn = INF;
		for (int j = 0; j < n; j++) {
			if (W[j] >= 0 && chmin(mn, W[j])) p = j;
		}
		if (p == -1 || p == t) break;
		for (edge g : e[p]) {
			if (g.i == i) continue;
			chmin(W[g.v], W[p] + g.c);
		}
		for (edge g : f[p]) {
			if (g.i != i) continue;
			chmin(W[g.v], W[p] + g.c);
		}
		W[p] = -1;
	}
	return W[t];
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<edge> e[2][n];
	int u[m], v[m], c[m], d[m];
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d%d", u + i, v + i, c + i, d + i);
		u[i]--;
		v[i]--;
		e[0][u[i]].push_back(edge(v[i], c[i], i));
		e[1][v[i]].push_back(edge(u[i], c[i], i));
	}

	bool used[2][m];
	bool dum[m];
	fill(used[0], used[2], false);
	int x[2][n], y[2][n];
	dijkstra(n, e[0], x[0], used[0], 0, n - 1);
	dijkstra(n, e[0], x[1], used[1], n - 1, 0);
	dijkstra(n, e[1], y[0], dum, n - 1, 0);
	dijkstra(n, e[1], y[1], dum, 0, n - 1);
	int w[2] = {x[0][n - 1], x[1][0]};

	ll ans = (ll)w[0] + w[1];
	for (int i = 0; i < m; i++) {
		ll tmp = d[i];
		for(int b = 0; b < 2; b++) {
			if(used[b][i]) {
				tmp += dijkstra(n, e[b], e[!b], i, 0, n - 1);
			} else {
				tmp += min((ll)w[b], (ll)c[i] + x[b][v[i]] + y[b][u[i]]);
			}
		}
		chmin(ans, tmp);
	}

	if (ans >= INF) ans = -1;
	printf("%lld\n", ans);
	return 0;
}
