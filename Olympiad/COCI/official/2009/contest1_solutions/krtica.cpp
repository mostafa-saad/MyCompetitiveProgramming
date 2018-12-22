#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 300000

const int inf = 1000000000;

int n;
vector<int> adj[MAX];
int qhead, qtail;
int queue[MAX];
int dad[MAX];
int dist[MAX];

int visina[MAX][3];
int how_visina[MAX][3];
int dole_diametar[MAX];
int best_dole_diametar[MAX][2];
int how_dole_diametar[MAX][2];
int rez_diametar[MAX];
int rez_put[MAX];

void bfs( int start, int nemoj_tamo ) {
   for( int i = 0; i < n; ++i ) {
      dad[i] = -1;
      dist[i] = inf;
   }

   if( nemoj_tamo >= 0 ) dist[nemoj_tamo] = -inf;
   
   qhead = qtail = 0;
   
   dist[start] = 0;
   queue[qtail++] = start;
   while( qhead != qtail ) {
      int x = queue[qhead++];
      for( vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); ++it ) {
         if( dist[*it] <= dist[x] + 1 ) continue;
         dad[*it] = x;
         dist[*it] = dist[x] + 1;
         queue[qtail++] = *it;
      }
   }

}

int pol_dijametra( int A, int nemoj_tamo ) {
   bfs( A, nemoj_tamo );
   int B = queue[qhead-1];
   bfs( B, nemoj_tamo );
   int C = queue[qhead-1];
   int D = C;
   for( int i = 0; i < dist[C]/2; ++i ) D = dad[D];
   return D;
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 1; i < n; ++i ) {
      int a, b;
      scanf( "%d%d", &a, &b );
      --a; --b;
      adj[a].push_back( b );
      adj[b].push_back( a );
   }
   
   bfs( 0, -1 );

   for( int i = 0; i < n; ++i ) {
      for( int j = 0; j < 3; ++j ) {
         visina[i][j] = 0;
         how_visina[i][j] = -1;
      }
      for( int j = 0; j < 2; ++j ) {
         best_dole_diametar[i][j] = 0;
         how_dole_diametar[i][j] = -1;
      }
      dole_diametar[i] = 0;
      rez_put[i] = 0;
      rez_diametar[i] = 0;
   }

   for( int i = n-1; i >= 0; --i ) {
      int x = queue[i];

      for( vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); ++it ) {
         if( *it == dad[x] ) continue;
         
         int V = visina[*it][0] + 1;
         for( int j = 2; j >= 0; --j ) 
            if( V > visina[x][j] ) {
               if( j+1 < 3 ) {
                  visina[x][j+1] = visina[x][j];
                  how_visina[x][j+1] = how_visina[x][j];
               }
               visina[x][j] = V;
               how_visina[x][j] = *it;
            } else break;         
         
         int D = dole_diametar[*it];
         for( int j = 1; j >= 0; --j ) 
            if( D > best_dole_diametar[x][j] ) {
               if( j+1 < 2 ) {
                  best_dole_diametar[x][j+1] = best_dole_diametar[x][j];
                  how_dole_diametar[x][j+1] = how_dole_diametar[x][j];
               }
               best_dole_diametar[x][j] = D;
               how_dole_diametar[x][j] = *it;
            } else break;         
      }
      dole_diametar[x] = best_dole_diametar[x][0];
      dole_diametar[x] = max( dole_diametar[x], visina[x][0] + visina[x][1] );
   }

   int ret = inf, how;
   for( int i = 0; i < n; ++i ) {
      int x = queue[i];
      int y = dad[x];

      if( y == -1 ) {
         rez_put[x] = -inf;
         rez_diametar[x] = -inf;
         continue;
      }
      
      rez_put[x] = max( rez_put[x], 1+rez_put[y] );
         
      if( how_visina[y][0] == x ) rez_put[x] = max( rez_put[x], visina[y][1] );
      else rez_put[x] = max( rez_put[x], visina[y][0] );

      rez_diametar[x] = max( rez_diametar[x], rez_diametar[y] );         
      
      if( how_visina[y][0] == x ) {
         rez_diametar[x] = max( rez_diametar[x], (1+rez_put[y]) + visina[y][1] );
         rez_diametar[x] = max( rez_diametar[x], visina[y][1] + visina[y][2] );
      } else if( how_visina[y][1] == x ) {
         rez_diametar[x] = max( rez_diametar[x], (1+rez_put[y]) + visina[y][0] );
         rez_diametar[x] = max( rez_diametar[x], visina[y][0] + visina[y][2] );
      } else {
         rez_diametar[x] = max( rez_diametar[x], (1+rez_put[y]) + visina[y][0] );
         rez_diametar[x] = max( rez_diametar[x], visina[y][0] + visina[y][1] );
      }

      if( how_dole_diametar[y][0] == x ) {
         rez_diametar[x] = max( rez_diametar[x], best_dole_diametar[y][1] );         
      } else {
         rez_diametar[x] = max( rez_diametar[x], best_dole_diametar[y][0] );
      }

      int novi_diametar = max( dole_diametar[x], rez_diametar[x] );
      novi_diametar = max( novi_diametar, 1 + (dole_diametar[x]+1)/2 + (rez_diametar[x]+1)/2 );
      
      if( novi_diametar < ret ) {
         ret = novi_diametar;
         how = x;
      }
   }

   int A = how, B = dad[how];
   printf( "%d\n", ret );
   printf( "%d %d\n", A+1, B+1 );
   printf( "%d %d\n", pol_dijametra( A, B )+1, pol_dijametra( B, A )+1 );

   return 0;
}
