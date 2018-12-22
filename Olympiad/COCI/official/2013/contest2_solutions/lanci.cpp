#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define MAX 500005

int N;
int l[ MAX ];

int main( void )
{
  scanf( "%d", &N );

  for( int i = 0; i < N; ++i )
    scanf( "%d", l + i );

  sort( l, l + N );

  int sol = 0;
  for( int i = 0; sol < N - i - 1; ++i ) 
    sol += min( N - i - 1 - sol, l[i] );

  printf( "%d\n", sol );

  return 0;
}
