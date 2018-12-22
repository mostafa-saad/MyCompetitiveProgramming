#include <cstdio>
#include <cstring>

#define MOD 10301

inline void add( int &a, int b ) {
    a += b;
    if( a >= MOD ) a -= MOD;
}

int N, A, B;
int memoL[1024][1024][2];
int memoR[1024][1024][2];

int recR( int n, int rub, bool ok ) {
    int &ret = memoR[n][rub][ok];
    if( ret != -1 ) return ret;

    ret = ok;
    if( rub <= n ) add( ret, recR(n-rub, rub, true) );
    if( n ) add( ret, recR(n-1, rub+1, false) );

    return ret;
}

int recL( int n, int rub, bool ok ) {
    int &ret = memoL[n][rub][ok];
    if( ret != -1 ) return ret;

    ret = 0;
    if( ok ) add( ret, recR(n, B, true) );
    if( rub <= n ) add( ret, recL(n-rub, rub, true) );
    if( n ) add( ret, recL(n-1, rub+1, false) );

    return ret;
}

int main( void ) {
    memset( memoL, -1, sizeof memoL );
    memset( memoR, -1, sizeof memoR );

    scanf( "%d%d%d", &N, &A, &B );

    printf( "%d\n", recL( N-A-B, A, true ) );

    return 0;
}
