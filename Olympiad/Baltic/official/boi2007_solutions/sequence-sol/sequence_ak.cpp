// Author:	Adrian Kuegel
// Date: 	April 1st, 2007
// Algorithm:	greedy
// Complexity:	O(n)

#include <stdio.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#define MAXN 100000

int a[MAXN+1];

int main() {
	int n;

	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d",&n);
	assert(n >= 1 && n <= 100000);

	for (int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		assert(0 <= a[i] && a[i] <= 1000000);
	}

	a[0] = 1000001;
	long long cost = 0;
	int p = 0; // maintain a list of decreasing numbers

	for (int i=1; i<=n; ++i) {
		while(a[p] <= a[i])
			// remove a[p] with a reduce operation
			cost += min(a[--p], a[i]);
		a[++p] = a[i];
	}

	for (int i=1; i<p; ++i)
		cost += a[i];

	printf("%lld\n",cost);
	return 0;
}
