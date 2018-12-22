/*
  Sluzbeno rjesenje zadatka XOR, trebalo bi dobiti sve bodove.
  Autor: Goran Zuzic
*/

#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

const int MAXN = 16;

int n;
int X[ MAXN ], Y[ MAXN ], R[ MAXN ], C[ MAXN ];

long long suma_A = 0;

void recurse( int work, int x, int y, int c, int kol, int sign )
{
    if( x+y >= c ) return ;

    if( work == n ) {
        if( kol == 0 ) return ;
        long long r = c-x-y;
        suma_A += sign*(1LL<<(kol-1))*r*r;
        return ;
    }

    recurse( work+1, x, y, c, kol, sign );
    recurse( work+1, max( x, X[work] ), max( y, Y[work] ), min( c, C[work] ), kol+1, -sign );
}

int main( void )
{ 
    scanf( "%d", &n );

    for( int i = 0; i < n; ++i ) {
        scanf( "%d %d %d", X+i, Y+i, R+i );
        C[i] = X[i]+Y[i]+R[i];
    }

    recurse( 0, 0, 0, 1000000000, 0, -1 );
    printf( "%lld.%lld\n", suma_A/2, suma_A%2 == 0 ? 0LL : 5LL );

    return (0-0);
}
