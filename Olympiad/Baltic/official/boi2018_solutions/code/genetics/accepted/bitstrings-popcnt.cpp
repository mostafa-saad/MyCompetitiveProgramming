#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
using namespace std;

#define trav(a, x) for (auto& a : x)

int main() {
	cin.sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	vector<string> input(N);
	for (int i = 0; i < N; ++i) cin >> input[i];
	bool expand = false;
	trav(x, input) trav(y, x) {
		if (y == 'G' || y == 'T') expand = true;
	}

	int realM = M;
	if (expand) {
		M *= 3;
		K *= 2;
	}
	int N2 = (N + 63) / 64;
	vector<vector<uint64_t>> strings(M, vector<uint64_t>(N2));
	vector<bool> iscandidate(N, true);
	vector<int> rc(N);
	vector<vector<int>> mat(N, vector<int>(M));
	int ncand = N;
	for (int i = 0; i < N; ++i) {
		string& str = input[i];
		int co = 0;
		for (int j = 0; j < realM; ++j) {
			int v = (str[j] >> 1) & 3;
			if (expand) {
				int v0 = 0, v1 = 0, v2 = 0;
				if (v == 0) v0 = v1 = v2 = 1;
				else if (v == 1) v0 = 1;
				else if (v == 2) v1 = 1;
				else if (v == 3) v2 = 1;
				int j0 = 3*j+0;
				int j1 = 3*j+1;
				int j2 = 3*j+2;

				strings[j0][i / 64] |= uint64_t(v0) << (i & 63);
				mat[i][j0] = 1 - 2 * v0;
				co += v0;
				strings[j1][i / 64] |= uint64_t(v1) << (i & 63);
				mat[i][j1] = 1 - 2 * v1;
				co += v1;
				strings[j2][i / 64] |= uint64_t(v2) << (i & 63);
				mat[i][j2] = 1 - 2 * v2;
				co += v2;
			} else {
				strings[j][i / 64] |= uint64_t(v) << (i & 63);
				mat[i][j] = 1 - 2 * v;
				co += v;
			}
		}
		rc[i] = co;
	}

	vector<bool> included(N);
	vector<uint64_t> bincluded(N2);
	vector<int> count(M, 0);
	while (ncand > 1) {
		unsigned int nincluded = 0;
		bincluded.assign(N2, 0);
		for (int i = 0; i < N; ++i) {
			included[i] = (rand() >> 14) & 1;
			bincluded[i / 64] |= uint64_t(included[i]) << (i & 63);
			nincluded += included[i] ? 1 : 0;
		}
		for (int j = 0; j < M; ++j) {
			int co = 0;
			for (int i = 0; i < N2; ++i)
				co += __builtin_popcountll(strings[j][i] & bincluded[i]);
			count[j] = co;
		}
		for (int i = 0; i < N; ++i) {
			if (!iscandidate[i]) continue;
			unsigned int sumdif = 0;
			for (int j = 0; j < M; ++j)
				sumdif += count[j] * mat[i][j];
			sumdif += nincluded * rc[i];
			unsigned int expectedsumdif = nincluded * K - (included[i] ? K : 0);
			if (sumdif != expectedsumdif) {
				iscandidate[i] = false;
				--ncand;
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		if (iscandidate[i]) {
			cout << i + 1 << endl;
			return 0;
		}
	}
	cout << "nothing!" << endl;
	return 1;
}
