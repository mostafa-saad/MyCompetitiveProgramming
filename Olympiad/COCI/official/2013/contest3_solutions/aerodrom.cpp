#include<cstdio>
using namespace std;

int a[300001];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	long long lo = 0, hi = 0;
	for(int i=0; i < n; i++) {
		scanf("%d", a+i);
		if (hi < a[i])
			hi = a[i];
	}
	hi *= m;
	while( lo < hi )
	{
		long long mid = (lo+hi)/2;
		long long kol = 0;
		for(int i=0; i<n; i++)
			kol += mid / a[i];
		if( kol < m ) lo = mid+1;
		else hi = mid;
	}
	printf("%lld\n", lo);
}
