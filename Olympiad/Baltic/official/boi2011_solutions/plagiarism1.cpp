// BOI 2011
// Task PLAGIARISM
// Ahto Truu, ahto.truu@ut.ee

// Naive solution with pairwise comparison
// O(N) memory, O(N^2) time

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;

	int *f = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> f[i];
	}

	long long k = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (10 * min(f[i], f[j]) >= 9 * max(f[i] , f[j])) {
				++k;
			}
		}
	}

	cout << k << endl;
	return 0;
}
