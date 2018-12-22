#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int odb[512][512];
int dp[512][512];
int best[512][512];
const int inf = 1000000000;

void izracunaj_dpove(int lo, int hi)
{
	if (hi == lo + 2) {
		dp[lo][lo + 1] = dp[lo + 1][lo] = odb[lo][lo + 1];
		return;
	}
	int mid = (lo + hi) / 2;
	izracunaj_dpove(lo, mid);
	izracunaj_dpove(mid, hi);

	int mid1 = (lo + mid) / 2;
	int mid2 = (mid + hi) / 2;

	for (int a = lo; a < mid; ++a)
		for (int D = mid; D < hi; ++D) {
			best[a][D] = inf;
			int from, to;
			if (D < mid2) {
				from = mid2;
				to = hi;
			} else {
				from = mid;
				to = mid2;
			}
			for (int b = from; b < to; ++b)
				best[a][D] = min(best[a][D], odb[a][b] + dp[b][D]);
		}

	for (int L = lo; L < mid; ++L)
		for (int D = mid; D < hi; ++D) {
			dp[L][D] = inf;
			int from, to;
			if (L < mid1) {
				from = mid1;
				to = mid;
			} else {
				from = lo;
				to = mid1;
			}
			for (int a = from; a < to; ++a)
				dp[L][D] = min(dp[L][D], dp[L][a] + best[a][D]);
			dp[D][L] = dp[L][D];
		}
}

int main()
{
	int k;
	scanf("%d", &k);
	int n = 1 << k;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; ++j)
			scanf("%d", &odb[i][j]);

	izracunaj_dpove(0, n);

	int sol = inf;
	for (int L = 0; L < n/2; ++L)
		for (int D = n/2; D < n; ++D)
			sol = min(sol, dp[L][D]);

	printf("%d\n", sol);
}
