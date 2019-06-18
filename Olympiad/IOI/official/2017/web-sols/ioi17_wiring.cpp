#include "wiring.h"
#include <bits/stdc++.h>
using namespace std;
const int inf = 1234567890;
typedef pair<int, int> pi;
typedef long long lint;

int n;
pi a[1000005];
set<int> sa, sb;

int getnear(int x){
	int ret = 2e9;
	if(a[x].second == 1){
		auto p = sa.lower_bound(a[x].first);
		if(p != sa.end()){
			ret = min(ret, *p - a[x].first);
		}
		if(p != sa.begin()){
			p--;
			ret = min(ret, a[x].first - *p);
		}
	}
	else{
		auto p = sb.lower_bound(a[x].first);
		if(p != sb.end()){
			ret = min(ret, *p - a[x].first);
		}
		if(p != sb.begin()){
			p--;
			ret = min(ret, a[x].first - *p);
		}
	}
	return ret;
}

lint suma[1000005], sumb[1000005];
lint dp[1000005];
int mat[1000005], prv[2000005];

long long min_total_length(std::vector<int> aa, std::vector<int> bb) {
	int p = aa.size();
	int q = bb.size();
	for(int i=1; i<=p; i++){
		a[i].first = aa[i-1];
		sa.insert(aa[i-1]);
		a[i].second = -1;
	}
	for(int i=1; i<=q; i++){
		a[i+p].first = bb[i-1];
		sb.insert(bb[i-1]);
		a[i+p].second = 1;
	}
	n = p+q;
	sort(a+1, a+n+1);
	memset(mat, -1, sizeof(mat));
	memset(prv, -1, sizeof(prv));
	prv[n] = 0;
	int cur = n;
	for(int i=1; i<=n; i++){
		suma[i] = suma[i-1];
		sumb[i] = sumb[i-1];
		if(a[i].second == -1){
			suma[i] += a[i].first;
			cur++;
		}
		else{
			sumb[i] += a[i].first;
			cur--;
		}
		if(prv[cur] >= 0){
			mat[i] = prv[cur];
		}
		prv[cur] = i;
	}
	for(int i=1; i<=n; i++){
		dp[i] = dp[i-1] + getnear(i);
		if(~mat[i]){
			dp[i] = min(dp[i], dp[mat[i]] + abs(suma[i] - suma[mat[i]] - sumb[i] + sumb[mat[i]]));
		}
	}
	return dp[n];
}
