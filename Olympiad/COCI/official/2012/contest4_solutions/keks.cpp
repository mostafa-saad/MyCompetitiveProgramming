#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;

char s[MAXN], a[MAXN];
vector< int > v[10];

int main( void ) {
  int n, k;
  scanf( "%d %d", &n, &k );
  scanf( "%s", s );
  
  for( int i = n-1; i >= 0; --i )
    v[ s[i]-'0' ].push_back( i );

  int m = n-k, p = 0;
  for( int i = 0; i < m; ++i ) { //biramo n-k znamenaka
    for( int j = 9; j >= 0; --j ) {
      while( v[j].size() > 0 && v[j].back() < p ) v[j].pop_back();
      if( v[j].size() > 0 && n-v[j].back()-1 >= m-i-1 ) { p = v[j].back(); break; }
    }
    a[i] = s[p], p++;
  }

  a[m] = '\0';
  puts( a );
  return 0;
}
