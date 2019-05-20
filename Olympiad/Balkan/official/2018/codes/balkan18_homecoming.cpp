#include<bits/stdc++.h>
#include "homecoming.h"
using namespace std;
using lint = long long;
const int MAXN = 4000005;
 
lint a[MAXN], b[MAXN], dp[MAXN];
 
long long solve(int N, int K, int *A, int *B){
	for(int i=1; i<=N; i++){
		a[i] = a[i+N] = A[i-1];
		b[i] = b[i+N] = B[i-1];
	}
	for(int i=1; i<=2*N; i++){
		a[i] += a[i-1];
		b[i] += b[i-1];
	}
	if(K == N){
		return max(0ll, a[N] - b[N]);
	}
	// First DP : Go across the interval
	lint ans = max(0ll, a[N] - b[N]);
	dp[N+1] = 0;
	lint curmax = -1e18;
	for(int i=N; i; i--){
		dp[i] = a[N] - a[i-1] - (b[N] - b[i-1]); // [i, N]
		dp[i] = max(dp[i], dp[i+1]); // Fuck it
		dp[i] = max(dp[i], curmax + b[i-1] - a[i-1]);
		curmax = max(curmax, dp[i] - b[i + K - 2] + a[i - 1]);
		if(i + K - 2 <= N) ans = max(ans, dp[i] + a[i-1] - b[i + K - 2]);
	}
	dp[N+1] = 0;
	curmax = -1e18;
	// Second DP : Act like it never existed
	for(int i=N; i; i--){
		dp[i] = dp[i+1];
		dp[i] = max(dp[i], curmax + b[i-1] - a[i-1]);
		curmax = max(curmax, dp[i] - b[i + K - 2] + a[i - 1]);
	}
	ans = max(ans, dp[1]);
	return ans;
}