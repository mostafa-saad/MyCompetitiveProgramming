#include <cstdio>
using namespace std;

const int N = 2000;

int l, n;
int a, b;
int mxm, mxd, idm, idd;
int bio[N];

int max( int a, int b ) {
	if( a > b ) return a;
	return b;
}

int main( void ) {
	scanf( "%d", &l );
	scanf( "%d", &n );
	
	for( int i = 0; i < n; ++i ) {
		scanf( "%d %d", &a, &b );
		
		if( b-a+1 > mxm ) {
			mxm = b-a+1;
			idm = i;
		}
		
		int uk = 0;
		for( int j = a; j <= b; ++j ) {
			if( bio[j] ) continue;
			++uk;
			bio[j] = 1;
		} 
		
		if( uk > mxd ) {
			mxd = uk;
			idd = i;
		}
	}
	
	printf( "%d\n", idm+1 );
	printf( "%d\n", idd+1 );
	
	return 0;
}
