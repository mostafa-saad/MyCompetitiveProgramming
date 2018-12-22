#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int cur[100];
int end[100];

int next[101];
int prev[101];

vector<int> zaba;
vector<int> koliko;

void skoci( int x ) {
  if( zaba.empty() || zaba.back() != x ) {
    zaba.push_back( x );
    koliko.push_back( 0 );
  }
  ++koliko.back();

  for( int i = 0; i < x; ++i ) {
    int a = prev[x];
    int y = next[x];
    int b = next[y];
    next[a] = y; prev[y] = a;
    next[y] = x; prev[x] = y;
    next[x] = b; prev[b] = x;
  }
}

void rijesi( int *niz, int rev ) {
  zaba.clear();
  koliko.clear();

  for( int i = 0; i < n; ++i ) {
    next[niz[i]] = niz[(i+1)%n];
    prev[niz[(i+1)%n]] = niz[i];
  }

  for( int t = n-2; t >= 2; --t ) {
    while( next[1] != t+1 ) skoci( 1 );
    for( int i = 2; i < t+1; ++i )
      while( next[i] > i && next[i] != t+1 )
        skoci( i );
  }

  while( next[1] != 2 ) skoci( 1 );
  while( next[n] != 1 ) skoci( n );

  if( rev ) {
    reverse( zaba.begin(), zaba.end() );
    reverse( koliko.begin(), koliko.end() );
  }

  for( int i = 0; i < zaba.size(); ++i ) {
    int a = zaba[i];
    int b = koliko[i];
    if( rev ) b *= (n-1) / __gcd( n-1, a ) - 1;
    b %= (n-1) / __gcd( n-1, a );
    for( ; b > 0; --b ) printf( "%d\n", a );
  }
}

int main( void ) {
  scanf( "%d", &n );
  for( int i = 0; i < n; ++i ) scanf( "%d", &cur[i] );
  for( int i = 0; i < n; ++i ) scanf( "%d", &end[i] );
  rijesi( cur, 0 );
  rijesi( end, 1 );
  return 0;
}

