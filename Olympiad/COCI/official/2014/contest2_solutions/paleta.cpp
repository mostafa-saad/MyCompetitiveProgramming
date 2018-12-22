#include <cstdio>
#include <set>

using namespace std;

typedef long long llint;

const int MAXN = 1000010;
const int MOD = 1000000007;

int N, K, f[MAXN];
llint calc[MAXN], g[MAXN];
int disc[MAXN], t = 1;
int cycle_size;

int find(int start) {
	int curr = start;
	while(1) {
		if(disc[curr] != 0 && disc[curr] < disc[start]) return 0;
		if(disc[curr] != 0) return t - disc[curr];
		disc[curr] = t++;
		curr = f[curr];
	}
}

int main(void) {

	scanf("%d%d", &N, &K);
	for(int i = 1; i <= N; ++i) scanf("%d", f + i);

	g[0] = 1;
	g[1] = K;
	g[2] = ((llint)K - 1) * g[1] % MOD;
	g[3] = ((llint)K - 2) * g[2] % MOD;

	for(int i = 4; i <= N; ++i)
		g[i] = ((K - 1) * g[i - 2] + (K - 2) * g[i - 1]) % MOD;

	llint ans = 1;

	for(int i = 1; i <= N; ++i)
		if(disc[i] == 0) {
			int x = find(i);
			ans = (llint)ans * g[x] % MOD;
			cycle_size += x;
		}

	for(int i = 0; i < N - cycle_size; ++i)
		ans = (llint)ans * (K - 1) % MOD;

	printf("%lld\n", ans);

	return 0;

}
