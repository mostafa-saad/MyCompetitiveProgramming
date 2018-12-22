#include <cstdio>

int dana_u_mjesecu[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
char *imena[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

int main( void ) {
   int dd, mm;
   scanf( "%d%d", &dd, &mm );
   
   int dan = 2 + dd;
   for( int m = 1; m < mm; ++m ) dan += dana_u_mjesecu[m];

   printf( "%s\n", imena[dan%7] );

   return 0;
}
