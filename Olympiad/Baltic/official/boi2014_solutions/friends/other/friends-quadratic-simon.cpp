#include <iostream>
#include <string>
using namespace std;

int a(int a, int b) {
	return a >= b ? a+1 : a;
}
int N;
int main() {
	cin >> N;
	string S;
	cin >> S;
	int sz = (int)S.size(), N = sz / 2;

	char value = 0;
	for (int i = 0; i < sz; ++i)
		value ^= S[i];

	string sol;
	for (int i = 0; i < sz; ++i) {
		if (S[i] != value) continue;
		for (int j = 0; j < N; ++j) {
			if (S[a(j, i)] != S[a(j+N, i)])
				goto fail;
		}
		if (!sol.empty()) {
			cout << "NOT UNIQUE" << endl;
			return 0;
		}
		sol = (S.substr(0, i) + S.substr(i + 1)).substr(0, N);
fail:;
	}
	cout << sol << endl;
}
