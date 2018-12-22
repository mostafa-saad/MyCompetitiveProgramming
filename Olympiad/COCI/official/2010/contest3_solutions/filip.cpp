#include <cstdio>
#include <cstdlib>

int main( void ) {
	int a, b; scanf( "%d %d", &a, &b );
	a = ( a % 10 ) * 100 + ( a / 10 % 10 ) * 10 + ( a / 100 );
	b = ( b % 10 ) * 100 + ( b / 10 % 10 ) * 10 + ( b / 100 );
	printf( "%d\n", a > b ? a : b );
	return( 0 );
}
