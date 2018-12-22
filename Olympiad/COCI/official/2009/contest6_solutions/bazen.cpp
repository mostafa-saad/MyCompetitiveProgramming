#include <cstdio>

struct pt {
	double x, y;
	pt() {}
	pt( double a, double b ) { x=a; y=b; }
};

pt solve( pt a ) {
	// p je dvostruka povrsina polovice trokuta
	// stranica promatranog trokuta * njegova visina = p
	// rjesavamo svaki od sest slucajeva
	
	double p = 250*250/2;
	
	if( a.x == 0 )
		if( a.y < 125 ) return pt( p/(250-a.y), 250-p/(250-a.y) );
		else return pt( p/a.y, 0 );
		
	if( a.y == 0 )
		if( a.x < 125 ) return pt( 250-p/(250-a.x), p/(250-a.x) );
		else return pt( 0, p/a.x );
		
	if( a.x > 125 ) return pt( 0, 250-p/a.x );
	else return pt( 250-p/a.y, 0 );
}

int main(void) {
	pt a, b;
	scanf( "%lf%lf", &a.x, &a.y );
	b = solve( a );
	printf( "%.2lf %.2lf\n", b.x, b.y );
	return 0;
}
