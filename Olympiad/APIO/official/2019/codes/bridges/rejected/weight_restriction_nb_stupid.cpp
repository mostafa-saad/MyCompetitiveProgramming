// Created by Nikolay Budin

#ifdef LOCAL
#  define _GLIBCXX_DEBUG
#else
#  define cerr __get_ce
#endif
#include <bits/stdc++.h>
#define ff first
#define ss second
#define szof(x) ((int)x.size())

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef unsigned long long ull;
int const INF = (int)1e9 + 1e3;
ll const INFL = (ll)1e18 + 1e6;
#ifdef LOCAL
	mt19937 tw(9450189);
#else
	mt19937 tw(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif
uniform_int_distribution<ll> ll_distr;
ll rnd(ll a, ll b) { return ll_distr(tw) % (b - a + 1) + a; }


void solve() {
	int n, m;
	cin >> n >> m;
	vector<multiset<pii>> graph(n);
	vector<pair<pii, int>> edges;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		graph[a].insert({b, c});
		graph[b].insert({a, c});
		edges.push_back({{a, b}, c});
	}
	int q;
	cin >> q;
	vector<int> used(n, -1);
	vector<int> qu(n);
	for (int i = 0; i < q; ++i) {
		int type;
		cin >> type;
		if (type == 1) {
			int ind, w;
			cin >> ind >> w;
			--ind;
			int a, b;
			tie(a, b) = edges[ind].ff;
			int c = edges[ind].ss;
			graph[a].erase(graph[a].find({b, c}));
			graph[b].erase(graph[b].find({a, c}));
			graph[a].insert({b, w});
			graph[b].insert({a, w});
			edges[ind].ss = w;
		} else {
			int v, w;
			cin >> v >> w;
			--v;
			int l = 0, r = 0;
			qu[r++] = v;
			used[v] = i;
			while (l < r) {
				int v = qu[l++];
				for (pii to : graph[v]) {
					if (to.ss >= w && used[to.ff] != i) {
						used[to.ff] = i;
						qu[r++] = to.ff;
					}
				}
			}

			cout << r << "\n";
		}
	}
}


int main() {
#ifdef LOCAL
	auto start_time = clock();
	cerr << setprecision(3) << fixed;
#endif
	cout << setprecision(15) << fixed;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int test_count = 1;
	// cin >> test_count;
	for (int test = 1; test <= test_count; ++test) {
		solve();
	}
	
#ifdef LOCAL
	auto end_time = clock();
	cerr << "Execution time: " << (end_time - start_time) * (int)1e3 / CLOCKS_PER_SEC << " ms\n";
#endif
}
