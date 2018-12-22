#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>

#define maxn 100
#define maxd 1000
#define maxf (maxn+maxd+2)
#define source 0
#define sink 1

using namespace std;

int n, m, d, slicice[maxn], ducan[maxd][2];
int C[maxf][maxf], dad[maxf], flow[maxf];
vector< int > next[maxf];

void load() {
	scanf( "%d%d", &n, &m );
	for( int i = 0; i < n; ++i ) {
		scanf( "%d", &slicice[i] );
		d += slicice[i];
	} d /= 2;
	for( int i = 0; i < m; ++i ) scanf( "%d%d", &ducan[i][0], &ducan[i][1] );
}

void spoji( int a, int b, int c ) {
	C[a][b] = c;
	next[a].push_back( b );
	next[b].push_back( a );
}

void build_graph() {
	for( int i = 0; i < d; ++i ) spoji( source, 2+i, 2 );
	
	for( int i = 0; i < m; ++i ) {
		spoji( 2+i, 1+d+ducan[i][0], 2 );
		spoji( 2+i, 1+d+ducan[i][1], 2 );
	}
	
	for( int i = m; i < d; ++i )
		for( int j = 0; j < n; ++j ) spoji( 2+i, 2+d+j, 2 );
	
	for( int i = 0; i < n; ++i ) spoji( 2+d+i, sink, slicice[i] );
}

int aug_flow() {
	memset( dad, -1, sizeof dad );
	memset( flow, 0, sizeof flow );

	queue< int > Q;	
	
	flow[source] = maxf;
	for( Q.push( source ); !Q.empty(); Q.pop() ) {
		int curr = Q.front();
		
		if( curr == sink ) return 1;
		
		for( int i = 0; i < next[curr].size(); ++i ) {
			int t = next[curr][i];
			if( C[ curr ][ t ] == 0 || dad[t] != -1 ) continue;
			
			dad[t] = curr;
			flow[t] = min( flow[curr], C[ curr ][ t ] );
			Q.push( t );
		}
	}
	
	return 0;
}

void max_flow() {
	while( aug_flow() ) {
		for( int t = sink; t != source; t = dad[t] ) {
			C[ dad[t] ][ t ] -= flow[sink];
			C[ t ][ dad[t] ] += flow[sink];
		}
	}
}

void output() {
	printf( "%d\n", d );
	for( int i = 0; i < m; ++i ) printf( "%d %d %d\n", ducan[i][0], ducan[i][1], C[ 1+d+ducan[i][0] ][ 2+i ] );
	
	for( int i = m; i < d; ++i ) {
		vector< int > tmp;
		for( int j = 0; j < n; ++j )
			if( C[ 2+d+j ][ 2+i ] ) tmp.push_back( j+1 );
			
		if( tmp.size() == 2 ) printf( "%d %d 1\n", tmp[0], tmp[1] );
		else printf( "%d %d 2\n", tmp[0], tmp[0]==1? 2: 1 );
	}
}

int main(void) {
	load();
	build_graph();
	max_flow();
	output();
	return 0;
}
