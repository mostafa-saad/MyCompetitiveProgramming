#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MOD 1000007

typedef long long int huge;

huge *f[MAXN];
int a[MAXN];
int n;

void Maximize(int& a, int b)
{
	if(b > a)
	{
		a = b;
	}
}

huge F(int i, int m)
{
	if(i == n) return 1;
	if(f[i][m]) return f[i][m];
	return f[i][m] = ((m * F(i + 1, m)) + (F(i + 1, m + 1))) % MOD;
}

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
	  	f[i] = (huge *) calloc (n + 1, sizeof (huge));
		scanf("%d", a + i);
	}

	huge rsl = 0;
	int m = 1;
	for(int i = 0; i < n; i++)
	{
		if(a[i] == 1)
		{
			continue;
		}

		rsl += (a[i] - 1) * F(i + 1, m);
		Maximize(m, a[i]);
	}

	printf("%lld\n", (rsl + 1) % MOD);
	return 0;
}
