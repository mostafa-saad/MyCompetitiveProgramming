// BOI 2011
// Task PLAGIARISM
// Ahto Truu, ahto.truu@ut.ee

// Solution with binary search
// O(N) memory, O(NlogN) time

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
	for (int i = 0; i < n; ++i) {
		// smallest possible size of smaller file: 0.9*a[i], rounded up
		int g = (9 * f[i] - 1) / 10 + 1;
		int *p = lower_bound(f, f + i, g);
		k += f + i - p;
	}

	cout << k << endl;
	return 0;
}
