#include <algorithm>
#include <cstdio>

using namespace std;

const int inf = 1000000000;

struct skakavac {
   short r, c;
   int val;
   int dp;
} niz[1500*1500+1];
bool operator < ( const skakavac &A, const skakavac &B ) { return A.val > B.val; }

struct best4 {
   skakavac *best[4];

   void update( skakavac *S ) {
      for( int i = 3; i >= 0; --i ) {
         if( S->dp <= best[i]->dp ) break;

         if( i+1 < 4 ) best[i+1] = best[i];
         best[i] = S;
      }
   }

   int query( int r, int c ) {
      for( int i = 0; i < 4; ++i ) {
         if( abs(r-best[i]->r)<=1 && abs(c-best[i]->c)<=1 ) continue;
         return best[i]->dp;
      }
      return -inf;
   }
} R[1500], C[1500];

int n, r0, c0;

int main( void ) {
   scanf( "%d%d%d", &n, &r0, &c0 ); --r0; --c0;
   
   skakavac *next = niz;
   for( int i = 0; i < n; ++i ) {
      for( int j = 0; j < n; ++j ) {
         next->r = i;
         next->c = j;
         next->dp = 1;
         scanf( "%d", &next->val );
         ++next;
      }
   }
   next->r = -5; next->c = -5; next->dp = -inf;

   for( int i = 0; i < n; ++i ) 
      for( int j = 0; j < 4; ++j ) 
         R[i].best[j] = C[i].best[j] = next;   

   sort( niz, niz + n*n );

   for( int i = 0, j; i < n*n; i = j ) {
      for( j = i; j < n*n && niz[j].val == niz[i].val; ++j ) {
         skakavac *S = &niz[j];

         if( S->r-1 >= 0 ) niz[j].dp = max( niz[j].dp, 1+R[S->r-1].query( S->r, S->c ) );
         if( S->c-1 >= 0 ) niz[j].dp = max( niz[j].dp, 1+C[S->c-1].query( S->r, S->c ) );
         if( S->r+1 <  n ) niz[j].dp = max( niz[j].dp, 1+R[S->r+1].query( S->r, S->c ) );
         if( S->c+1 <  n ) niz[j].dp = max( niz[j].dp, 1+C[S->c+1].query( S->r, S->c ) );
      }

      for( j = i; j < n*n && niz[j].val == niz[i].val; ++j ) {
         skakavac *S = &niz[j];
         
         R[S->r].update( S );
         C[S->c].update( S );

         if( S->r == r0 && S->c == c0 ) printf( "%d\n", S->dp );
      }
   }
   

   return 0;
}
