#include <cstdio>

#define MAXN 500
#define MAXK 500
#define MOD 1000000007

typedef long long llint;

int gcd( int a, int b ) { return b == 0 ? a : gcd( b, a%b ); }

llint komb[MAXN+1][MAXK+1];
llint povrh[MAXK+1];

struct node { llint dp[MAXK+1]; } nodes[3*MAXN], *allocator = nodes;

int k, h[MAXN];

void calc_povrh( int n ) {
   static int gore[MAXK], i;
   povrh[0] = 1;
   for( i = 1; i <= k && n >= i; ++i ) {
      gore[i-1] = n - i+1;
      
      int dole = i;
      for( int j = 0; j < i; ++j ) {
         int g = gcd( gore[j], dole );
         dole /= g;
         gore[j] /= g;
      }
      povrh[i] = 1;
      for( int j = 0; j < i; ++j ) povrh[i] = povrh[i] * gore[j] % MOD;
   }
   while( i <= k ) povrh[i++] = 0;
}

node *rec( int a, int b, int h0 ) {
   node *curr = allocator++;

   int leaf = 1, minh = 1000000000, minh_index = -1;
   for( int i = a; i < b; ++i ) {
      if( h[i] < minh ) { minh = h[i]; minh_index = i; }
      if( h[i] != h[a] ) leaf = 0;
   }

   if( leaf ) {
      calc_povrh( minh-h0 );  
      
      for( int i = 0; i <= k; ++i )
         curr->dp[i] = komb[b-a][i] * povrh[i]%MOD;
      
   } else if( minh > h0 ) {
      node *up = rec( a, b, minh );

      calc_povrh( minh-h0 );

      for( int i = 0; i <= k; ++i ) {
         curr->dp[i] = 0;
         for( int j = 0; j <= i && b-a-j >= 0; ++j )
            curr->dp[i] += up->dp[j] * povrh[i-j]%MOD * komb[b-a-j][i-j]%MOD;
         curr->dp[i] %= MOD;
      }
   } else {
      node *left = rec( a, minh_index, h0 );
      node *right = rec( minh_index+1, b, h0 );
      
      for( int i = 0; i <= k; ++i ) {
         curr->dp[i] = 0;
         for( int j = 0; j <= i; ++j ) 
            curr->dp[i] = curr->dp[i] + left->dp[j] * right->dp[i-j]%MOD;
         curr->dp[i] %= MOD;
      }
   }
   return curr;
}

int main( void ) {
   int n;
   scanf( "%d%d", &n, &k );
   for( int i = 0; i < n; ++i ) scanf( "%d", &h[i] );

   for( int i = 0; i <= n; ++i ) {
      komb[i][0] = 1;
      for( int j = 1; j <= i; ++j ) 
         komb[i][j] = komb[i][j-1] * (i-j+1) % MOD;
   }

   node * root = rec( 0, n, 0 );
   printf( "%d\n", root->dp[k] );

   return 0;
}
