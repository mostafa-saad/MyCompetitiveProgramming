#include <iostream>
#include <string>

using namespace std;

int dp[2048][2048][2];

void chmax(int& t, int f)
{
	if (t < f) {
		t = f;
	}
}

int main()
{
	int M, N;
	char S[2048], T[2048];

	cin >> M >> N >> S >> T;

	for (int i = 0; i < M; ++i) {
		S[i] = S[i] == 'I' ? 0 : 1;
	}
	for (int i = 0; i < N; ++i) {
		T[i] = T[i] == 'I' ? 0 : 1;
	}

	int res = 0;

	for (int s = 0; s <= M; ++s) {
		for (int t = 0; t <= N; ++t) {
			dp[s][t][0] = -1001001001;
			dp[s][t][1] = 0;
		}
	}

	for (int s = 0; s <= M; ++s) {
		for (int t = 0; t <= N; ++t) {
			if (s < M) chmax(dp[s + 1][t][S[s]], dp[s][t][1 - S[s]] + 1);
			if (t < N) chmax(dp[s][t + 1][T[t]], dp[s][t][1 - T[t]] + 1);
		}
	}
	for (int s = 0; s <= M; ++s) {
		for (int t = 0; t <= N; ++t) {
			chmax(res, dp[s][t][0]);
		}
	}

	cout << res << endl;

	return 0;
}
