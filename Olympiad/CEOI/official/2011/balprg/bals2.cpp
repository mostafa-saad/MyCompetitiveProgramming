/* Slow solution for the task BAL (Balloons)
 * Author: Jakub Pachocki
 * O(n^2) time solution
 */

#include <cstdio>
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
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int pos;
		scanf("%d", &pos);
		int size;
		scanf("%d", &size);
		long double maxRadius = size;
		for (int j = ss - 1; j >= 0; --j) {
			long double c = sq(s[j].x - pos);
			maxRadius = min(maxRadius, c / (4 * s[j].radius));
		}
		printf("%.3Lf\n", maxRadius);
		s[ss].x = pos;
		s[ss].radius = maxRadius;
		++ss;
	}
}
