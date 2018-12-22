#include <cstdio>

#define MAXSIEVE 7380000
#define MAXPRIMES 501000
int p[MAXPRIMES], np;
char sieve[MAXSIEVE];

int N;
int mod( int a ) { return (a%N + N) % N; }

int forward( int x, int p ) {
    if( x == 0 ) return mod(p);

    if( x <= p%(N-1) ) x = mod(x-1);
    x = mod(x - p/(N-1));

    return x;
}

int backward( int x, int p ) {
    if( x == mod(p) ) return 0;

    x = mod(x + p/(N-1));
    if( x <= p%(N-1) ) x = mod(x+1);

    return x;
}

int main( void ) {
    for( int i = 2; i < MAXSIEVE; ++i ) {
        if( sieve[i] ) continue;
        p[np++] = i;
        for( int j = i+i; j < MAXSIEVE; j += i ) sieve[j] = 1;
    }

    int A, K;
    scanf( "%d%d%d", &N, &K, &A ); --A;
    for( int i = 0; i < K; ++i ) A = forward(A, p[i]);

    int L = mod(A-1), R = mod(A+1);

    for( int i = K-1; i >= 0; --i ) L = backward(L, p[i]);
    for( int i = K-1; i >= 0; --i ) R = backward(R, p[i]);

    printf( "%d %d\n", R+1, L+1 );
    return 0;
}
