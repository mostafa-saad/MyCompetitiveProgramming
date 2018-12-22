#include <algorithm>
#include <cstdio>
#include <cstdlib>

#define MAX 300000
#define ITER 100

using namespace std;

typedef pair<int,int> par;

inline int myrand() {
    int a = rand()%5000;
    int b = rand()%5000;
    return a*5000+b;
}

int n, Q, C;
int a[MAX];
par b[MAX];

int main( void ) {
    scanf( "%d%d", &n, &C );
    for( int i = 0; i < n; ++i ) scanf( "%d", &a[i] );
    for( int i = 0; i < n; ++i ) b[i] = par( a[i], i );
    sort( b, b+n );

    scanf( "%d", &Q );
    for( int qq = 0; qq < Q; ++qq ) {
        int lo, hi;
        scanf( "%d%d", &lo, &hi ); --lo; --hi;

        int m = hi-lo+1;
        int iter, x, cnt;
        for( iter = 0; iter < ITER; ++iter ) {
            x = a[lo+myrand()%m];
            cnt = upper_bound(b, b+n, par(x, hi)) - lower_bound(b, b+n, par(x, lo));

            if( cnt*2 > m ) break;
        }
        if( iter == ITER ) printf( "ne\n" );
        else printf( "da %d\n", x );
    }
    return 0;
}
