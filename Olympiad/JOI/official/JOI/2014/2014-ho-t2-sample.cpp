#include <bits/stdc++.h>
using namespace std;

const int INF = 1001001001;
const int LIM_M = 10000;
const int LIM_N = 500;

int M, N;
int P[LIM_M + 10];
int C[LIM_N + 10], E[LIM_N + 10];

int PSum[LIM_M + 10];
int dp[LIM_M + 10];

int main() {
	int i, j;
	
	scanf("%d%d", &M, &N);
	for (i = 0; i < M; ++i) {
		scanf("%d", &P[i]);
	}
	for (j = 0; j < N; ++j) {
		scanf("%d%d", &C[j], &E[j]);
	}
	
	//	PSum[i] := maximum price for selling i manjus.
	sort(P, P + M, greater<int>());
	for (i = 0; i < M; ++i) {
		PSum[i + 1] = PSum[i] + P[i];
	}
	
	//	dp[i] := minimum expense for boxes to pack i manjus.
	//	invariant: dp[0] <= dp[1] <= ... <= dp[M].
	for (i = 0; i <= M; ++i) {
		dp[i] = INF;
	}
	dp[0] = 0;
	for (j = 0; j < N; ++j) {
		for (i = M; i >= 0; --i) {
			if (dp[i] > dp[max(i - C[j], 0)] + E[j]) {
				dp[i] = dp[max(i - C[j], 0)] + E[j];
			}
		}
	}
	
	int ans = 0;
	for (i = 0; i <= M; ++i) {
		if (ans < PSum[i] - dp[i]) {
			ans = PSum[i] - dp[i];
		}
	}
	printf("%d\n", ans);
	
	return 0;
}

