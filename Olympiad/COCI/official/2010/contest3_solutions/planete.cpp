/*
  Sluzbeno rjesenje zadatka Planete. Trebalo bi dobiti 100% bodova. 
  Slozenost algoritma: O( N^2*F )
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

const int MAXN = 210;
const int MAXF = 210;

int N, F;
int DuM[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int Init[ MAXN ][ MAXF+1 ];
int Mat[ MAXN ][ MAXF+1 ];

inline int get_day() 
{
    int d, m; scanf( "%d %d", &d, &m ); --d, --m;

    for( int i = 0; i < m; ++i )
        d += DuM[i];

    return d;
}

int Sol5[ MAXF ];
int Sol73[ MAXF ];

int Inverz[ 100 ];
int superOk = true;

void gauss_solve( int p, int *Sol )
{
    for( int i = 0; i < N; ++i )
        for( int j = 0; j <= F; ++j )
            Mat[i][j] = Init[i][j] % p;

    Inverz[0] = 0;

    for( int i = 1; i < p; ++i )
        for( int j = 1; j < p; ++j )
            if( (i*j)%p == 1 )
                Inverz[i] = j;

    int R = 0;

    for( int s = 0; s < F; ++s ) {
        int indeks = -1;

        for( int i = R; indeks == -1 && i < N; ++i )
            if( Mat[i][s] != 0 )
                indeks = i;

        if( indeks == -1 ) continue;
        if( R != indeks )
            for( int i = 0; i <= F; ++i )
                swap( Mat[R][i], Mat[indeks][i] );

        int mnozi = Inverz[ Mat[R][s] ];
        for( int i = 0; i <= F; ++i )
            Mat[R][i] = ( Mat[R][i]*mnozi ) % p;

        for( int i = 0; i < N; ++i )
            if( i != R ) {
                int coef = Mat[i][s];

                for( int j = 0; j <= F; ++j ) {
                    Mat[i][j] -= coef * Mat[R][j];
                    Mat[i][j] %= p; if( Mat[i][j] < 0 ) Mat[i][j] += p;
                }
            }

        ++R;
    }

    for( int i = 0; i < N; ++i ) {
        int first = -1;

        for( int j = 0; j < F; ++j )
            if( Mat[i][j] != 0 ) {
                first = j;
                break;
            }

        if( first == -1 ) {
            if( Mat[i][F] != 0 ) { superOk = false; return ; }            
            continue;
        }

        Sol[ first ] = Mat[i][F];
    }
}

int main( void )
{
    scanf( "%d %d", &N, &F );

    for( int i = 0; i < N; ++i ) {
        int a = get_day();
        int b = get_day();

        for( int j = 0; j < F; ++j )
            scanf( "%d", Init[i] + j );

        Init[i][F] = ((b-a)%365+365)%365;
    }

    gauss_solve( 5, Sol5 );
    gauss_solve( 73, Sol73 );

    if( !superOk ) { printf( "-1\n" ); return (0-0); }

    for( int i = 0; i < F; ++i ) {
        int tmp = ( 146*Sol5[i] + 220*Sol73[i] ) % 365;
        if( tmp == 0 ) tmp = 365;
        printf( "%d\n", tmp );
    }

    return (0-0);
}
