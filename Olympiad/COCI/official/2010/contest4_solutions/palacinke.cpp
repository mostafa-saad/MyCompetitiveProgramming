#include <iostream>
#include <string>

using namespace std;

#define MAXV 25
#define MAXE 500
#define SIZE 1+2*MAXV
#define MOD 5557

int n;
void mult( int a[SIZE][SIZE], int b[SIZE][SIZE], int c[SIZE][SIZE] ) {
    static int tmp[SIZE][SIZE];
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j ) {
            tmp[i][j] = 0;
            for( int k = 0; k < n; ++k )
                tmp[i][j] += a[i][k] * b[k][j];
        }
    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j )
            c[i][j] = tmp[i][j] % MOD;
}

int id( int u, int t ) { return 1 + u*2 + t; }

int N, M, T;
struct edge { int u, v, mask; } E[MAXE];

int solve( int mask ) {
    static int A[SIZE][SIZE];
    static int B[SIZE][SIZE];

    for( int i = 0; i < n; ++i )
        for( int j = 0; j < n; ++j ) {
            A[i][j] = 0;
            B[i][j] = i==j;
        }
    A[0][0] = 1;
    for( int u = 0; u < N; ++u ) A[id(u, 1)][id(u, 0)] = 1;

    for( int i = 0; i < M; ++i ) {
        ++A[id(E[i].v, 0)][id(E[i].u, 0)];
        if( !(E[i].mask & mask) ) ++A[id(E[i].v, 0)][id(E[i].u, 1)];

        if( E[i].v == 0 ) {
            ++A[0][id(E[i].u, 0)];
            if( !(E[i].mask & mask) ) ++A[0][id(E[i].u, 1)];
        }
    }

    for( int k = T;; ) {
        if( k & 1 ) mult( B, A, B );
        if( !(k >>= 1) ) break;
        mult( A, A, A );
    }

    return B[0][id(0, 0)];
}

int main( void ) {
    cin >> N >> M;
    n = 1 + 2*N;
    for( int i = 0; i < M; ++i ) {
        string s;
        cin >> E[i].u >> E[i].v >> s;
        --E[i].u; --E[i].v;
        E[i].mask = 0;
        if( s.find("B") != string::npos ) E[i].mask |= 1;
        if( s.find("J") != string::npos ) E[i].mask |= 2;
        if( s.find("M") != string::npos ) E[i].mask |= 4;
        if( s.find("P") != string::npos ) E[i].mask |= 8;
    }
    cin >> T;

    int ret = 0;
    for( int mask = 0; mask < 16; ++mask ) {
        int sgn = 1;
        for( int i = 0; i < 4; ++i )
            if( (mask>>i)&1 ) sgn = -sgn;
        ret += sgn * solve(mask);
    }

    cout << (ret%MOD + MOD)%MOD << endl;

    return 0;
}
