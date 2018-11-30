// BOI 2011
// Task MEETINGS
// Ahto Truu, ahto.truu@ut.ee

// Optimized dynamic programming solution
// O(N) memory, O(N^1.5) time

#include <iostream>
using namespace std;

int main() {
	int n, p, v;
	cin >> n >> p >> v;

	int *a = new int[1 + n];
	a[1] = 0; // special case: no meeting
	for (int i = 2; i <= n; ++i) {
		a[i] = i * p + v; // baseline: no subgroups
		for (int j = 1; j * j <= i; ++j) {
			// consider dividing the group of i into j subgroups
			// the size of biggest subgroup will be i/j rounded up
			int k = (i - 1) / j + 1;
			// now the total time is a[k] for subgroup meetings
			// plus a[j] for the meeting(s) of subgroup leaders
			int t = a[k] + a[j];
			// is it better than the best option we have so far?
			if (a[i] > t) {
				a[i] = t;
			}
			// if we were to divide the group into subgroups of j,
			// then the number of subgroups would be i/j rounded up
			// and the total time would be the same, of course
		}
	}

	cout << a[n] << endl;
	return 0;
}
