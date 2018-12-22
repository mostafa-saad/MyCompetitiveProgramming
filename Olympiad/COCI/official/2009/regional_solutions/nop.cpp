#include <cctype>
#include <cstdio>
#include <cstring>

#define MAX 200

char prog[MAX+1];

int main( void ) {
   scanf( "%s", prog );
   int n = strlen( prog );

   int nop = 0;
   for( int i = 0; i < n; ++i ) {
      if( !isupper( prog[i] ) ) continue;

      while( (i+nop)%4 != 0 ) ++nop;
   }

   printf( "%d\n", nop );

   return 0;
}
