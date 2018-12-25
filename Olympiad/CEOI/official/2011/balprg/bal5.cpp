/* Model solution for the task BAL (Balloons)
 * Author: Jakub Pachocki
 * O(n*log(Z)) time solution
 * Searching for max radius with binary search
 */


#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

struct Balloon {
	int x;
	long double radius;
};

long double sq(long double x) {
	return x * x;
}

long double getMaxRadius(long double r1, long double dx) {
	long double l = 0, r = 1000000000;
	for (int i = 0; i < 70; ++i) {
		long double c = (l + r) / 2;
		if (sqrt((r1 - c) * (r1 - c) + dx * dx) < r1 + c)
			r = c;
		else
			l = c;
	}
	return r;
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
			maxRadius = min(maxRadius, getMaxRadius(s[ss - 1].radius, s[ss - 1].x - pos));
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
