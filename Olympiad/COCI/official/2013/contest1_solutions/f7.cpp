#include <cstdio>
#include <algorithm>
using namespace std;

int a[300000];

bool cmp(int x, int y) { return x > y; }

int main () {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a+i);
	sort(a, a+n, cmp);
	int s = 0;
	int maks = 0;
	for (int i = 0; i < n; ++i) {
		s += (a[i] + n >= maks);
		maks = max(maks, a[i] + i + 1); 
	}
	printf("%d\n", s);
}
