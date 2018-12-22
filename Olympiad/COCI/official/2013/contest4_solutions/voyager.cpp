#include <cstdio>
#include <cstring>
using namespace std;

const int N = 502;
const int inf = 0x3f3f3f3f;

int n, m;
int r, s;
int sr, ss, di, mx, smjer;
int bio[N][N][4];
char mat[N][N];

int dr[] = { -1, 0, 1, 0 };
int ds[] = { 0, 1, 0, -1 };
char out[] = { 'U', 'R', 'D', 'L' };

int main( void ) {
	scanf( "%d %d", &n, &m );
	for( int i = 0; i < n; ++i ) scanf( "%s", mat[i] ); 
	
	scanf( "%d %d", &r, &s );
	--r; --s;
	
	for( int i = 0; i < 4; ++i ) {
		di = i;
		sr = r; 
		ss = s;
		
		int uk = 0;
		while( 1 ) {
			if( sr < 0 || ss < 0 || sr >= n || ss >= m ) break;
			if( mat[sr][ss] == 'C' ) break;
			
			if( bio[sr][ss][di] ) {
				uk = inf;
				break;
			}
			bio[sr][ss][di] = 1;
			
			if( mat[sr][ss] == '/' ) {
				if( di == 0 || di == 2 ) ++di;
				else --di; 
			}
			if( mat[sr][ss] == '\\' ) {
				if( di == 0 || di == 2 ) --di;
				else ++di;
				
				di = ( di+4 )&3;
			}
			
			++uk;
			sr += dr[di];
			ss += ds[di];
		}
		
		if( uk > mx ) {
			mx = uk;
			smjer = i;
		}
		memset( bio, 0, sizeof bio );
	}
	
	
	printf( "%c ", out[smjer] );
	if( mx == inf ) printf( "Voyager\n" );
	else printf( "%d\n", mx );
	
	return 0;
}
