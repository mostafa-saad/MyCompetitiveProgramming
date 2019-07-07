#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int main() {
	cin.sync_with_stdio(false);
	int N, K, D;
	cin >> N >> K >> D;
	vector<vector<bool> > strings(N, vector<bool>(K));
	string str;
	for (int i = 0; i < N; ++i) {
		cin >> str;
		for (int j = 0; j < K; ++j)
			strings[i][j] = (str[j] == '1');
	}
	vector<bool> included(N, true);
	unsigned int nincluded = N;
	vector<int> count(K, 0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			count[j] += strings[i][j];
		}
	}
	unsigned int expectedsumdif = (nincluded - 1) * D;
	int same = 0;
	for (int i = 0; i < N; ++i) {
		unsigned int sumdif = 0;
		for (int j = 0; j < K; ++j)
			sumdif += (strings[i][j] ? nincluded - count[j] : count[j]);
		if (sumdif != expectedsumdif) continue;
		same++;
		for (int k = 0; k < N; ++k) if (k != i) {
			int dif = 0;
			for (int j = 0; j < K; ++j)
				dif += (strings[i][j] != strings[k][j]);
			if (dif != D) goto fail;
		}
		cout << i+1 << endl;
		break;
fail:;
	}
	cerr << same << endl;
}
