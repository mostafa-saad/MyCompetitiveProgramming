#include <cstdio>

#define MAXR 25
#define MAXS 25

int R, S;
char a[MAXR][MAXS+1];
int lijevo( int r, int s ) {
   return s >  0  && (a[r][s-1]=='+' || a[r][s-1]=='-' || a[r][s-1]=='1' || a[r][s-1]=='2');
}
int desno( int r, int s ) {
   return s < S-1 && (a[r][s+1]=='+' || a[r][s+1]=='-' || a[r][s+1]=='3' || a[r][s+1]=='4');
}
int gore( int r, int s ) {
   return r >  0  && (a[r-1][s]=='+' || a[r-1][s]=='|' || a[r-1][s]=='1' || a[r-1][s]=='4');
}
int dolje( int r, int s ) {
   return r < R-1 && (a[r+1][s]=='+' || a[r+1][s]=='|' || a[r+1][s]=='2' || a[r+1][s]=='3');
}

int main( void ) {
   scanf( "%d%d", &R, &S );
   for( int r = 0; r < R; ++r ) scanf( "%s", a[r] );

   for( int r = 0; r < R; ++r ) 
      for( int s = 0; s < S; ++s ) {
         if( a[r][s] != '.' ) continue;

         if( lijevo(r,s) && desno(r,s) && gore(r,s) && dolje(r,s) ) printf( "%d %d +\n", r+1, s+1 );
         else if( lijevo(r,s) && desno(r,s) ) printf( "%d %d -\n", r+1, s+1 ); 
         else if(   gore(r,s) && dolje(r,s) ) printf( "%d %d |\n", r+1, s+1 );
         else if(  desno(r,s) && dolje(r,s) ) printf( "%d %d 1\n", r+1, s+1 );
         else if(  desno(r,s) &&  gore(r,s) ) printf( "%d %d 2\n", r+1, s+1 );
         else if( lijevo(r,s) &&  gore(r,s) ) printf( "%d %d 3\n", r+1, s+1 );
         else if( lijevo(r,s) && dolje(r,s) ) printf( "%d %d 4\n", r+1, s+1 );

      }
   return 0;
}
