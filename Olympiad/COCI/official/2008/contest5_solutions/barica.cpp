#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

#define MAXN 300000

using namespace std;

const int inf = 1000000000;

int n;
struct point { int x, y, m; } p[MAXN+1];

bool cmp ( int a, int b ) {
   if( p[a].x != p[b].x ) return p[a].x < p[b].x;
   return p[a].y < p[b].y;
}
 
int dp[MAXN+1];
int how[MAXN+1];
int max_x[100001];
int max_y[100001];

int order[MAXN];

int main( void ) {
   memset( max_x, 0, sizeof max_x );
   memset( max_y, 0, sizeof max_y );

   int n, k;
   scanf( "%d%d", &n, &k );

   for( int i = 1; i <= n; ++i ) {
      scanf( "%d%d%d", &p[i].x, &p[i].y, &p[i].m );
      order[i-1] = i;
   }
   sort( order, order+n, cmp );

   dp[0] = -inf;
   for( int i = 0; i < n; ++i ) {
      int a = order[i];

      dp[a] = -inf;
      if( a == 1 ) dp[a] = p[a].m;
      
      int &xx = max_x[p[a].x];
      int &yy = max_y[p[a].y];

      if( dp[xx] >= k && dp[a] < dp[xx] + p[a].m - k ) {
         dp[a] = dp[xx] + p[a].m - k;
         how[a] = xx;
      }
      if( dp[yy] >= k && dp[a] < dp[yy] + p[a].m - k ) {
         dp[a] = dp[yy] + p[a].m - k;
         how[a] = yy;
      }

      if( dp[a] > dp[xx] ) xx = a;
      if( dp[a] > dp[yy] ) yy = a;
   }   

   stack<int> S;
   for( int a = n; a != 1; a = how[a] )
      S.push( a );
   S.push( 1 );

   printf( "%d\n", dp[n] );
   printf( "%d\n", S.size() );
   while( !S.empty() ) {
      printf( "%d %d\n", p[S.top()].x, p[S.top()].y );
      S.pop();
   }

   return 0;
}
