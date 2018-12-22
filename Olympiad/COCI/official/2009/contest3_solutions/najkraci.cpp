#include <cstdio>
#include <set>

using namespace std;

#define MAXV 3000
#define MAXE 10000
#define MOD 1000000007
#define INF 1000000000

struct edge {
   int u, v;
   int weight;   
   int ret;
   edge *next;
};

int n, m;
edge E[MAXE];
edge *adj[MAXV];
int paths_to[MAXV], paths_from[MAXV];
int dist[MAXV];

int n_settled;
int settled[MAXV];

struct cmp {
   bool operator () ( int a, int b ) {
      if( dist[a] != dist[b] ) return dist[a] < dist[b];
      return a < b;
   }
};

void solve( int source ) {
   for( int i = 0; i < n; ++i ) dist[i] = INF;
   
   set<int,cmp> PQ;
   dist[source] = 0;
   paths_to[source] = 1;
   n_settled = 0;
   PQ.insert( source );

   while( !PQ.empty() ) {
      int u = *PQ.begin();
      PQ.erase( PQ.begin() );
    
      settled[n_settled++] = u;
  
      for( edge *e = adj[u]; e; e = e->next ) {
         if( dist[e->v] < dist[u] + e->weight ) continue;
         if( dist[e->v] > dist[u] + e->weight ) {
            paths_to[e->v] = 0;
            if( dist[e->v] != INF ) PQ.erase( e->v );
            dist[e->v] = dist[u] + e->weight;
            PQ.insert( e->v );
         }
         paths_to[e->v] = (paths_to[e->v] + paths_to[u]) % MOD;
      }
   }

   for( int i = n_settled-1; i >= 0; --i ) {
      int u = settled[i];
      
      paths_from[u] = 1;
      for( edge *e = adj[u]; e; e = e->next ) {
         if( dist[e->v] < dist[u] + e->weight ) continue;

         paths_from[u] = (paths_from[u] + paths_from[e->v]) % MOD;

         e->ret = (e->ret + (long long)paths_to[u]*paths_from[e->v]) % MOD;
      }
   }
}

int main( void ) {
   scanf( "%d%d", &n, &m );
   for( int i = 0; i < n; ++i ) adj[i] = 0;

   for( int i = 0; i < m; ++i ) {
      scanf( "%d%d%d", &E[i].u, &E[i].v, &E[i].weight );
      --E[i].u;
      --E[i].v;
      E[i].ret = 0;
      E[i].next = adj[ E[i].u ];
      adj[ E[i].u ] = &E[i];
   }

   for( int i = 0; i < n; ++i )
      solve( i );
   
   for( int i = 0; i < m; ++i ) 
      printf( "%d\n", E[i].ret );
   
   return 0;
}
