/* Model solution for the task BAL (Balloons)
 * Author: Jakub Pachocki
 * O(n) time solution
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
		while (ss > 0) {
			long double c = sq(s[ss - 1].x - pos);
			maxRadius = min(maxRadius, c / (4 * s[ss - 1].radius));
			if (maxRadius > s[ss - 1].radius - 1e-10)
				--ss;
			else
				break;
		}
		printf("%.3Lf\n", maxRadius);
		s[ss].x = pos;
		s[ss].radius = maxRadius;
		++ss;
	}
}
