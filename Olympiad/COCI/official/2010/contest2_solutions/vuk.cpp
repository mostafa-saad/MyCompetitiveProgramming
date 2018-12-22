#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
queue< pair< pair< int, int >, int > > Q;
priority_queue < pair< int, pair< int, int > > > PQ;
pair< int, int > V, J;

int dr[ 4 ][ 2 ] = { { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1 } };
int n, m, udalj[ 505 ][ 505 ], best[ 505 ][ 505 ];
char mat[ 505 ][ 505 ];

int main( void ) {
	scanf( "%d %d", &n, &m );
	for( int i = 0; i < n; ++i )
		scanf( "%s", mat[ i ] );
	
	memset( best, -1, sizeof( best ) );
	memset( udalj, -1, sizeof( udalj ) );
	for( int i = 0; i < n; ++i )
		for( int j = 0; j < m; ++j ) {
			if( mat[ i ][ j ] == '+' ) {
				udalj[ i ][ j ] = 0;
				Q.push( make_pair( make_pair( i, j ), 0 ) );
			}
			
			if( mat[ i ][ j ] == 'V' ) V = make_pair( i, j );
			if( mat[ i ][ j ] == 'J' ) J = make_pair( i, j );
		}
	
	while( !Q.empty() ) {
		int trow = Q.front().first.first;
		int tcol = Q.front().first.second;
		int level = Q.front().second; Q.pop();
		
		for( int i = 0; i < 4; ++i ) {
			int nrow = trow + dr[ i ][ 0 ];
			int ncol = tcol + dr[ i ][ 1 ];
			
			if( nrow < 0 || nrow >= n ) continue;
			if( ncol < 0 || ncol >= m ) continue;
			if( udalj[ nrow ][ ncol ] > -1 ) continue;
			
			udalj[ nrow ][ ncol ] = level + 1;
			Q.push( make_pair( make_pair( nrow, ncol ), level + 1 ) );
		}
	}
	
	best[ V.first ][ V.second ] = udalj[ V.first ][ V.second ];
	PQ.push( make_pair( best[ V.first ][ V.second ], V ) );
	
	while( !PQ.empty() ) {
		int trow = PQ.top().second.first;
		int tcol = PQ.top().second.second;
		int D = PQ.top().first; PQ.pop();
		
		for( int i = 0; i < 4; ++i ) {
			int nrow = trow + dr[ i ][ 0 ];
			int ncol = tcol + dr[ i ][ 1 ];
			
			if( nrow < 0 || nrow >= n ) continue;
			if( ncol < 0 || ncol >= m ) continue;
			if( best[ nrow ][ ncol ] > -1 ) continue;
			
			best[ nrow ][ ncol ] = min( D, udalj[ nrow ][ ncol ] );
			PQ.push( make_pair( best[ nrow ][ ncol ], make_pair( nrow, ncol ) ) );
		}
	}
	
	printf( "%d\n", best[ J.first ][ J.second ] );
	return( 0 );
}
