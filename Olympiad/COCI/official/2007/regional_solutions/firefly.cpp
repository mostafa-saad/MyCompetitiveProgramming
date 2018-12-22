
/*
  Croatian Regional Competition in Informatics 2007
  Task FIREFLY
  Programming language C++
*/

#include <algorithm>
#include <cstdio>

using namespace std;

int n, h;
int stalagmiti[100000];
int stalaktiti[100000];

int main( void ) {
   scanf( "%d%d", &n, &h ); n /= 2;
   for( int i = 0; i < n; i++ ) scanf( "%d%d", &stalagmiti[i], &stalaktiti[i] );

   sort( stalagmiti, stalagmiti+n );
   sort( stalaktiti, stalaktiti+n );

   int mini = 1000000000, broj = 0;

   for( int y = 0; y < h; ++y ) {
      int kungfu =
         n - (int)(lower_bound( stalagmiti, stalagmiti+n, y+1 )-stalagmiti) +
         n - (int)(lower_bound( stalaktiti, stalaktiti+n, h-y )-stalaktiti);

      if( kungfu  < mini ) { mini = kungfu; broj = 0; }
      if( kungfu == mini ) ++broj;
   }

   printf( "%d %d\n", mini, broj );

   return 0;
}
