/* A solution for BOI 2009 task BEETLE.
 * Correct. Requires O(N^3) time and O(N^2) memory.
 * Author: Vytautas Gruslys
 */

#include <cstdio>
#include <iostream>

#define A_LOT 100000000
#define MAX_DROPS 502

int left[MAX_DROPS][MAX_DROPS], right[MAX_DROPS][MAX_DROPS], drop[MAX_DROPS];
int N, M;

int abs( int x ) {
    if( x < 0 ) return -x;
    return x;
};

void read() {
    scanf( "%d%d", &N, &M );
    for( int d = 0; d < N; d++)
        scanf( "%d", &drop[d + 1] );
    drop[0] = -A_LOT;
    drop[N + 1] = A_LOT;
};

int min( int a, int b ) {
    if( a < b && a < A_LOT) return a;
    if( b < A_LOT ) return b;
    return A_LOT;
};

int multiply( int a, int b ) {
    if( b == 0 || a <= A_LOT / b ) return a * b;
    return A_LOT;
};

void fill( int k ) {
    for( int d = 1; d <= N - k; d++ ) {
        left[d][d + k] = 0;
        right[d][d + k] = 0;
    };
    
    for( int s = k - 1; s >= 0; s-- )
        for( int d = 1; d <= N - s; d++ ) {
            left[d][d + s]  = min( left[d - 1][d + s]  + multiply( drop[d] - drop[d - 1], k - s ),
                                   right[d][d + s + 1] + multiply( drop[d + s + 1] - drop[d], k - s ) );
            right[d][d + s] = min( left[d - 1][d + s]  + multiply( drop[d + s] - drop[d - 1], k - s ),
                                   right[d][d + s + 1] + multiply( drop[d + s + 1] - drop[d + s], k - s ) );
        };
};

void sort() {
    int d = 1;
    while( d < N )
        if( drop[d] > drop[d + 1] ) {
            int temp = drop[d];
            drop[d] = drop[d + 1];
            drop[d + 1] = temp;
            d--;
        } else d++;
};

void write() {
    int best = 0;
    for( int k = 0; k < N; k++ ) {
        fill( k );
        for( int d = 1; d <= N; d++ ) {
            if( best < ( k + 1 ) * M - left[d][d] - ( k + 1 ) * abs(drop[d]) )
                best = ( k + 1 ) * M - left[d][d] - ( k + 1 ) * abs(drop[d]);
        };
    };
    printf( "%d\n", best );
};

int main() {
    read();
    sort();
    write();
    return 0;
};
