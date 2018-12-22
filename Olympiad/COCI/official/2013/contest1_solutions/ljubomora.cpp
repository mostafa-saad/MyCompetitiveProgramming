#include <cstdio>
using namespace std;

int a[300000];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int maks = 0;
	for (int i = 0; i < m; ++i) {
		scanf("%d", a+i);
		if (maks < a[i])
			maks = a[i];
	}
	int lo = 0, hi = maks;
	while (lo < hi) {
		int y = (lo + hi) / 2;
		int n2 = 0;
		for (int i = 0; i < m; ++i)
			n2 += (a[i] + y - 1) / y;
		if (n2 > n)
			lo = y + 1;
		else
			hi = y;
	}
	printf("%d\n", lo);
}
