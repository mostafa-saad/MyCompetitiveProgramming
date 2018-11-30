// BOI 2011
// Task PLAGIARISM
// Ahto Truu, ahto.truu@ut.ee

// Solution with two parallel linear scans
// O(N) memory, O(NlogN) time (for sorting)

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

	sort(f, f + n);

	long long k = 0;
	for (int i = 0, j = 0; i < n; ++i) {
		while (10 * f[j] < 9 * f[i]) {
			++j;
		}
		k += i - j;
	}

	cout << k << endl;
	return 0;
}
