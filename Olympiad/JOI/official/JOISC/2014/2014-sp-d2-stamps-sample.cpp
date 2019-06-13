#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = 1 << 30; // > 10^9

int U[3005], V[3005], D[3005], E[3005];
int dp[3005][3005];

int main() {
	int N, T;
	scanf("%d%d", &N, &T);
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d%d%d", &U[i], &V[i], &D[i], &E[i]);
	}
	
	for (int i = 0; i <= N; ++i) fill(dp[i], dp[i] + N + 5, INF);
	dp[0][0] = 0;
	
	for (int i = 1; i <= N; ++i) {
		for(int j = 0; j < N + 5; ++j) {
			int base_cost = dp[i-1][j] + T * (j * 2 + 1);
			dp[i][j] = min(dp[i][j], base_cost + U[i] + V[i]);
			if (j > 0) dp[i][j] = min(dp[i][j], base_cost + D[i] + E[i]);
		}
		int best = INF;
		for(int j = 0; j < N + 5; ++j) {
			dp[i][j] = min(dp[i][j], best);
			best = min(best, dp[i-1][j] + T * (j * 2 + 1));
			best += V[i] + D[i];
			best = min(best, INF);
		}
		best = INF;
		for(int j = N + 4; j >= 0; --j) {
			dp[i][j] = min(dp[i][j], best);
			best = min(best, dp[i-1][j] + T * (j * 2 + 1));
			best += U[i] + E[i];
			best = min(best, INF);
		}
	}
	
	printf("%d\n", dp[N][0] + T);
	
	return 0;
}