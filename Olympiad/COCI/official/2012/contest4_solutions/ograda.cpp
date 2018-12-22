#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long llint;

const int MAXN = 300000;

int s[MAXN];
int a[MAXN], b[MAXN];

int main( void ) {
  int n;
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i )
    scanf( "%d", s+i );
  for( int i = 0; i < n; ++i )
    scanf( "%d", a+i );

  sort( a, a + n );
  int l = 0, r = n-1;

  for( int i = 1; i < n-1; ++i )
    if( s[i] > s[i-1] && s[i] > s[i+1] ) b[i] = a[r--]; else // k = +2
      if( s[i] < s[i-1] && s[i] < s[i+1] ) b[i] = a[l++]; // k = -2

  if( s[0] < s[1] ) b[0] = a[l++]; else b[0] = a[r--]; // k = -1 ili +1
  if( s[n-1] < s[n-2] ) b[n-1] = a[l++]; else b[n-1] = a[r--]; // k = -1 ili +1

  for( int i = 1; i < n-1; ++i ) // k = 0
    if( s[i-1] < s[i] && s[i] < s[i+1] ) b[i] = a[l++]; else
      if( s[i-1] > s[i] && s[i] > s[i+1] ) b[i] = a[r--];

  llint sum = 0;
  for( int i = 0; i < n-1; ++i )
    if( b[i] < b[i+1] ) sum += b[i+1]-b[i]; else
      sum += b[i]-b[i+1];

  printf( "%lld\n", sum );
  for( int i = 0; i < n; ++i )
    printf( "%d ", b[i] );
  putchar( '\n' );
  return 0;
}
