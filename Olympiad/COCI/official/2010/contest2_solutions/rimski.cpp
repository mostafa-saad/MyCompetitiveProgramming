#include <cstdio>
#include <cstdlib>

int p[ 255 ] = { 0 };
char st[ 35 ];

int main( void ) {
	scanf( "%s", st );
	for( int i = 0; st[ i ] != 0; ++i )
		p[ ( int )st[ i ] ]++;
	
	if( p[ 'C' ] == 1 ) { printf( "XC" ); p[ 'C' ]--; p[ 'X' ]--; }
	if( p[ 'L' ] == 1 ) {
		if( p[ 'X' ] == 1 || ( p[ 'X' ] == 2 && p[ 'I' ] == 1 && p[ 'V' ] == 0 ) )
			{ printf( "X" ); p[ 'X' ]--; }
		printf( "L" ); p[ 'L' ]--;
	}	
	
	while( p[ 'X' ] > 1 ) { printf( "X" ); p[ 'X' ]--; }
	if( p[ 'X' ] == 1 && p[ 'V' ] == 0 && p[ 'I' ] == 1 )
		{ printf( "IX" ); p[ 'X' ]--; p[ 'I' ]--; }
	if( p[ 'X' ] == 1 ) { printf( "X" ); p[ 'X' ]--; }
	
	if( p[ 'I' ] == 1 && p[ 'V' ] == 1 ) { printf( "I" ); p[ 'I' ]--; }
	if( p[ 'V' ] == 1 ) { printf( "V" ); p[ 'V' ]--; }
	
	
	while( p[ 'I' ] > 0 ) { printf( "I" ); p[ 'I' ]--; }
	
	printf( "\n" );
	return( 0 );
}
