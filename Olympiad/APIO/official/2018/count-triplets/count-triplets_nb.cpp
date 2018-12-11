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

const int MAXN = 3e5 + 5, MAXM = 5e5 + 5;

vector<pii> graph[MAXN];

int up[MAXN];
int depth[MAXN];
vector<bool> used;
int edge_color[MAXM];
vector<int> st;
int cnt_color;

int dfs(int v, int e, int d) {
	used[v] = true;
	depth[v] = d;
	up[v] = d;
	for (pii to : graph[v]) {
		if (!used[to.ff]) {
			st.push_back(to.ss);
			dfs(to.ff, to.ss, d + 1);
			up[v] = min(up[v], up[to.ff]);
			if (up[to.ff] >= depth[v]) {
				while (st.back() != to.ss) {
					edge_color[st.back()] = cnt_color;
					st.pop_back();
				}
				edge_color[st.back()] = cnt_color++;
				st.pop_back();
			}
		} else if (e != to.ss) {
			if (depth[to.ff] < depth[v]) {
				st.push_back(to.ss);
			}
			up[v] = min(up[v], depth[to.ff]);
		}
	}

	return 0;
}

vector<int> sz_subtree;
vector<ll> prod;

int calc_szs(int v, int p, vector<vector<int>> const& tree, vector<int> const& szs) {
	int& ret = sz_subtree[v];
	ret = szs[v];

	for (int to : tree[v]) {
		if (to != p) {
			ret += calc_szs(to, v, tree, szs);
		}
	}
	return ret;
}

int calc_prod(int v, int p, vector<vector<int>> const& tree, vector<int> const& szs, int tot) {
	int sum = tot - sz_subtree[v];
	for (int to : tree[v]) {
		if (to != p) {
			calc_prod(to, v, tree, szs, tot);
			prod[v] += (ll) sum * sz_subtree[to];
			sum += sz_subtree[to];
		}
	}

	//cerr << "prod " << v << " " << prod[v] << endl;
	return 0;
}

ll calc_ans(int v, int p, vector<vector<int>> const& tree, vector<int> const& szs, int tot) {
	used[v] = true;
	ll ret = 0;
	int sum = tot - sz_subtree[v];
	ret += (ll) szs[v] * (szs[v] - 1) * (tot - sz_subtree[v]);
	if (p != -1 && p < cnt_color) {
		ret += (ll) szs[v] * szs[p] * (szs[p] - 1) / 2;
		ret += (ll) szs[v] * szs[p] * (tot - sz_subtree[v] - szs[p]);
	}
	if (p != -1 && v >= cnt_color) {
		ret += (ll) prod[p] - (ll) sz_subtree[v] * (tot - sz_subtree[v] - szs[p]);
	}
	ret += (ll) szs[v] * (szs[v] - 1) * (szs[v] - 2) / 2;
	//cerr << v << " " << sz_subtree[v] << endl;
	ll tmp = 0;
	for (int to : tree[v]) {
		if (to != p) {
			//cerr << v << " " << to << " " << (ll) sum * szs[v] * sz_subtree[to] << endl;
			ret += (ll) szs[v] * (szs[v] - 1) * sz_subtree[to];
			if (to < cnt_color) {
				ret += (ll) szs[v] * szs[to] * (szs[to] - 1) / 2;
				ret += (ll) szs[v] * szs[to] * (sz_subtree[to] - szs[to]);
			}
			if (v >= cnt_color) {
				ret += (ll) prod[to] - (ll) (sz_subtree[to] - szs[to]) * (tot - sz_subtree[to]);
			}
			//cerr << "add " << v << " " << (ll) sum * szs[v] * sz_subtree[to] << endl;
			ret += (ll) sum * szs[v] * sz_subtree[to];
			tmp += calc_ans(to, v, tree, szs, tot);
			sum += sz_subtree[to];
		}
	}
	//cerr << v << " " << ret << endl;
	ret += tmp;
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
		if (a == b) {
			continue;
		}
		graph[a].push_back({b, szof(edges)});
		graph[b].push_back({a, szof(edges)});
		edges.push_back({a, b});
	}

	m = szof(edges);

	fill(edge_color, edge_color + m, -1);
	used = vector<bool>(n);
	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			dfs(i, -1, 0);
		}
	}

	/*
	for (int i = 0; i < m; ++i) {
		cerr << edge_color[i] << " ";
	}
	cerr << endl;
	*/

	ll ans = 0;
	vector<vector<int>> tree(cnt_color);
	vector<int> szs(cnt_color);
	vector<int> was(cnt_color);
	int tcnt = 1;
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		int any = -1;
		++tcnt;
		for (pii to : graph[i]) {
			if (was[edge_color[to.ss]] != tcnt) {
				++cnt;
				any = edge_color[to.ss];
				was[edge_color[to.ss]] = tcnt;
			}
		}

		
		if (!cnt) {
			continue;
		} else if (cnt == 1) {
			szs[any]++;
		} else {
			tree.push_back({});
			szs.push_back(1);
			++tcnt;
			for (pii to : graph[i]) {
				if (was[edge_color[to.ss]] != tcnt) {
					was[edge_color[to.ss]] = tcnt;
					tree.back().push_back(edge_color[to.ss]);
					tree[edge_color[to.ss]].push_back(szof(tree) - 1);
				}
			}
		}
	}

	/*
	for (int i = 0; i < szof(tree); ++i) {
		cerr << "i: " << i << " " << szs[i] << endl;
		for (int to : tree[i]) {
			cerr << to << " ";
		}
		cerr << endl;
	}
	*/

	used = vector<bool>(szof(tree));

	sz_subtree = vector<int>(szof(tree));

	prod = vector<ll>(szof(tree));

	for (int i = 0; i < szof(tree); ++i) {
		if (!used[i]) {
			int tot = calc_szs(i, -1, tree, szs);
			calc_prod(i, -1, tree, szs, tot);
			ans += calc_ans(i, -1, tree, szs, tot);
		}
	}

	cout << ans * 2 << "\n";
}


int main() {
	//freopen("in", "r", stdin);
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