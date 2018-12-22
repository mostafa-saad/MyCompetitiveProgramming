
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task PROSTOR
  Programming language C++
*/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 1000

typedef long long llint;

struct loga2D {
   int a[MAX][MAX];

   void clear() {
      memset( a, 0, sizeof a );
   }

   void update( int X, int Y, int delta ) {
      for( int x = X; x <= MAX; x += x&-x )
         for( int y = Y; y <= MAX; y += y&-y )
            a[x][y] += delta;
   }

   int query( int X, int Y ) {
      int ret = 0;
      for( int x = X; x > 0; x -= x&-x )
         for( int y = Y; y > 0; y -= y&-y )
            ret += a[x][y];
      return ret;
   }

   int query( int X1, int Y1, int X2, int Y2 ) {
      return query( X2, Y2 ) - query( X1-1, Y2 ) - query( X2, Y1-1 ) + query( X1-1, Y1-1 );
   }

} Lo, Hi;

struct event {
   int type, y;
   int x1, x2;
   int z1, z2;
   event( int T, int Y, int X1, int X2, int Z1, int Z2 ) {
      type = T; y = Y;
      x1 = X1; x2 = X2;
      z1 = Z1; z2 = Z2;
   }
};
bool operator < ( const event &A, const event &B ) {
   if( A.y != B.y ) return A.y < B.y;
   return A.type < B.type;
}

llint sweep( vector<event> &E ) {
   llint ret = 0;

   sort( E.begin(), E.end() );
   Lo.clear();
   Hi.clear();

   for( vector<event>::iterator it = E.begin(); it != E.end(); ++it ) {
      if( it->type == 1 || it->type == 2 ) {
         ret += Lo.query( it->x1, 1, it->x2, it->z2 ) - Hi.query( it->x1, 1, it->x2, it->z1 - 1 );
      }
      if( it->type == 1 ) {
         Lo.update( it->x1, it->z1, 1 );
         Hi.update( it->x2, it->z2, 1 );
      }
      if( it->type == 3 ) {
         Lo.update( it->x1, it->z1, -1 );
         Hi.update( it->x2, it->z2, -1 );
      }
   }

   return ret;
}

int main( void ) {
   int n;
   scanf( "%d", &n );

   vector<event> sweepXY;
   vector<event> sweepYZ;
   vector<event> sweepZX;

   for( int i = 0; i < n; ++i ) {
      int x1, y1, z1;
      int x2, y2, z2;
      scanf( "%d%d%d", &x1, &y1, &z1 );
      scanf( "%d%d%d", &x2, &y2, &z2 );
      if( x2 < x1 ) swap( x1, x2 );
      if( y2 < y1 ) swap( y1, y2 );
      if( z2 < z1 ) swap( z1, z2 );

      if( x1 == x2 ) {
         sweepXY.push_back( event( 1, y1, x1, x2, z1, z2 ) );
         sweepZX.push_back( event( 2, x1, z1, z2, y1, y2 ) );
         sweepXY.push_back( event( 3, y2, x1, x2, z1, z2 ) );
      }
      if( y1 == y2 ) {
         sweepYZ.push_back( event( 1, z1, y1, y2, x1, x2 ) );
         sweepXY.push_back( event( 2, y1, x1, x2, z1, z2 ) );
         sweepYZ.push_back( event( 3, z2, y1, y2, x1, x2 ) );
      }
      if( z1 == z2 ) {
         sweepZX.push_back( event( 1, x1, z1, z2, y1, y2 ) );
         sweepYZ.push_back( event( 2, z1, y1, y2, x1, x2 ) );
         sweepZX.push_back( event( 3, x2, z1, z2, y1, y2 ) );
      }
   }

   printf( "%lld\n", sweep(sweepXY) + sweep(sweepYZ) + sweep(sweepZX) );

   return 0;
}
