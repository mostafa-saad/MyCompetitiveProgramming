#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll>pii;
typedef pair<ll, pii>pi3;
int main()
{
	int num, query;
	scanf("%d%d", &num, &query);
	ll dif = 1;
	int beg = 0;
	vector<pi3>v;
	for (int i = 1; i <= num; i++)
	{
		ll z;
		scanf("%lld", &z);
		if (z > dif)
		{
			v.push_back(make_pair(dif, make_pair(beg, i - 1)));
			dif = (z + dif - 1) / dif*dif;
			beg = i;
		}
	}
	v.push_back(make_pair(dif, make_pair(beg, num)));
	for (int p = 0; p < query; p++)
	{
		ll zt, zl, zr;
		scanf("%lld%lld%lld", &zt, &zl, &zr);
		ll ans = 0;
		for (int i = 0; i < v.size(); i++)
		{
			ll end = zt / v[i].first*v[i].first - v[i].second.first;
			ll beg = end + v[i].second.first - v[i].second.second;
			ans += max(0LL, min(zr, end) - max(zl, beg) + 1);
		}
		printf("%lld\n", ans);
	}
}