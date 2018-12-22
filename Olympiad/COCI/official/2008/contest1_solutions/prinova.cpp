#include <cstdio>

int n;
int p[100];
int A, B;
int rjesenje;

int abs( int x ) { return x < 0 ? -x : x; }

int racunaj( int x ) {
   if( x%2 == 0 ) return 0;

   int ret = 1000000000;
   for( int i = 0; i < n; ++i ) 
      ret <?= abs( x-p[i] );
   return ret;
}

void probaj( int x ) {
   if( x < A || x > B ) return;

   if( racunaj( x ) > racunaj( rjesenje ) ) rjesenje = x;   
}


int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) scanf( "%d", &p[i] );
   scanf( "%d%d", &A, &B );

   rjesenje = 0;

   probaj( A ); 
   probaj( A+1 );
   probaj( B ); 
   probaj( B-1 );

   for( int i = 0; i < n; ++i ) 
      for( int j = i+1; j < n; ++j ) {
         probaj( (p[i]+p[j])/2-1 );
         probaj( (p[i]+p[j])/2 );
         probaj( (p[i]+p[j])/2+1 );
      }

   printf( "%d\n", rjesenje );

   return 0;
}
