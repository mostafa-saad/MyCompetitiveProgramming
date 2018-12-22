
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task ZBRKA
  Programming language C++
*/

#include <cstdio>

#define maxk 10001
#define mod 1000000007

int n, k, dp[2][maxk]; // za racunanje relacije treba nam samo trenutni i zadnji red

int main(void) {
   scanf( "%d%d", &n, &k );
	dp[1][0] = 1;
	for( int i = 2; i <= n; i++ ) {
		int tmp = 0;
		for( int j = 0; j <= k; j++ ) {
			tmp = (tmp+dp[(i-1)&1][j])%mod;
			if( j >= i ) tmp = (tmp-dp[(i-1)&1][j-i]+mod)%mod;
			dp[i&1][j] = tmp;
		}
	}
	printf( "%d\n", dp[n&1][k] );
	return 0;
}
