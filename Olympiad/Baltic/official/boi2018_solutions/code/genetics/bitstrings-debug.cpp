#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int main() {
	cin.sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	vector<string> strings(N);
	for (int i = 0; i < N; ++i) cin >> strings[i];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			int count = 0;
			for (int k = 0; k < M; ++k) {
				count += (strings[i][k] != strings[j][k]);
			}
			if (count != K) {
				clog << j << ", " << flush;
				goto fail;
			}
		}
		cout << i + 1 << endl;
		// return 0;
fail:;
	}
	// return 1;
}
