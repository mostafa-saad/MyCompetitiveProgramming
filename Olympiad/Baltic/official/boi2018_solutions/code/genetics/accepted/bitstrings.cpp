#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

int main() {
	cin.sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	vector<vector<int> > strings(N, vector<int>(M));
	vector<bool> iscandidate(N, true);
	int ncand = N;
	string str;
	for (int i = 0; i < N; ++i) {
		cin >> str;
		for (int j = 0; j < M; ++j)
			strings[i][j] = (str[j] >> 1) & 3;
	}
	while (ncand > 1) {
		vector<unsigned> weight(N);
		unsigned totweight = 0;
		for (int i = 0; i < N; ++i) {
			weight[i] = rand();
			totweight += weight[i];
		}
		vector<unsigned> count[4];
		count[0].assign(M, 0);
		count[1].assign(M, 0);
		count[2].assign(M, 0);
		count[3].assign(M, 0);
		for (int i = 0; i < N; ++i) {
			unsigned w = weight[i];
			for (int j = 0; j < M; ++j) {
				count[strings[i][j]][j] += w;
			}
		}
		for (int i = 0; i < N; ++i) {
			if (!iscandidate[i]) continue;
			unsigned sumdif = 0;
			for (int j = 0; j < M; ++j)
				sumdif += totweight - count[strings[i][j]][j];
			unsigned expectedsumdif = (totweight - weight[i]) * K;
			if (sumdif != expectedsumdif) {
				iscandidate[i] = false;
				--ncand;
			}
		}
	}
	int ans = -1;
	for (int i = 0; i < N; ++i) {
		if (iscandidate[i]) {
			ans = i;
		}
	}
	assert(ans != -1);
	for (int i = 0; i < N; ++i) if (i != ans) {
		int dif = 0;
		for (int j = 0; j < M; ++j)
			dif += (strings[i][j] != strings[ans][j]);
		assert(dif == K);
	}
	cout << ans + 1 << endl;
	return 0;
}
