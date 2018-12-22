#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 100100;
const int MAXE = 200100 + 2*MAXN;

int n, e;
int A[ MAXE ], B[ MAXE ];
char E_ziv[ MAXE ];
char pobojaj[ MAXE ];

char posjetio[ MAXN ];
char bio[ MAXN ][ 2 ];

vector< int > E[ MAXN ];

int e_tmp = 0;
int n_tmp = 0;

int last_boja = 0;

struct stack_frame {
    int x;
    int iter;
    int e_indeks;

    stack_frame() {}
    stack_frame( int _x, int _iter, int _e ) : x( _x ), iter( _iter ), e_indeks( _e ) {}
};

stack< stack_frame > Stk;

void euler_iterativni( int Pocetak ) 
{
    for( Stk.push( stack_frame( Pocetak, 0, -1 ) ); !Stk.empty(); ) {
        stack_frame P = Stk.top(); Stk.pop();
        int x = P.x;

        posjetio[ x ] = true;

        if( P.e_indeks != -1 ) {
            bio[ A[ P.e_indeks ] ][ last_boja ] = true;
            bio[ B[ P.e_indeks ] ][ last_boja ] = true;
            pobojaj[ P.e_indeks ] = last_boja;
            last_boja ^= 1;
        }

        for( ; !E[x].empty(); ) {
            int ind = E[x].back();
            if( E_ziv[ ind ] == false ) { E[x].pop_back(); continue; }

            E_ziv[ ind ] = false;
            E[x].pop_back();

            int y = A[ind] + B[ind] - x;

            Stk.push( stack_frame( x, -1, ind ) );
            Stk.push( stack_frame( y, -1, -1 ) );
            
            break;
        }
    }
}

int OrgSize[ MAXN ];

int main( void )
{
    memset( bio, 0, sizeof bio );
    memset( E_ziv, 1, sizeof bio );
    memset( posjetio, 0, sizeof posjetio );

    scanf( "%d %d", &n, &e );

    for( int i = 0; i < e; ++i ) {
        int a, b; scanf( "%d %d", &a, &b ); --a, --b;
        A[i] = a; B[i] = b;
        E[a].push_back( i );
        E[b].push_back( i );
    }

    for( int i = 0; i < n; ++i )
        OrgSize[i] = ( int )E[i].size();

    n_tmp = n+1;
    e_tmp = e;

    for( int i = 0; i < n; ++i ) {
        if( (( int )E[i].size()) % 2 == 1 ) {
            A[ e_tmp ] = i; B[ e_tmp ] = n;
            E[ i ].push_back( e_tmp );
            E[ n ].push_back( e_tmp );
            ++e_tmp;
        }
    }   

    for( int i = n; i >= 0; --i ) {
        if( posjetio[i] == true ) continue;
        if( i == n || int(E[i].size()) >= 4 ) {
            euler_iterativni( i );
        }
    }

    for( int i = 0; i < n; ++i ) {
        if( posjetio[i] == true ) continue;
        euler_iterativni( i );
    }

    int ok = true;
    for( int i = 0; i < n; ++i )
        if( OrgSize[i] > 0 && bio[i][0] + bio[i][1] != 2 )
            ok = false;

    if( ok ) 
        for( int i = 0; i < e; ++i )
            printf( "%d\n", pobojaj[i] + 1 );        
    else 
        printf( "0\n" );

    return (0-0);
}
