#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef unsigned int uint;

const int MAXN = 100003;

vector< uint > X[MAXN];
vector< int > E[MAXN], oa[MAXN], ob[MAXN];
int off[MAXN];
uint bio[MAXN], v[MAXN];

queue< int > Q;

int main( void ) {
  int n, m;
  scanf( "%d %d", &n, &m );
  for( int i = 0; i < m; ++i ) {
    int tip, a, b;
    scanf( "%d %d %d", &tip, &a, &b );
    if( tip == 1 ) off[a-1] = (off[a-1] + b)%32;
    if( tip == 2 ) {
      uint x;
      scanf( "%u", &x );
      --a, --b;
      E[a].push_back( b );
      X[a].push_back( x );
      oa[a].push_back( off[a] );
      ob[a].push_back( off[b] );
      E[b].push_back( a );
      X[b].push_back( x );
      oa[b].push_back( off[b] );
      ob[b].push_back( off[a] );
    }
  }
    
  for( int i = 0; i < n; ++i )
    for( int j = 31; j >= 0; --j )
      if( ( (bio[i]>>j)&1 ) == 0 ) {
        Q.push( (i*32 + j)*2 + 0 );
        while( !Q.empty() ) {
          int i = (Q.front()/2)/32;
          int j = (Q.front()/2)%32;
          int val = (Q.front()%2); Q.pop();
                    
          for( int k = 0; k < (int)E[i].size(); ++k ) {
            int w = (j-oa[i][k]+32)%32;
            int y = (w+ob[i][k])%32;
            
            int x = E[i][k], xval = ((X[i][k]>>w)&1)^val;
            if( (bio[x]>>y)&1 ) {
              if( ((v[x]>>y)&1) != xval ) { puts( "-1" ); return 0; }
            } else {
              Q.push( (x*32 + y)*2 + xval );
              bio[x] |= (1U<<y);
              v[x] |= (uint(xval)<<y);
            }
          }
        }
      }

  
  for( int i = 0; i < n; ++i ) {
    if( i ) putchar( ' ' );
    printf( "%u", v[i] );
  }
  putchar( '\n' );
  return 0;
}
