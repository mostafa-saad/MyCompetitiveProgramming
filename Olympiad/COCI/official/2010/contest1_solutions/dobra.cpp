#include <cstdio>
#include <cstdlib>

char rijec[ 105 ];
int sluchaj[ 105 ] = { 0 };
int br[] = { 0, 5, 1, 20 };

int samoglasnik( char ch ) {
	return( ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' );
}

int uzastop( void ) {
	for( int i = 0; rijec[ i+1 ] != 0  &&  rijec[ i+2 ] != 0; ++i ) {
		int tip1 = ( samoglasnik( rijec[ i+0 ] ) || sluchaj[ i+0 ] == 1 );
		int tip2 = ( samoglasnik( rijec[ i+1 ] ) || sluchaj[ i+1 ] == 1 );
		int tip3 = ( samoglasnik( rijec[ i+2 ] ) || sluchaj[ i+2 ] == 1 );
		if( tip1 == tip2 && tip2 == tip3 ) return( 1 );
	}
	
	return( 0 );
}

long long konstruiraj( int poz, int L ) {
	if( rijec[ poz ] == 0 )
		return( L  &&  !uzastop() );
	
	if( rijec[ poz ] >= 'A' && rijec[ poz ] <= 'Z' )
		return( konstruiraj( poz + 1, L | ( rijec[ poz ] == 'L' ) ) );
	
	long long komb = 0ll;
	for( int i = 1; i <= 3; ++i ) {
		sluchaj[ poz ] = i;
		komb += br[ i ] * konstruiraj( poz + 1, L | ( i == 2 ) );
	}
	
	return( komb );
}

int main( void ) {
	scanf( "%s", rijec );
	printf( "%lld\n", konstruiraj( 0, 0 ) );
	return( 0 );
}
