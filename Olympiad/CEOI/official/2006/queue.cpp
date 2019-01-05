#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

map<int,int> map_next, map_prev;
multimap<int,int> L_queries, P_queries;
typedef multimap<int,int>::iterator mapiterator;

int next( int x ) {
   if( map_next.count( x ) ) return map_next[x];
   return x+1;
}
int prev( int x ) {
   if( map_prev.count( x ) ) return map_prev[x];
   return x-1;
}

int n, q;
const int inf = 2000000000;

void input_list() {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      int a, b;
      scanf( "%d%d", &a, &b );
      map_next[prev(a)] = next(a);
      map_prev[next(a)] = prev(a);

      int c = prev(b);
      map_next[c] = a;
      map_prev[a] = c;
      map_next[a] = b;
      map_prev[b] = a;
   }
   map_next[inf] = inf+1;
}

void input_queries() {
   scanf( "%d", &q );
   for( int i = 0; i < q; ++i ) {
      char type;
      int x;
      scanf( " %c %d", &type, &x );
      if( type == 'L' ) L_queries.insert( pair<int,int>(x, i) );
      if( type == 'P' ) P_queries.insert( pair<int,int>(x, i) );
   }
   L_queries.insert( pair<int,int>(inf, q) );
   P_queries.insert( pair<int,int>(inf, q) );
}

int main( void ) {

   input_list();
   input_queries();

   vector< int > ret( q+1 );
   int label = 0, position = 0;

   while( label < inf ) {
      int a = map_next.lower_bound( label )->first - label;
      int b = L_queries.lower_bound( position )->first - position;
      int c = P_queries.lower_bound( label )->first - label;

      int mini = a <? b <? c;

      label += mini;
      position += mini;

      if( mini == b ) {
         pair<mapiterator,mapiterator> eq = L_queries.equal_range( position );
         for( mapiterator it = eq.first; it != eq.second; ++it )
            ret[it->second] = label;
      }
      if( mini == c ) {
         pair<mapiterator,mapiterator> eq = P_queries.equal_range( label );
         for( mapiterator it = eq.first; it != eq.second; ++it )
            ret[it->second] = position;
      }

      label = next(label);
      ++position;
   }

   for( int i = 0; i < q; ++i )
      printf( "%d\n", ret[i] );

   return 0;
}
