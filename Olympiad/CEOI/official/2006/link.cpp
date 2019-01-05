#include <cstdio>
#include <vector>

using namespace std;

#ifdef DJGPP
unsigned _stklen = 16*1024*1024;
#endif

#define MAXN 1000000
const int inf = 1000000000;

int n, k;
int link[MAXN];
int dead[MAXN];
vector<int> adj[MAXN];

vector< vector<int> > ciklusi;

int result = 0;

void nadji_cikluse() {
   vector<int> bio( n, 0 );
   int time = 0;

   for( int i = 0; i < n; ++i ) {
      if( bio[i] ) continue;
      int a, b;

      bio[i] = ++time;
      for( a = link[i]; !bio[a]; a = link[a] )
         bio[a] = ++time;

      if( bio[a] < bio[i] ) continue;

      ciklusi.push_back( vector<int> (1,a) );
      for( b = link[a]; b != a; b = link[b] )
         ciklusi.back().push_back( b );
   }
}

int rec( int a ) {
   int kill = 0;
   for( vector<int>::iterator it = adj[a].begin(); it != adj[a].end(); ++it )
      kill >?= rec( *it );
   if( a == 0 ) kill = k+1;

   dead[a] = 1;
   if( kill == 0 ) {
      kill = k;
      ++result;
   }
   return kill-1;
}

int main( void ) {
   scanf( "%d%d", &n, &k );

   for( int i = 0; i < n; ++i ) {
      int a, b;
      scanf( "%d%d", &a, &b ); --a; --b;
      link[a] = b;
      adj[b].push_back( a );
   }

   nadji_cikluse();

   for( vector< vector<int> >::iterator it = ciklusi.begin(); it != ciklusi.end(); ++it ) {
      vector<int> &ciklus = *it;

      int m = ciklus.size();

      {
         int kill = 0;
         int prev = ciklus[m-1];
         for( int i = 0; i < 2*m; ++i ) {
            int curr = ciklus[i%m];

            if( i < m ) {
               for( vector<int>::iterator it = adj[curr].begin(); it != adj[curr].end(); ++it ) {
                  if( *it == prev ) continue;
                  kill >?= rec( *it );
               }
               if( curr == 0 ) kill = k+1;
            }
            if( kill-- > 0 ) dead[curr] = 1;

            prev = curr;
         }
      }

      vector<int> next( m, inf );

      {
         int prev = 0;
         for( int i = 2*m-1; i >= 0; --i ) {
            int curr = i%m;

            next[curr] = next[prev]+1;
            if( !dead[ciklus[curr]] ) next[curr] = 0;

            prev = curr;
         }
      }
      if( next[0] >= inf ) continue;


      {
         int best = 1000000;
         for( int start = 0; start < (k<?m); ++start ) {
            int cost = 0;
            int i = start + next[start];
            while( i - start < m ) {
               ++cost;
               i += k;
               i += next[i%m];
            }
            best <?= cost;
         }
         result += best;
      }
   }

   printf( "%d\n", result );

   return 0;
}
