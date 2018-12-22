#include <cstdio>
#include <cstring>

#define MAX 250000

inline int mod10( int x ) { 
   if( x < 10 ) return x;
   return x-10;
}

struct Interval {
   int lo, hi;
   int freq[10];   
   int lazy;
   Interval *left, *right;
   
   Interval() { lazy = 0; memset( freq, 0, sizeof freq ); }

   void rotate( int rot ) {
      static int tmp[10];
      for( int i = 0; i < 10; ++i ) tmp[i] = freq[i];
      for( int i = 0; i < 10; ++i ) freq[mod10(i+rot)] = tmp[i];
      lazy = mod10( lazy + rot );
   }
   
   void split() {
      left->rotate( lazy );
      right->rotate( lazy );
      lazy = 0;
   }
   
   void join() {
      for( int i = 0; i < 10; ++i ) 
         freq[i] = left->freq[i] + right->freq[i];
   }
} memory[2*MAX], *allocator = memory;

int n;
char start[MAX+1];

void tree_build( Interval *x ) {
   if( x->lo == x->hi ) {
      x->freq[ start[x->lo]-'0' ] = 1;
   } else {
      int mid = (x->lo + x->hi)/2;
      
      x->left = allocator++;
      x->left->lo = x->lo; 
      x->left->hi = mid;
      tree_build( x->left );

      x->right = allocator++;
      x->right->lo = mid+1; 
      x->right->hi = x->hi;
      tree_build( x->right );

      x->join();
   }
}

int A, B;
int ret;

void tree_query( Interval *x ) {
   if( x->lo > B || x->hi < A ) return;
   if( A <= x->lo && x->hi <= B ) {
      for( int i = 0; i < 10; ++i ) ret += i * x->freq[i];
      x->rotate( 1 );
   } else {
      x->split();
      tree_query( x->left );
      tree_query( x->right );
      x->join();
   }
}

int main( void ) {
   int n, m;

   scanf( "%d%d ", &n, &m );
   gets( start );

   Interval *root = allocator++;
   root->lo = 0;
   root->hi = n-1;

   tree_build( root );
   
   for( int i = 0; i < m; ++i ) {
      scanf( "%d%d", &A, &B ); --A; --B;
      
      ret = 0;
      tree_query( root );      
      printf( "%d\n", ret );
   }

   return 0;
}
