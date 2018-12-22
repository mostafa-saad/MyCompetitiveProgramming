#include <cstdio>
#include <cstring>
using namespace std;

int brojac[32], d[300005];

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);

	long long rjesenje = 0;

	for (int i = 0; i < n; ++i)
	{
		char rijec[21];
		scanf("%s", rijec);

		d[i] = strlen(rijec);
		rjesenje += brojac[d[i]];

		if (i >= k)
			--brojac[d[i - k]];
		++brojac[d[i]];
	}
	printf("%lld\n", rjesenje);
}
