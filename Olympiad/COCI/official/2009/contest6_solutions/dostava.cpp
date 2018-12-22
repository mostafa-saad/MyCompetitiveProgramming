#include <cstring>
#include <cstdio>

#define maxr 2000
#define maxs 200
#define inf -1

int r, s, grid[maxr][maxs], sum[maxr][maxs]; // parcijalne sume za svaki redak
// G[i][j][k] = tezina brida od (j==0? lijevog: desnog) polja i-tog retka, u smjeru k (vodoravno,gore,dolje)
// dp[i][a][j][b] = najkraci put od i-tog retka do j-tog retka, s kojeg kraja retka odredjuju a i b
int G[maxr][2][3], dp[maxr][2][maxr][2];

void initsum() { // parcijalne sume
	for( int i = 0; i < r; ++i ) {
		sum[i][0] = grid[i][0];
		for( int j = 1; j < s; ++j ) sum[i][j] = sum[i][j-1] + grid[i][j];
	}
}

int fsum( int i, int l, int r ) { // suma u i-tom retku u intervalu [l,r>
	if( r == 0 ) return 0;
	if( l == 0 ) return sum[i][r-1];
	return sum[i][r-1] - sum[i][l-1];
}

void load() {
	scanf( "%d%d", &r, &s );
	for( int i = 0; i < r; ++i )
		for( int j = 0; j < s; ++j ) scanf( "%d", &grid[i][j] );
}

void initg() { // nagradi graf
	for( int i = 0; i < r; ++i ) {
		if( i == 0 ) G[i][0][0] = G[i][1][0] = inf;
		else { G[i][0][0] = grid[i-1][0]; G[i][1][0] = grid[i-1][s-1]; }
		
		if( i+1 == r ) G[i][0][2] = G[i][1][2] = inf;
		else { G[i][0][2] = grid[i+1][0]; G[i][1][2] = grid[i+1][s-1]; }
		
		G[i][0][1] = fsum( i, 1, s );
		G[i][1][1] = fsum( i, 0, s-1 );
	}
}

int manji( int a, int b ) {
	if( a == inf ) return b;
	if( b == inf ) return a;
	return a<b? a: b;
}

void initdp() { // dinamicki popuni tablicu
	memset( dp, inf, sizeof dp );
	
	for( int k = 0; k < 2; ++k ) {
		for( int i = 0; i < r; ++i ) {
			dp[i][k][i][k] = 0;
			
			int ll = 0, rr = 0;
			for( int j = i;; ++j) {
				dp[i][k][i][1-k] = manji( dp[i][k][i][1-k], ll+rr+G[j][k][1] );
				if( j+1 == r ) break;
				ll += G[j][k][2];
				rr += G[j+1][1-k][0];
			}
			
			ll = rr = 0;
			for( int j = i;; --j) {
				dp[i][k][i][1-k] = manji( dp[i][k][i][1-k], ll+rr+G[j][k][1] );
				if( j-1 < 0 ) break;
				ll += G[j][k][0];
				rr += G[j-1][1-k][2];
			}
		}
	}
	
	for( int t = 1; t < r; ++t ) {
		
		for( int i = 0; i < r-t; ++i ) {
			for( int k = 0; k < 2; ++k ) {
				dp[i][k][i+t][k] = manji( dp[i][k][i+t][k], dp[i+1][k][i+t][k] + G[i][k][2] );
				dp[i][k][i+t][k] = manji( dp[i][k][i+t][k], dp[i][k][i][1-k] + G[i][1-k][2] + dp[i+1][1-k][i+t][k] );
				
				dp[i][k][i+t][1-k] = manji( dp[i][k][i+t][1-k], G[i][k][2] + dp[i+1][k][i+t][1-k] );
				dp[i][k][i+t][1-k] = manji( dp[i][k][i+t][1-k], dp[i][k][i][1-k] + G[i][1-k][2] + dp[i+1][1-k][i+t][1-k] );
			}
		}
	
		for( int i = t; i < r; ++i ) {
			for( int k = 0; k < 2; ++k ) {
				dp[i][k][i-t][k] = manji( dp[i][k][i-t][k], dp[i-1][k][i-t][k] + G[i][k][0] );
				dp[i][k][i-t][k] = manji( dp[i][k][i-t][k], dp[i][k][i][1-k] + G[i][1-k][0] + dp[i-1][1-k][i-t][k] );
				
				dp[i][k][i-t][1-k] = manji( dp[i][k][i-t][1-k], G[i][k][0] + dp[i-1][k][i-t][1-k] );
				dp[i][k][i-t][1-k] = manji( dp[i][k][i-t][1-k], dp[i][k][i][1-k] + G[i][1-k][0] + dp[i-1][1-k][i-t][1-k] );
			}
		}
		
	}
}

// udaljenost od tocke do tocke, od cetiri moguca nacina putovanja odaberemo najbolji
int dist( int r1, int s1, int r2, int s2 ) {
	int d1 = fsum( r1, 0, s1 ) + dp[r1][0][r2][0] + fsum( r2, 1, s2+1 );
	int d2 = fsum( r1, 0, s1 ) + dp[r1][0][r2][1] + fsum( r2, s2, s-1 );
	
	int d3 = fsum( r1, s1+1, s ) + dp[r1][1][r2][0] + fsum( r2, 1, s2+1 );
	int d4 = fsum( r1, s1+1, s ) + dp[r1][1][r2][1] + fsum( r2, s2, s-1 );

	int ret = manji( manji( d1, d2 ), manji( d3, d4 ) );
	if( r1 == r2 ) {
		if( s1 < s2 ) ret = manji( ret, fsum( r1, s1+1, s2+1 ) );
		else ret = manji( ret, fsum( r1, s2, s1 ) );
	}
	
	return ret;
}

void solve() {
	long long sol = grid[0][0];
	int m, a, b, cr = 0, cs = 0;
	for( scanf( "%d", &m ); m; --m ) {
		scanf( "%d%d", &a, &b );
		
		sol += dist( cr, cs, a-1, b-1 );
		
		cr = a-1;
		cs = b-1;
	}
	
	printf( "%lld\n", sol );
}

int main(void) {
	load();
	initsum();
	initg();
	initdp();
	solve();
	return 0;
}
