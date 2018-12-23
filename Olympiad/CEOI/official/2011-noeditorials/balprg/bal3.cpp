/* Model solution for the task BAL (Balloons)
 * Author: Jakub Pachocki
 * O(n) time solution
 * using iostream instead of cstdio
 */

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Balloon {
	int x;
	long double radius;
};

long double sq(long double x) {
	return x * x;
}

Balloon s[200000];
int ss;

int n;

int main() {
	ios_base::sync_with_stdio(0);
	cin >> n;
	cout << fixed;
	cout << setprecision(3);
	for (int i = 0; i < n; ++i) {
		int pos;
		cin >> pos;
		int size;
		cin >> size;
		long double maxRadius = size;
		while (ss > 0) {
			long double c = sq(s[ss - 1].x - pos);
			maxRadius = min(maxRadius, c / (4 * s[ss - 1].radius));
			if (maxRadius > s[ss - 1].radius - 1e-10)
				--ss;
			else
				break;
		}
		cout << maxRadius << "\n";
		s[ss].x = pos;
		s[ss].radius = maxRadius;
		++ss;
	}
}
