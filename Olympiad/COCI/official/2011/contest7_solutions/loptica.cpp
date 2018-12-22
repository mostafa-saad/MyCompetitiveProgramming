#include <cstdio>
#include <cassert>

#define MAXNODES 1000000
#define MAXQUERIES 1000000

struct query { int type, node; } queries[MAXQUERIES];

int N, M;
int initial[MAXNODES];
int parent[MAXNODES];

int n_output;
int output[MAXQUERIES];

int getRoot( int x ) {
   if( parent[x] < 0 || parent[x] == x ) return x;
   return parent[x] = getRoot(parent[x]);
}

int main( void ) {
   scanf( "%d", &N );
   for( int i = 0; i < N; ++i ) parent[i] = -2;
   for( int i = 0; i < N; ++i ) {
      scanf( "%d", &initial[i] ); --initial[i];
      if( initial[i] == -1 ) parent[i] = -1;
   }
   scanf( "%d", &M );
   for( int i = 0; i < M; ++i ) {
      scanf( "%d%d", &queries[i].type, &queries[i].node ); --queries[i].node;
      if( queries[i].type == 1 ) {
         ++n_output;
      } else if( queries[i].type == 2 ) {
		 assert(parent[queries[i].node] != -1);
         parent[queries[i].node] = -1;
      }
   }
   for( int i = N-1; i >= 0; --i )
      if( parent[i] == -2 )
         parent[i] = getRoot(initial[i]);

   int *out = output + n_output;
   for( int i = M-1; i >= 0; --i ) {
      if( queries[i].type == 1 ) {
         int root = getRoot(queries[i].node);
         *--out = parent[root] == -1 ? root : -1;
      } else {
         parent[queries[i].node] = getRoot(initial[queries[i].node]);
      }
   }

   for( int i = 0; i < n_output; ++i )
      if( output[i] == -1 )
         printf( "CIKLUS\n" );
      else
         printf( "%d\n", output[i] + 1 );

   return 0;
}
