/*
  Zadatak PROGRAM (honi 5. kolo)
  Sluzbeno rjesenje, trebalo bi biti potpuno tocno.

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

const int MAXN = 1000100;

int n, k;
int q;

int X[ MAXN ];
int Niz[ MAXN ];

long long Prefix[ MAXN ];

int main()
{
    memset( Niz, 0, sizeof Niz );

    scanf( "%d %d", &n, &k );
    for( int i = 0; i < k; ++i )         
        scanf( "%d", X + i );

    //    int progress = 0;
    //    int next = 1;

    sort( X, X + k );
    for( int i = 0; i < k; ) {
        int temp = X[i];
        int cnt = 0;

        for( ; i < k && X[i] == temp; ++i )
            ++cnt;

        for( int iter = 0; iter < n; iter += temp )
            Niz[ iter ] += cnt;

        //        if( i >= progress+next ) {
        //            progress += next;
        //            next *= 2;
        //            printf( "obradio %d\n", progress );
        //        }
    }

    //    printf( "Niz =" ); for( int i = 0; i < n; ++i )
    //        printf( " %d", Niz[i] );
    //    putchar( '\n' );

    Prefix[0] = 0;
    for( int i = 0; i < n; ++i )
        Prefix[i+1] = Prefix[i] + Niz[i];

    scanf( "%d", &q );
    for( int i = 0; i < q; ++i ) {
        int l, r; scanf( "%d %d", &l, &r );
        printf( "%lld\n", Prefix[r+1] - Prefix[l] );
    }

    return (0-0);
}
