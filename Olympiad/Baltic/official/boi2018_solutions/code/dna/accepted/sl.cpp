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
	vi v(n);
	vi counts(k);
	rep(i,0,n) {
		cin >> v[i];
		assert(0 <= v[i] && v[i] < k);
		counts[v[i]]++;
	}
	int failed = 0;
	vi have(k), wanted(k);
	rep(i,0,r) {
		int sym, co;
		cin >> sym >> co;
		assert(0 <= sym && sym < k);
		assert(co > 0);
		if (counts[sym] < co) {
			cerr << "impossible" << endl;
			cout << "impossible" << endl;
			return 0;
		}
		wanted[sym] = co;
		++failed;
	}
	int i = 0, j = 0;
	int res = INT_MAX, occ = 0;
	for (;;) {
		if (failed) {
			if (j == n) break;
			if (++have[v[j]] == wanted[v[j]]) failed--;
			j++;
		} else {
			int dif = j - i;
			if (dif < res) res = dif, occ = 0;
			if (dif == res) occ++;
			assert(i < j);
			if (have[v[i]]-- == wanted[v[i]]) failed++;
			i++;
		}
	}
	assert(res != INT_MAX);
	cout << res << endl;
	cerr << res << ", " << occ << " places" << endl;
}
