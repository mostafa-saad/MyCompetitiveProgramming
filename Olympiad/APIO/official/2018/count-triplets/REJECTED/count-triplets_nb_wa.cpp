#include "bits/stdc++.h"
#define ff first
#define ss second
#define szof(_x) ((int) (_x).size())
#define TASK_NAME ""

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 1e9 + 7;
const ll INFL = 1e18 + 123;
const double PI = atan2(0, -1);
mt19937 tw(960172);
ll rnd(ll x, ll y) { static uniform_int_distribution<ll> d; return d(tw) % (y - x + 1) + x; }

const int MAXN = 3e5 + 5;

vector<pii> graph[MAXN];

int up[MAXN];
int depth[MAXN];
bool used[MAXN];

int dfs(int v, int e, int d) {
	used[v] = true;
	depth[v] = d;
	up[v] = d;
	for (pii to : graph[v]) {
		if (!used[to.ff]) {
			dfs(to.ff, to.ss, d + 1);
			up[v] = min(up[v], up[to.ff]);
		} else if (e != to.ss) {
			up[v] = min(up[v], up[to.ff]);
		}
	}
	return 0;
}

int color[MAXN];
int cnt_color = 0;
int of_color[MAXN];

int paint(int v, int c) {
	used[v] = true;
	color[v] = c;
	of_color[c]++;
	for (pii to : graph[v]) {
		if (!used[to.ff]) {
			if (up[to.ff] == depth[to.ff]) {
				paint(to.ff, cnt_color++);
			} else {
				paint(to.ff, c);
			}
		}
	}
	return 0;
}

vector<int> tree[MAXN];
int sz[MAXN];
vector<int> visited;

int calc_szs(int v, int p) {
	visited.push_back(v);
	sz[v] = of_color[v];
	for (int to : tree[v]) {
		if (to != p) {
			calc_szs(to, v);
			sz[v] += sz[to];
		}
	}
	return 0;
}

ll calc_on_tree(int v, int p, int tot) {
	used[v] = true;
	ll ret = 0;
	int sum = tot - sz[v];
	for (int to : tree[v]) {
		if (to != p) {
			ret += calc_on_tree(to, v, tot);
			ret += (ll) sum * sz[to] * of_color[v];
			sum += sz[to];
		}
	}
	return ret;
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<pii> edges;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		graph[a].push_back({b, i});
		graph[b].push_back({a, i});
		edges.push_back({a, b});
	}

	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			dfs(i, -1, 0);
		}
	}

	fill(used, used + n, 0);
	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			paint(i, cnt_color++);
		}
	}

	ll ans = 0;
	for (int i = 0; i < cnt_color; ++i) {
		ans += (ll) of_color[i] * (of_color[i] - 1) * (of_color[i] - 2) / 2;
	}

	for (int i = 0; i < m; ++i) {
		if (color[edges[i].ff] != color[edges[i].ss]) {
			tree[color[edges[i].ff]].push_back(color[edges[i].ss]);
			tree[color[edges[i].ss]].push_back(color[edges[i].ff]);
		}
	}

	fill(used, used + cnt_color, 0);
	for (int i = 0; i < cnt_color; ++i) {
		if (!used[i]) {
			visited.clear();
			calc_szs(i, -1);
			for (int v : visited) {
				ans += (of_color[v] - 1 + (ll) (of_color[v] - 1) * (of_color[v] - 2)) * (sz[i] - of_color[v]);
			}
			ans += calc_on_tree(i, -1, sz[i]);
		}
	}

	cout << ans * 2 << "\n";
}


int main() {
	//freopen(TASK_NAME ".in", "r", stdin);
	//freopen(TASK_NAME ".out", "w", stdout);
	cerr << fixed << setprecision(15);
	cout << fixed << setprecision(15);
	ios::sync_with_stdio(false);

	int tests = 1;
	// cin >> tests;
	for (int it = 1; it <= tests; ++it) {
		solve();
	}
	
	#ifdef LOCAL
		cerr << "time: " << clock() << " ms\n";
	#endif
	return 0;
}