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
	vector<pair<pii, int>> edges;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		edges.push_back({{a, b}, c});
	}

	const int SZ = 500;

	int q;
	cin >> q;
	vector<int> ans(q, -1);
	vector<bool> changed(m);
	vector<pair<pii, int>> actions;
	vector<pair<pii, int>> questions;
	vector<int> dsu(n);
	vector<int> sz(n);
	vector<pair<int*, int>> dsu_changes;
	auto get_root = [&](int v, int t) {
		int mem = v;
		while (dsu[v] != v) {
			v = dsu[v];
		}
		if (t) {
			while (dsu[mem] != mem) {
				int tmp = dsu[mem];
				dsu[mem] = v;
				mem = tmp;
			}
		}
		return v;
	};

	auto unite = [&](int a, int b, int t) {
		a = get_root(a, t);
		b = get_root(b, t);
		if (a == b) {
			return;
		}
		if (sz[a] < sz[b]) {
			swap(a, b);
		}
		dsu_changes.push_back({&sz[a], sz[a]});
		sz[a] += sz[b];
		dsu_changes.push_back({&dsu[b], dsu[b]});
		dsu[b] = a;
	};

	vector<int> static_edges;
	vector<int> not_static_edges;

	for (int i = 0; i < q; ++i) {
		int t;
		cin >> t;
		if (t == 1) {
			int ind, c;
			cin >> ind >> c;
			--ind;
			changed[ind] = true;
			actions.push_back({{ind, c}, i});
		} else {
			int v, w;
			cin >> v >> w;
			--v;
			questions.push_back({{w, v}, i});
		}
		if (i == q - 1 || szof(actions) == SZ) {
			sort(questions.begin(), questions.end());
			reverse(questions.begin(), questions.end());
			iota(dsu.begin(), dsu.end(), 0);
			fill(sz.begin(), sz.end(), 1);

			static_edges.clear();
			not_static_edges.clear();

			for (int j = 0; j < m; ++j) {
				if (!changed[j]) {
					static_edges.push_back(j);
				} else {
					not_static_edges.push_back(j);
				}
			}

			sort(static_edges.begin(), static_edges.end(), [&](int a, int b){
				return edges[a].ss > edges[b].ss;
			});

			vector<int> last(m);

			int cnt_static_edges = 0;
			for (auto q : questions) {
				while (cnt_static_edges < szof(static_edges) && edges[static_edges[cnt_static_edges]].ss >= q.ff.ff) {
					unite(edges[static_edges[cnt_static_edges]].ff.ff, edges[static_edges[cnt_static_edges]].ff.ss, 1);
					++cnt_static_edges;
				}
				int mem = szof(dsu_changes);
				
				for (int e : not_static_edges) {
					last[e] = edges[e].ss;
				}
				for (auto act : actions) {
					if (act.ss > q.ss) {
						break;
					}
					last[act.ff.ff] = act.ff.ss;
				}
				for (int e : not_static_edges) {
					if (last[e] >= q.ff.ff) {
						unite(edges[e].ff.ff, edges[e].ff.ss, 0);
					}
				}
				ans[q.ss] = sz[get_root(q.ff.ss, 0)];
				while (szof(dsu_changes) > mem) {
					*dsu_changes.back().ff = dsu_changes.back().ss;
					dsu_changes.pop_back();
				}
			}

			for (auto act : actions) {
				edges[act.ff.ff].ss = act.ff.ss;
			}

			actions.clear();
			questions.clear();
			fill(changed.begin(), changed.end(), 0);
		}
	}


	for (int num : ans) {
		if (num != -1) {
			cout << num << "\n";
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
