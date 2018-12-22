/*
  Tocno rjesenje zadatka Pasijans. Trebao bi dobiti sve bodove.
  Autor: Goran Zuzic
*/

#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
#include <vector>
#include <string>

using namespace std;

typedef long long llint;

const int MAXN = 1024;

int n;
int L[ MAXN ];
int A[ MAXN ][ MAXN ]; // 4 MB

int rank[ MAXN ][ MAXN ][ 10 ]; // 40 MB

struct state {
    int x, poc;
    llint rr;

    state() {}
    state( int _x, int _poc, llint _rr ) : x( _x ), poc( _poc ), rr( _rr ) {}

    friend bool operator < ( const state &A, const state &B ) {
        return A.rr < B.rr;
    }
} V[ MAXN*MAXN ]; // 16MB

int v_cnt = 0;
int Poc[ MAXN ];

struct pq_cmpf {
    bool operator () ( int a, int b ) const {
        int poca = Poc[a];
        int pocb = Poc[b];

        for( int bit = 9; bit >= 0; --bit ) {
            if( poca+(1<<bit) > L[a] || pocb+(1<<bit) > L[b] ) continue;

            if( rank[a][poca][bit] != rank[b][pocb][bit] ) 
                return rank[a][poca][bit] < rank[b][pocb][bit];
            else {
                poca += (1<<bit);
                pocb += (1<<bit);
            }
        }

        if( L[a]-poca != L[b]-pocb ) return L[a]-poca > L[b]-pocb;
        return a < b;
    }
};

set< int, pq_cmpf > pq;

int main( void )
{
    int suma_svih = 0;
    scanf( "%d", &n );

    for( int i = 0; i < n; ++i ) {
        scanf( "%d", L + i ); suma_svih += L[i];

        for( int j = 0; j < L[i]; ++j )
            scanf( "%d", A[i] + j );
    }

    for( int b = 0; (1<<b) <= 1000; ++b ) {
        int len = 1<<b;
        int pola = len / 2;
        v_cnt = 0;

        for( int i = 0; i < n; ++i ) 
            for( int j = 0; j+len <= L[i]; ++j ) {
                llint Val = 0;

                if( len == 1 ) { Val = A[i][j]; }
                else { Val = rank[i][j][b-1]*100000100LL + rank[i][j+pola][b-1]; }

                V[ v_cnt++ ] = state( i, j, Val );
            }

        llint last = -1;
        int koji = -1;
        sort( V, V+v_cnt );

        for( int i = 0; i < v_cnt; ++i ) {
            if( last != V[i].rr ) { last = V[i].rr; ++koji; }
            rank[ V[i].x ][ V[i].poc ][ b ] = koji;
        }
    }

    for( int i = 0; i < n; ++i ) {
        Poc[i] = 0;
        pq.insert( i );
    }

    for( int cnt = 0; !pq.empty(); ++cnt ) {
        int x = *pq.begin(); pq.erase( pq.begin() );
        printf( "%d%c", A[x][Poc[x]], cnt+1 < suma_svih ? ' ' : '\n' );
        ++Poc[x]; if( Poc[x] != L[x] ) pq.insert( x );
    }

    return (0-0);
}
