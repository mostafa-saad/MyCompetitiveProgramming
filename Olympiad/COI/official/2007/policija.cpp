/*
  Croatian Olympiad in Informatics 2007
  Task POLICIJA
*/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int n, m;
struct edge {
   int u, v;
   edge( int U, int V ) { u = U; v = V; }
};
bool operator < ( const edge &A, const edge &B ) { return A.u < B.u; }

struct sparse_graph {
   vector<edge> E;
   vector< vector<edge>::iterator > V;

   void insert_edge( const edge &e ) {
      E.push_back( e );
   }

   void init() {
      V.resize(n+1);
      sort( E.begin(), E.end() );
      V[0] = E.begin();
      for( int i = 1; i <= n; ++i )
         for( V[i] = V[i-1]; V[i] != E.end() && V[i]->u < i; ++V[i] );
   }

   inline vector<edge>::iterator begin( int u ) { return V[u]; }
   inline vector<edge>::iterator end( int u ) { return V[u+1]; }
} graph;

vector<int> discover, finish, lowlink, depth;
int Time = 0;

vector< vector<int> > children;

void dfs( int u, int dad, int d ) {
   discover[u] = lowlink[u] = Time++;
   depth[u] = d;

   for( vector<edge>::iterator it = graph.begin(u); it != graph.end(u); ++it ) {
      if( it->v == dad ) continue;

      if( discover[it->v] == -1 ) {
         dfs( it->v, u, d+1 );
         lowlink[u] <?= lowlink[it->v];
         children[u].push_back( it->v );
      } else {
         lowlink[u] <?= discover[it->v];
      }
   }

   finish[u] = Time++;
}

int is_descendant( int a, int b ) {
   return discover[b] <= discover[a] && finish[a] <= finish[b];
}

int find_related_child( int me, int descendant ) {
   int lo = 0, hi = children[me].size() - 1;
   while( lo != hi ) {
      int mid = (lo+hi) / 2;

      if( discover[descendant] > finish[ children[me][mid] ] ) lo = mid+1;
      else if( finish[descendant] < discover[ children[me][mid] ] ) hi = mid-1;
      else lo = hi = mid;
   }
   return children[me][lo];
}

int main( void ) {
   scanf( "%d%d", &n, &m );
   for( int i = 0; i < m; ++i ) {
      int u, v;
      scanf( "%d%d", &u, &v ); --u; --v;
      graph.insert_edge( edge( u, v ) );
      graph.insert_edge( edge( v, u ) );
   }
   graph.init();
   discover = finish = lowlink = depth = vector<int> (n, -1);
   children.resize( n );
   dfs( 0, -1, 0 );

   scanf( "%d", &m );
   for( int i = 0; i < m; ++i ) {
      int tip, a, b, c, d;
      scanf( "%d%d%d%d", &tip, &a, &b, &c ); --a; --b; --c;
      if( tip == 1 ) {
         scanf( "%d", &d ); --d;
         if( is_descendant( c, d ) ) swap( c, d );

         if( depth[d] != depth[c]+1 ) printf( "yes\n" );
         else if( lowlink[d] < discover[d] ) printf( "yes\n" );
         else if( is_descendant( a, d ) == is_descendant( b, d ) ) printf( "yes\n" );
         else printf( "no\n" );

      } else {
         if( !is_descendant( a, c ) && !is_descendant( b, c ) ) printf( "yes\n" );
         else if( is_descendant( a, c ) && is_descendant( b, c ) ) {
            int e = find_related_child( c, a );
            int f = find_related_child( c, b );
            if( e == f ) printf( "yes\n" );
            else if( lowlink[e] < discover[c] && lowlink[f] < discover[c] ) printf( "yes\n" );
            else printf( "no\n" );
         } else {
            if( is_descendant( a, c ) ) swap( a, b );
            int e = find_related_child( c, b );
            if( lowlink[e] < discover[c] ) printf( "yes\n" );
            else printf( "no\n" );
         }
      }
   }

   return 0;
}
