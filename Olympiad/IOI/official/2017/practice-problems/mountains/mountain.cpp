//In the name of God
//...
#include <iostream>
#include "mountains.h"
using namespace std;
const int N = 2016;

int n, x[N], y[N], dp[N][N];

long long rot(int a, int b, int c) { return 1ll * (x[b] - x[a]) * (y[c] - y[a]) - 1ll * (y[b] - y[a]) * (x[c] - x[a]); }
int maximum_deevs(vector<int> h) {
	int n = h.size();
	for (int i = 0; i < n; i++) {
		x[i] = i;
		y[i] = h[i];
	}
	for (int e = 1; e <= n; e++) {
		dp[e][e] = dp[e - 1][e] = 1;
		int ls = e - 1, res = 0;
		for (int b = e - 2; b > 0; b--) {
			if (rot(b - 1, ls - 1, e - 1) >= 0) { // b is seen
				res += dp[b + 1][ls - 1];
				ls = b;
			}
			dp[b][e] = max(dp[b][e - 1], 1 + res + dp[b][ls - 1]);
		}
	}
	return dp[1][n];
}
