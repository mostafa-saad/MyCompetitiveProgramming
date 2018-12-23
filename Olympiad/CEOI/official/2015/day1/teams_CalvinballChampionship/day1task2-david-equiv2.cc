#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001
#define MOD 1000007

typedef long long int huge;

huge A1[MAXN];
huge A2[MAXN];
int Max[MAXN];
int a[MAXN];
int n;

int GetMax(int a, int b)
{
	return (a > b) ? a : b;
}

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", a + i);
	}

	Max[0] = 0;
	for(int i = 0; i < n; i++)
	{
		Max[i + 1] = GetMax(Max[i], a[i]);
	}

	huge rsl = 0;
	for(int i = n; i >= 1; i--)
	{
		huge* A = (i % 2) ? A1 : A2;
		huge* B = (i % 2) ? A2 : A1;

		for(int j = 1; j <= i; j++)
		{
			if(i == n)
			{
				A[j] = 1;
			}
			else
			{
				A[j] = ((j * B[j]) + B[j + 1]) % MOD;
			}
		}

		rsl += (a[i - 1] - 1) * A[Max[i - 1]];
	}

	printf("%lld\n", (rsl + 1) % MOD);
	return 0;
}
