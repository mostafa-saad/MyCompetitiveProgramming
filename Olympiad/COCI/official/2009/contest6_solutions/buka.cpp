#include <cstring>
#include <cstdio>

#define maxn 101

char a[maxn], op[2], b[maxn];
int la, lb;

int veci( int a, int b ) { return a>b? a: b; }
int manji( int a, int b ) { return a<b? a: b; }

void nule( int n ) {
	for( int i = 0; i < n; ++i ) printf( "0" );
}
	
int main(void) {
	scanf( "%s%s%s", a, op, b );
	la = strlen( a );
	lb = strlen( b );
	if( op[0] == '+' ) { // zbrajanje
		// poseban slucaj ako su isti brojevi, rezultat je 2 puta odgovarajuca potencija broja 10
		if( la == lb ) { printf( "2" ); nule( la-1 ); }
		else {
			printf( "1" ); nule( veci( la, lb ) - manji( la, lb ) - 1 ); // ako nisu isti rezultat je oblika 1, neke nule, 1, neke nule
			printf( "1" ); nule( manji( la, lb ) - 1 );
		}
	} else { // mnozenje
		printf( "1" );
		nule( la+lb-2 );
	}
	printf( "\n" );
	return 0;
}
