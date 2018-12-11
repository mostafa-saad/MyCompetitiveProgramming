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

struct edge {
	int f, c;
	edge(int _c) : f(0), c(_c) {}
};

vector<edge> edges;
vector<vector<pii>> graph;

int add_node() {
	graph.push_back({});
	return szof(graph) - 1;
}

void add_edge(int a, int b, int c) {
	graph[a].push_back({b, szof(edges)});
	edges.push_back(edge(c));
	graph[b].push_back({a, szof(edges)});
	edges.push_back(edge(0));
}

void solve() {
	int n, m;
	cin >> n >> m;
	vector<pii> init_edges;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		init_edges.push_back({a, b});
	}

	vector<pii> from;
	ll ans = 0;
	vector<int> cnt(n);
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				if (k == i || k == j) {
					continue;
				}

				graph.clear();
				edges.clear();

				vector<pii> nodes;
				for (int q = 0; q < n; ++q) {
					nodes.push_back({add_node(), add_node()});
					add_edge(nodes[q].ff, nodes[q].ss, 1);
				}

				for (auto e : init_edges) {
					add_edge(nodes[e.ff].ss, nodes[e.ss].ff, 1);
					add_edge(nodes[e.ss].ss, nodes[e.ff].ff, 1);
				}

				int s = add_node();
				int t = add_node();
				add_edge(s, nodes[k].ss, 2);
				add_edge(nodes[i].ss, t, 1);
				add_edge(nodes[j].ss, t, 1);

				from.resize(szof(graph));
				int f = 0;
				while (f < 2) {
					queue<int> q;
					q.push(s);
					fill(from.begin(), from.end(), make_pair(-1, -1));
					while (szof(q)) {
						int v = q.front();
						q.pop();
						for (auto to : graph[v]) {
							if (edges[to.ss].f < edges[to.ss].c && from[to.ff].ff == -1) {
								from[to.ff] = {v, to.ss};
								q.push(to.ff);
							}
						}
					}

					if (from[t].ff == -1) {
						break;
					}

					int cur = t;
					while (cur != s) {
						int e = from[cur].ss;
						edges[e].f += 1;
						edges[e ^ 1].f -= 1;
						cur = from[cur].ff;
					}
					++f;
				}

				if (f == 2) {
					cnt[k]++;
					++ans;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cerr << cnt[i] << " ";
	}
	cerr << endl;
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