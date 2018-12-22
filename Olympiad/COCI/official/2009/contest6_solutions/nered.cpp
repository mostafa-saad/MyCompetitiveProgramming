#include <cstdio>

#define maxn 101

int n, k, grid[maxn][maxn];

void load() {
	scanf( "%d%d", &n, &k );
	for( int i = 0; i < k; ++i ) {
		int r, s;
		scanf( "%d%d", &r, &s );
		grid[r-1][s-1] = 1;
	}	
}

int sum( int l, int r, int c ) { // suma u stupcu c, izmedju redaka l i r
	int ret = 0;
	for( int i = l; i < r; ++i ) ret += grid[i][c];
	return ret;
}
	
int solve() {
	int ret = n*n;
	for( int i = 0; i < n; ++i )
		for( int j = i+1; j <= n; ++j ) {
			if( k%(j-i) ) continue; // povrsina pravokutnika mora biti jednaka broju kockica, zato stranica mora biti djeljiva sa k
			int s = k/(j-i), rsum = 0;
			
			if( s > n ) continue;
			
			for( int q = 0; q < s; ++q ) rsum += sum( i, j, q );
			
			// secemo pravokutnik s lijeva na desno, cijelo vrijeme je gornja stranica redak i, a donja redak j
			// rsum je trenutan broj obuhvacenih kockica
			for( int q = s; q <= n; ++q ) { 
				if( ret > k-rsum ) ret = k-rsum;
				
				rsum -= sum( i, j, q-s ); // micemo najljeviji stupac pravokutnika
				rsum += sum( i, j, q );   // i dodajemo novi
			}
		}
	return ret;
}

int main(void) {
	load();
	printf( "%d\n", solve() );
	return 0;
}
