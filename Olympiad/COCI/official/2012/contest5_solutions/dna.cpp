#include<cstdio>

inline int min( int a, int b )
{ return a>b?b:a; }

char s[1000005];
int f[1000005], g[1000005];

int main()
{
	int n;
	scanf("%d", &n);

	scanf("%s", s);

	f[0] = g[0] = 0;

	for(int i=0; i<n; i++)
		if( s[i] == 'A' )
		{
			f[i+1] = f[i];
			g[i+1] = 1 + min( f[i], g[i] );
		}
		else
		{
			g[i+1] = g[i];
			f[i+1] = 1 + min( f[i], g[i] );
		}
	printf("%d\n", f[n]);
}
