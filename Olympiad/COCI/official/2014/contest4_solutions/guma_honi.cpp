#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

int n, v[MAXN];
long long ans = 0;

int main(void) {

	scanf("%d", &n);
	v[0] = 1;

	for(int i = 1; i <= n + 1; ++i) {
		scanf("%d", v + i);
		ans += v[i] - __gcd(v[i], v[i - 1]);
	}

	printf("%lld\n", ans);

	return 0;

}
