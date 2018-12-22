#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 300010;
const int MOD = 1000000007;

typedef long long llint;

int n;
pair<int, int> p[MAXN];

bool cmp (pair<int, int> a, pair<int, int> b) {
	return (llint)a.first * b.second < (llint)a.second * b.first;
}

int main(void) {

	scanf("%d", &n);

	for(int i = 0; i < n; ++i) {
		int a, b; scanf("%d%d%*d", &a, &b);
		p[i] = make_pair(a, b);
	}

	sort(p, p + n, cmp);

	int l = 0, r = 0;
	llint ans = 0;

	for(int i = 0; i < n; ++i) {
		while(cmp(p[l], p[i])) ++l;  									// we don't actually calculate functions less(i) and greater (i)
		while(r < n && !cmp(p[i], p[r])) ++r;					// it suffices to have two pointers in the array, l and r
		ans += (llint)l * (n - r) % MOD;
		ans %= MOD;
	}

	printf("%lld\n", ans);

	return 0;

}
