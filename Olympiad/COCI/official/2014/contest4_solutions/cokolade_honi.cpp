#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1010;
const int MAXV = 1000000;

int n, cnt[MAXV + 5];
int ans[MAXN];

int main(void) {

	memset(ans, -1, sizeof ans);

	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		int v; scanf("%d", &v);
		cnt[v]++;
	}

	for(int i = 1; i <= MAXV; ++i)
		cnt[i] += cnt[i - 1];

	for(int t = 1; t <= MAXV; ++t) {
		for(int l = 0; l <= MAXV; l += t) {
			int r = min(MAXV, l + t - 1);
			int p = cnt[r];
			if(l > 0) p -= cnt[l - 1];
			if(ans[p] == -1) ans[p] = t;
		}
	}

	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);

	return 0;

}
