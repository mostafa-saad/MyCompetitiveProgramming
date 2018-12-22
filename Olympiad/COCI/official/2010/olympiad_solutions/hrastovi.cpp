#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

struct coords {
    int x, y;
    coords( int X, int Y ) { x = X; y = Y; }
};
bool cmpByX( const coords &A, const coords &B ) {
    if( A.x != B.x ) return A.x < B.x; else return A.y < B.y;
}
bool cmpByY( const coords &A, const coords &B ) {
    if( A.y != B.y ) return A.y < B.y; else return A.x < B.x;
}
typedef bool(*cmpFunction)( const coords &, const coords & );

int segment( const vector<coords> &sorted, cmpFunction cmp, const coords &A, const coords &B ) {
    return
        upper_bound( sorted.begin(), sorted.end(), B, cmp ) -
        lower_bound( sorted.begin(), sorted.end(), A, cmp );
}

int main( void ) {
    int n;
    scanf( "%d", &n );
    vector<coords> sortByX, sortByY;
    for( int i = 0; i < n; ++i ) {
        int x, y;
        scanf( "%d%d", &x, &y );
        sortByX.push_back( coords(x, y) );
        sortByY.push_back( coords(x, y) );
    }

    sort( sortByX.begin(), sortByX.end(), cmpByX );
    sort( sortByY.begin(), sortByY.end(), cmpByY );

    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) {
        int x1, y1, x2, y2;
        scanf( "%d%d%d%d", &x1, &y1, &x2, &y2 );

        int ret = 0;
        ret += segment( sortByX, cmpByX, coords(x1, y1), coords(x1, y2) );
        ret += segment( sortByX, cmpByX, coords(x2, y1), coords(x2, y2) );
        ret += segment( sortByY, cmpByY, coords(x1+1, y1), coords(x2-1, y1) );
        ret += segment( sortByY, cmpByY, coords(x1+1, y2), coords(x2-1, y2) );
        printf( "%d\n", ret );
   }

   return 0;
}
