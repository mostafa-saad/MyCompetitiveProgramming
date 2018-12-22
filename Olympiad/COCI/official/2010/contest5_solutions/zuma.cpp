#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

const int MAXN = 128;
const int MAXK = 5;
const int inf = 1000000000;

int n, k;
int A[ MAXN ];

int dp[ MAXN ][ MAXN ][ MAXK ];

int solve( int l, int r, int prije )
{
    if( l > r ) return 0;
    if( l == r ) return k-1-prije;

    int &ref = dp[l][r][prije];
    if( ref != -1 ) return ref;
    ref = inf;

    if( prije < k-1 ) ref = solve( l, r, prije+1 ) + 1;
    if( prije == k-1 ) ref = solve( l+1, r, 0 );

    for( int i = l+1; i <= r; ++i ) {
        if( A[i] != A[l] ) continue;
        int val = solve( l+1, i-1, 0 ) + solve( i, r, min( k-1, prije+1 ) );
        if( val < ref ) ref = val;
    }

    return ref;
}

int main( void )
{
    scanf( "%d %d", &n, &k );

    for( int i = 0; i < n; ++i )
        scanf( "%d", A + i );

    memset( dp, -1, sizeof dp );
    printf( "%d\n", solve( 0, n-1, 0 ) );

    return (0-0);
}
