#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

struct coords {
   int x, y;
   coords( int X=0, int Y=0 ) { x=X; y=Y; }
} cubes[5], robot;
bool operator < ( const coords &A, const coords &B ) {
   if( A.x != B.x ) return A.x > B.x;
   return A.y > B.y;
}

const int target_x[5] = { 8, 7, 7, 7, 6 };
const int target_y[5] = { 8, 8, 7, 6, 8 };

const int dd[4] = { 'L', 'U', 'R', 'D' };
const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

struct state {
   coords robot, cube;
   char &Seen();
   pair<state, int> &How();
};
char seen[17][17][17][17];
pair<state, int> how[17][17][17][17];

char &state::Seen() { return seen[robot.x+8][robot.y+8][cube.x+8][cube.y+8]; }
pair<state, int> & state::How() { return how[robot.x+8][robot.y+8][cube.x+8][cube.y+8]; }

void reconstruct( state S ) {
   if( S.How().second == -1 ) return;

   reconstruct( S.How().first );
   printf( "%c", dd[S.How().second] );
}

void move( int A, coords destination ) {
   queue< state > Q;
   state S;
   S.robot = robot;
   S.cube = cubes[A];

   memset( seen, 0, sizeof seen );
   S.How() = make_pair( state(), -1 );
   S.Seen() = 1;

   for( Q.push( S ); !Q.empty(); Q.pop() ) {
      S = Q.front();

      for( int d = 0; d < 4; ++d ) {
         state T = S;
         T.robot.x += dx[d];
         T.robot.y += dy[d];
         if( T.robot.x < -8 || T.robot.x > 8 ) continue;
         if( T.robot.y < -8 || T.robot.y > 8 ) continue;

         int ok = 1;
         for( int i = 0; i < 5; ++i ) {
            if( i == A ) continue;
            if( T.robot.x == cubes[i].x && T.robot.y == cubes[i].y )
               ok = 0;
         }
         if( !ok ) continue;

         if( T.robot.x == T.cube.x && T.robot.y == T.cube.y ) {
            T.cube.x += dx[d];
            T.cube.y += dy[d];
            if( T.cube.x < -8 || T.cube.x > 8 ) continue;
            if( T.cube.y < -8 || T.cube.y > 8 ) continue;

            if( T.cube.x == destination.x && T.cube.y == destination.y ) {
               T.How() = make_pair( S, d );
               cubes[A] = destination;
               robot = T.robot;
               reconstruct( T );
               return;
            }

            for( int d2 = 0; d2 < 4; ++d2 )
               for( int i = 0; i < 5; ++i ) {
                  if( i == A ) continue;
                  if( T.cube.x + dx[d2] == cubes[i].x && T.cube.y + dy[d2] == cubes[i].y )
                     ok = 0;
               }

            if( !ok ) continue;
         }

         if( T.Seen() ) continue;
         T.Seen() = 1;
         T.How() = make_pair( S, d );
         Q.push( T );
      }
   }
}

int peek( int x, int y ) {
   for( int i = 0; i < 5; ++i )
      if( cubes[i].x == x && cubes[i].y == y ) return i;
   return -1;
}

int neighbourCount( int x, int y ) {
   int ret = 0;
   for( int d = 0; d < 4; ++d )
      for( int i = 0; i < 5; ++i )
         if( cubes[i].x == x + dx[d] && cubes[i].y == y + dy[d] )
            ++ret;
   return ret;
}

int main( void ) {
   robot.x = robot.y = 0;
   for( int i = 0; i < 5; ++i ) scanf( "%d%d", &cubes[i].x, &cubes[i].y );

   sort( cubes, cubes + 5 );

   int cross = 0;
   coords P;

   for( int x = -5; x <= 5; ++x )
      for( int y = -5; y <= 5; ++y )
         if( neighbourCount( x, y ) == 4 ) {
            P = coords( x, y );
            cross = 1;
         }

   if( cross && (P.x != 0 || P.y != 0) ) {
      move( peek( P.x, P.y+1 ), P );

      int fifth = -1;
      for( int i = 0; i < 5; ++i )
         if( abs( P.x - cubes[i].x ) >= 2 || abs( P.y - cubes[i].y ) >= 2 )
            fifth = i;

      move( fifth, coords( P.x, P.y-2 ) );
   } else {
      if( cross ) {
         if( peek( 0, 3 ) == -1 )
            move( peek( 0, 1 ), coords( 0, 2 ) );
         else
            move( peek( 1, 0 ), coords( 2, 0 ) );
      }

      for( int i = 0; i < 5; ++i )
         move( i, coords( target_x[i], target_y[i] ) );
   }
   printf( "\n" );

   return 0;
}
