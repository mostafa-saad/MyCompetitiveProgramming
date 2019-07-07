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
	int N, M, K;
	cin >> N >> M >> K;
	vi col(N);
	rep(i,0,N) {
		cin >> col[i], --col[i];
		assert(0 <= col[i] && col[i] < K);
	}
	vector<vi> ed(N);
	rep(i,0,M) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[a].push_back(b);
		ed[b].push_back(a);
	}
	vi order(K);
	iota(all(order), 0);
	long long res = 0;
	vector<ll> dp(N), next(N);
	do {
		rep(i,0,N) dp[i] = (col[i] == order[0]);
		rep(k,1,K) {
			rep(i,0,N) {
				ll r = 0;
				if (col[i] == order[k]) {
					trav(x, ed[i]) r += dp[x];
				}
				next[i] = r;
			}
			swap(dp, next);
			if (is_sorted(order.begin() + k + 1, order.end())) {
				rep(i,0,N) res += dp[i];
			}
		}
	} while (next_permutation(all(order)));
	cout << res << endl;
}
