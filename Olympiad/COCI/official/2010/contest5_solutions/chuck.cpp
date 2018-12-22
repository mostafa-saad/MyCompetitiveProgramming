#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

#define Row first
#define Col second

using namespace std;
vector< string > rez;
vector< pair< int, int > > koord;

int R, S, mat[ 105 ][ 105 ], niz[ 10005 ];
int recon[ 20005 ], moguce[ 20005 ] = { 1 };
int sumuk[ 20005 ] = { 0 }, negativnih = 0;
int por[ 10005 ], tmp[ 105 ], cnt = 0;
char tmpbuff[ 105 ], ozn[ 105 ][ 105 ];


void rotaterow( int row, int K ) {
	for( int i = 0; i < S; ++i )
		tmp[ ( i + K ) % S ] = mat[ row ][ i ];
	for( int i = 0; i < S; ++i )
		mat[ row ][ i ] = tmp[ i ];
	for( int i = 0; i < ( int )koord.size(); ++i )
		if( koord[ i ].Row == row )
			koord[ i ].Col = ( koord[ i ].Col + K ) % S;
	
	sprintf( tmpbuff, "rotR %d %d", row + 1, K );
	rez.push_back( string( tmpbuff ) );
}

void rotatecol( int col, int K ) {
	for( int i = 0; i < R; ++i )
		tmp[ ( i + K ) % R ] = mat[ i ][ col ];
	for( int i = 0; i < R; ++i )
		mat[ i ][ col ] = tmp[ i ];
	for( int i = 0; i < ( int )koord.size(); ++i )
		if( koord[ i ].Col == col )
			koord[ i ].Row = ( koord[ i ].Row + K ) % R;
	
	sprintf( tmpbuff, "rotS %d %d", col + 1, K );
	rez.push_back( string( tmpbuff ) );
}

void changerow( int row ) {
	for( int i = 0; i < S; ++i )
		mat[ row ][ i ] = -mat[ row ][ i ];
	
	sprintf( tmpbuff, "negR %d", row + 1 );
	rez.push_back( string( tmpbuff ) );
}

void changecol( int col ) {
	for( int i = 0; i < R; ++i )
		mat[ i ][ col ] = -mat[ i ][ col ];
	
	sprintf( tmpbuff, "negS %d", col + 1 );
	rez.push_back( string( tmpbuff ) );
}

int suma( int a, int b ) {
	if( a > b ) return( 0 );
	return( sumuk[ b ] - ( a == 0 ? 0 : sumuk[ a-1 ] ) );
}

int evalpod( int X ) {
	return( suma( X, R * S - 1 ) - suma( 0, X - 1 ) );
}

pair< int, int > pronadji( int X ) {
	for( int i = 0; i < R; ++i )
		for( int j = 0; j < S; ++j )
			if( !ozn[ i ][ j ]  &&  mat[ i ][ j ] == X ) {
				ozn[ i ][ j ] = 1;
				return make_pair( i, j );
			}
	
	return make_pair( -1, -1 );
}

void sredi_stupac( void ) {
	int len = ( int )koord.size();
	for( int i = 0; i < len; ++i ) {
		int razl = i - koord[ i ].Row;
		if( razl < 0 ) razl += R;
		
		if( koord[ i ].Col == 0 ) rotaterow( koord[ i ].Row, 1 );
		if( koord[ i ].Row != i ) rotatecol( koord[ i ].Col, razl );
		rotaterow( koord[ i ].Row, S - koord[ i ].Col );
	}
}

void sredi_redak( void ) {
	int len = ( int )koord.size();
	for( int i = 0; i < len; ++i ) {
		int razl = i - koord[ i ].Col;
		if( razl < 0 ) razl += S;
		
		if( koord[ i ].Row == 0 ) rotatecol( koord[ i ].Col, 1 );
		if( koord[ i ].Col != i ) rotaterow( koord[ i ].Row, razl );
		rotatecol( koord[ i ].Col, R - koord[ i ].Row );
	}
}

int main( void ) {
	scanf( "%d %d", &R, &S );
	for( int i = 0; i < R; ++i )
		for( int j = 0; j < S; ++j ) {
			scanf( "%d", &mat[ i ][ j ] );
			niz[ S * i + j ] = mat[ i ][ j ];
		}
	
	sort( niz, niz + R * S );
	for( int i = 0; i < R * S; ++i ) {
		negativnih += ( niz[ i ] < 0 );
		sumuk[ i ] = ( i > 0 ? sumuk[ i-1 ] : 0 ) + niz[ i ];
		
		if( !moguce[ i ] ) continue;
		moguce[ i + R ] = 1;
		moguce[ i + S ] = 1;
		recon[ i + R ] = i;
		recon[ i + S ] = i;
	}
	
	int X, A = -1, B = -1;
	for( int i = 0; i <= R * S; ++i ) {
		if( !moguce[ i ] ) continue;
		if( i <= negativnih ) A = i;
		if( i >= negativnih && B == -1 )
			B = i;
	}
	
	if( A == -1 ) X = B; else if( B == -1 ) X = A;
	else X = ( evalpod( A ) > evalpod( B ) ? A : B );
	
	int prez = evalpod( X );
	while( X != 0 ) {
		por[ cnt++ ] = X;
		X = recon[ X ];
	}
	
	por[ cnt++ ] = 0;
	reverse( por, por + cnt );
	
	for( int i = 0; i < cnt-1; ++i ) {
		memset( ozn, 0, sizeof( ozn ) );
		koord.clear();
		
		for( int j = por[ i ]; j < por[ i + 1 ]; ++j )
			koord.push_back( pronadji( niz[ j ] ) );
		
		if( por[ i + 1 ] - por[ i ] == R ) {
			sredi_stupac();
			changecol( 0 );
		} else {
			sredi_redak();
			changerow( 0 );
		}
	}
	
	printf( "%d %d\n", prez, ( int )rez.size() );
	for( int i = 0; i < ( int )rez.size(); ++i )
		printf( "%s\n", rez[ i ].c_str() );
	
	return( 0 );
}
