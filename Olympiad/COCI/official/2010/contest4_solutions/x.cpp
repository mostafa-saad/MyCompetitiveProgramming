#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXVAL = 1000000;

using namespace std;
int pon[ MAXVAL + 5 ], n, niz[ 105 ];
int A[ MAXVAL ], counter = 0;

void dodajfaktore( int x ) {
	int tr = 2, org = x;
	
	while( tr * tr <= org ) {
		while( x % tr == 0 ) {
			pon[ tr ]++;
			x /= tr;
		}
		
		++tr;
	}
	
	if( x > 1 ) pon[ x ]++;
}

int solve( void ) {
	int rez = 1; counter = 0;
	
	for( int i = 2; i <= MAXVAL; ++i ) {
		pon[ i ] /= n;
		for( int j = 0; j < pon[ i ]; ++j )
			rez *= i;
		
		if( pon[ i ] > 0 ) A[ counter++ ] = i;
	}
	
	return( rez );
}

int calcprom( int x ) {
	int prom = 0;
	
	for( int i = 0; i < counter; ++i ) {
		 int br = A[ i ], tr = pon[ br ];
		 for( ; x % br == 0; --tr, x /= br );
		 if( tr > 0 ) prom += tr;
	}
	
	return( prom );
}

int main( void ) {
	memset( pon, 0, sizeof( pon ) );
	
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i ) {
		scanf( "%d", &niz[ i ] );
		dodajfaktore( niz[ i ] );
	}
	
	int rez = solve(), prom = 0;
	for( int i = 0; i < n; ++i )
		prom += calcprom( niz[ i ] );
	
	printf( "%d %d\n", rez, prom );
	return( 0 );
}
