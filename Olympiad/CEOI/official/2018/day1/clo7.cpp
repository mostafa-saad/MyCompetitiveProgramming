// Kamil Debowski
// OBL, AC solution
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	vector<pair<int, pair<int,int>>> events;
	for(int rep = 0; rep < 2; ++rep) {
		int n;
		scanf("%d", &n);
		while(n--) {
			int cnt, freq, cost;
			scanf("%d%d%d", &cnt, &freq, &cost);
			if(rep == 0) {
				cost *= -1; // cost of CPU
			}
			else {
				cnt *= -1;
			}
			// otherwise gain from a task
			events.push_back({freq, {cnt, cost}});
		}
	}
	sort(events.rbegin(), events.rend());
	vector<ll> dp{0};
	for(int i = 0; i < (int) events.size(); ++i) {
		vector<ll> dp2 = dp;
		for(int cnt = 0; cnt < (int) dp.size(); ++cnt) {
			int cnt2 = cnt + events[i].second.first;
			ll maybe_cost = dp[cnt] + events[i].second.second;
			if(cnt2 >= 0) {
				while((int) dp2.size() <= cnt2) dp2.push_back(LONG_LONG_MIN / 2);
				dp2[cnt2] = max(dp2[cnt2], maybe_cost);
			}
		}
		dp = dp2;
	}
	ll answer = 0;
	for(ll x : dp) answer = max(answer, x);
	printf("%lld\n", answer);
}
