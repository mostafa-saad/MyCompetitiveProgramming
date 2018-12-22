#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

const int MAXN = 100100;

int n;

struct planet {
    int x, y, z;
    int indeks;

    friend bool operator < ( const planet &A, const planet &B ) {
        if( A.x != B.x ) return A.x < B.x;
        if( A.y != B.y ) return A.y < B.y;
        if( A.z != B.z ) return A.z < B.z;
        return false;
    }

    friend int dist( const planet &A, const planet &B ) { 
        return min( abs( A.x-B.x ), min( abs( A.y-B.y ), abs( A.z-B.z ) ) );
    }
} P[ MAXN ], Org[ MAXN ]; // 3.2 MB

struct edge {
    int ind_a, ind_b;
    int cost;
    
    edge( int _a, int _b ) : ind_a( _a ), ind_b( _b ) {
        cost = dist( Org[ind_a], Org[ind_b] );
    }

    friend bool operator < ( const edge &A, const edge &B ) {
        return A.cost < B.cost;
    }
};

vector< edge > E; // 3.5 MB

bool x_cmpf( const planet &A, const planet &B ) { return A.x < B.x; }
bool y_cmpf( const planet &A, const planet &B ) { return A.y < B.y; }
bool z_cmpf( const planet &A, const planet &B ) { return A.z < B.z; }

int dad[ MAXN ];

int find_dad( int x ) {
    if( dad[x] == -1 ) return x;
    return dad[x] = find_dad( dad[x] );
}

int main( void )
{
    scanf( "%d", &n );
    E.reserve( 3*n + 100 );

    for( int i = 0; i < n; ++i ) {
        scanf( "%d %d %d", &P[i].x, &P[i].y, &P[i].z );
        P[i].indeks = i;
        Org[i] = P[i];
    }
    
    sort( P, P+n );
    for( int i = 1; i < n; ++i )
        if( !( P[i] < P[i-1] || P[i-1] < P[i] ) ) {
                puts( "GRESKA TESKA -> jednake vrijednosti!" );
                exit( 1 );
            }

    sort( P, P+n, x_cmpf );
    for( int i = 1; i < n; ++i )
        E.push_back( edge( P[i-1].indeks, P[i].indeks ) );

    sort( P, P+n, y_cmpf );
    for( int i = 1; i < n; ++i )
        E.push_back( edge( P[i-1].indeks, P[i].indeks ) );

    sort( P, P+n, z_cmpf );
    for( int i = 1; i < n; ++i )
        E.push_back( edge( P[i-1].indeks, P[i].indeks ) );

    sort( E.begin(), E.end() );

    long long sum = 0;
    memset( dad, -1, sizeof dad );

    for( vector< edge >::iterator it = E.begin(); it != E.end(); ++it ) {
        int A = find_dad( it->ind_a );
        int B = find_dad( it->ind_b );

        if( A != B ) {
            sum += it->cost;
            dad[A] = B;
        }
    }

    printf( "%lld\n", sum );

    return (0-0);
}
