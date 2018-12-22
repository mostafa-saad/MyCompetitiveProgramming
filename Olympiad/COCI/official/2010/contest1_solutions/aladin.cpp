/*
  Sluzbeno rjesenje zadatka Aladin.
  Slozenost: O(q lg^2 n)

  Autor: Goran Zuzic
*/

#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

const int MAXNODE = 2*132072;
typedef long long llint;

int n, q;

llint gcd( llint a, llint b ) { return b ? gcd( b, a%b ) : a; }
llint calc( llint a, llint b, llint n ) {
    llint x = a / b;
    llint sum = x*n*(n+1) / 2; a %= b;

    if( a == 0 || b == 0 ) return sum;

    llint diag = n/b;
    llint zadnji = a*n/b;

    return sum + n*zadnji - calc( b, a, zadnji ) + diag;
}

inline llint solve( llint a, llint b, llint n ) { 
    if( n < 1 ) return 0;
    llint g = gcd( a, b ); 
    return n*(n+1)/2*a - b*calc( a/g, b/g, n );
}

int _L, _R;
int _A, _B;

struct node {
    int a, b, poc;
    int size;

    llint suma;
    node() { suma = 0; b = 0; }

    void update( node &A, node &B ) { suma = A.suma + B.suma; }

    void set_it( int aa, int bb, int pocc ) {
        a = aa; b = bb; poc = pocc;
        suma = solve( a, b, poc+size-1 ) - solve( a, b, poc-1 );
    }

    void spread( node &A, node &B ) {
        if( b != 0 ) {
            A.set_it( a, b, poc );
            B.set_it( a, b, poc+A.size );
        }
        b = 0;
    }

} h[ MAXNODE ];

vector< int > Rez;

struct tournament {
    void init( int x, int l, int r ) {
        h[x].size = Rez[r] - Rez[l];
        if( l+1 == r ) return ;

        int mid = ( l + r ) / 2;
        init( 2*x, l, mid );
        init( 2*x+1, mid, r );
    }

    llint query( int x, int l, int r ) {
        if( _R <= l || r <= _L ) return 0;
        if( _L <= l && r <= _R ) return h[x].suma;

        h[x].spread( h[2*x], h[2*x+1] );

        int mid = ( l + r ) / 2;
        return query( 2*x, l, mid )
            +  query( 2*x+1, mid, r );
    }

    void update( int x, int l, int r ) {
        if( _R <= l || r <= _L ) return ;
        if( _L <= l && r <= _R ) { 
            h[x].set_it( _A, _B, Rez[l]-Rez[_L]+1 );
            return ;
        }

        h[x].spread( h[2*x], h[2*x+1] );

        int mid = ( l + r ) / 2;
        update( 2*x, l, mid );
        update( 2*x+1, mid, r );
        h[x].update( h[2*x], h[2*x+1] );
    }
} T;

const int MAXQ = 100100;

struct query {
    int type;
    int l, r;
    int a, b;
    
    query() {}
    query( int _type, int _l, int _r, int _a, int _b ) : type( _type ), l( _l ), r( _r ), a( _a ), b( _b ) {}
} Q[ MAXQ ];

int main( void )
{
    scanf( "%d %d", &n, &q );
    Rez.reserve( 2*q + 100 );

    Rez.push_back( 0 );
    Rez.push_back( n );

    for( int counter = 0; counter < q; ++counter ) {
        int type, l, r; scanf( "%d %d %d", &type, &l, &r ); _L = --l; _R = --r;
        Rez.push_back( l );
        Rez.push_back( r+1 );

        if( type == 1 ) {
            scanf( "%d %d", &_A, &_B ); _A %= _B;
            Q[counter] = query( type, l, r, _A, _B );
        }
        else {
            Q[counter] = query( type, l, r, 0, 0 );
        }
    }

    sort( Rez.begin(), Rez.end() );
    T.init( 1, 0, ( int )Rez.size()-1 );

    for( int counter = 0; counter < q; ++counter ) {
        _L = lower_bound( Rez.begin(), Rez.end(), Q[counter].l ) - Rez.begin();
        _R = upper_bound( Rez.begin(), Rez.end(), Q[counter].r ) - Rez.begin();

        _A = Q[counter].a;
        _B = Q[counter].b;

        if( Q[counter].type == 1 ) {
            T.update( 1, 0, ( int )Rez.size() - 1 );
        }
        else {
            printf( "%lld\n", T.query( 1, 0, ( int )Rez.size() - 1 ) );
        }
    }

    return (0-0);
}
