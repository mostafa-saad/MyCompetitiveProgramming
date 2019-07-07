#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int n, k, r;
	cin >> n >> k >> r;
	assert(r > 0);
	vi v(n);
	vi counts(k);
	rep(i,0,n) {
		cin >> v[i];
		assert(0 <= v[i] && v[i] < k);
		counts[v[i]]++;
	}
	rep(i,0,k) assert(counts[i] > 0);

	vi have(k);
	vector<pii> interesting;
	rep(i,0,r) {
		int sym, co;
		cin >> sym >> co;
		assert(0 <= sym && sym < k);
		assert(co > 0);
		if (counts[sym] < co) {
			cout << "impossible" << endl;
			return 0;
		}
		interesting.emplace_back(sym, co);
	}

	int i = 0, j = 0;
	auto works = [&]() {
		bool r = true;
		for (int k = i; k < j; k++) {
			have[v[k]]++;
		}
		trav(x, interesting) {
			if (have[x.first] < x.second) {
				r = false;
				break;
			}
		}
		for (int k = i; k < j; k++) {
			have[v[k]]--;
		}
		return r;
	};

	int res = INT_MAX;
	for (;;) {
		if (works()) {
			res = min(res, j - i);
			++i;
		} else {
			++j;
			if (j > n) break;
		}
	}
	cout << res << endl;
}
