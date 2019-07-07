#include <iostream>
#include <cstdlib>
#include <bitset>
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

	vector<vector<uint64_t>> strings;
	int M2;
	if (expand) {
		M2 = (M*3 + 63) / 64;
		strings.assign(N, vector<uint64_t>(M2));
		for (int i = 0; i < N; ++i) {
			string& str = input[i];
			for (int j = 0; j < M; ++j) {
				int v = (str[j] >> 1) & 3;
				uint64_t b0 = 0, b1 = 0, b2 = 0;
				if (v == 0) b0 = b1 = b2 = 1;
				else if (v == 1) b0 = 1;
				else if (v == 2) b1 = 1;
				else if (v == 3) b2 = 1;

				int j0 = j*3, j1 = j*3+1, j2 = j*3+2;
				strings[i][j0 / 64] |= b0 << (j0 & 63);
				strings[i][j1 / 64] |= b1 << (j1 & 63);
				strings[i][j2 / 64] |= b2 << (j2 & 63);
			}
		}
		K *= 2;
	} else {
		M2 = (M + 63) / 64;
		strings.assign(N, vector<uint64_t>(M2));
		for (int i = 0; i < N; ++i) {
			string& str = input[i];
			for (int j = 0; j < M; ++j)
				strings[i][j / 64] |= (uint64_t)(str[j] == 'C') << (j & 63);
		}
	}

	vector<bool> iscandidate(N, true);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			size_t count = 0;
			for (int k = 0; k < M2; ++k) {
				count += bitset<64>(strings[i][k]^strings[j][k]).count();
			}
			if (count != (size_t)K) {
				// clog << j << ", " << flush;
				goto fail;
			}
		}
		cout << i + 1 << endl;
		return 0;
fail:;
	}
	return 1;
}
