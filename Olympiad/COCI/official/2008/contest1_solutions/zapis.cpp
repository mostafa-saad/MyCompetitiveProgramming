#include <cstdio>
#include <cstring>

#define MAX 200
#define MOD 100000

int n;
char s[MAX+1];

typedef long long llint;

char *otvorena  = "([{";
char *zatvorena = ")]}";

llint mod( llint a ) {
   if( a >= MOD ) return MOD + a%MOD;
   return a;
}

llint memo[MAX][MAX];

llint rec( int lo, int hi ) {
   if( lo > hi ) return 1;
   
   llint &ret = memo[lo][hi];
   if( ret >= 0 ) return ret;

   ret = 0;
   for( int mid = lo+1; mid <= hi; mid += 2 )
      for( int tip = 0; tip < 3; ++tip ) 
         if( s[lo] == otvorena[tip] || s[lo] == '?' )
            if( s[mid] == zatvorena[tip] || s[mid] == '?' )
               ret = mod( ret + rec(lo+1,mid-1) * rec(mid+1,hi) );

   return ret;
}

int main( void ) {
   scanf( "%d", &n );
   scanf( "%s", s );

   memset( memo, -1, sizeof memo );
   llint ret = rec( 0, n-1 );

   if( ret < MOD ) printf( "%lld\n", ret );
   else printf( "%05lld\n", ret-MOD );

   return 0;
}
