#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 100000

int n;
int a[MAX], b[MAX];

int cmp( int i, int j ) {
    if( a[i] != a[j] ) return a[i] < a[j];
    return i < j;
}

struct node {
    int number;
    int frequency;
    int first;

    node( int a, int b, int c ) {
        number = a;
        frequency = b;
        first = c;
    }
};

bool operator < (const node &A, const node &B ) {
    if( A.frequency != B.frequency ) return A.frequency > B.frequency;
    return A.first < B.first;
}

int main( void ) {
    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) scanf( "%d", &a[i] );

    for( int i = 0; i < n; ++i ) b[i] = i;

    sort( b, b+n, cmp );

    vector<node> c;
    for( int i = 0, j; i < n; i = j ) {
        for( j = i+1; j < n && a[b[j]] == a[b[i]]; ++j );
        c.push_back( node( a[b[i]], j-i, b[i] ) );
    }

    sort( c.begin(), c.end() );
    for( vector<node>::iterator it = c.begin(); it != c.end(); ++it )
        for( int i = 0; i < it->frequency; ++i )
            printf( "%d ", it->number );
    printf( "\n" );

    return 0;
}
