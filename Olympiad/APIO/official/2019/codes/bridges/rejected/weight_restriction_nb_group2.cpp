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
	vector<int> arr;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		arr.push_back(c);
	}
	int bpv = 1;
	while (bpv < n) {
		bpv *= 2;
	}
	vector<int> rmq(bpv * 2);
	for (int i = 0; i < n - 1; ++i) {
		rmq[i + bpv] = arr[i];
	}
	for (int i = bpv - 1; i; --i) {
		rmq[i] = min(rmq[i * 2], rmq[i * 2 + 1]);
	}

	function<int(int, int, int, int, int)> segtree_get = [&](int v, int vl, int vr, int l, int r) {
		if (vr <= l || r <= vl) {
			return INF;
		}
		if (l <= vl && vr <= r) {
			return rmq[v];
		}
		int vm = (vl + vr) / 2;
		return min(segtree_get(v * 2, vl, vm, l, r), segtree_get(v * 2 + 1, vm, vr, l, r));
	};
	auto segtree_set = [&](int pos, int val) {
		pos += bpv;
		rmq[pos] = val;
		pos /= 2;
		while (pos) {
			rmq[pos] = min(rmq[pos * 2], rmq[pos * 2 + 1]);
			pos /= 2;
		}
	};
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		int t;
		cin >> t;
		if (t == 1) {
			int b, r;
			cin >> b >> r;
			segtree_set(b - 1, r);
		} else {
			int v, w;
			cin >> v >> w;
			--v;
			int l = -1, r = v;
			while (r - l > 1) {
				int mid = (l + r) / 2;
				if (segtree_get(1, 0, bpv, mid, v) < w) {
					l = mid;
				} else {
					r = mid;
				}
			}
			int mem = r;
			l = v, r = n;
			while (r - l > 1) {
				int mid = (l + r) / 2;
				if (segtree_get(1, 0, bpv, v, mid) < w) {
					r = mid;
				} else {
					l = mid;
				}
			}
			cout << l - mem + 1 << "\n";
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
