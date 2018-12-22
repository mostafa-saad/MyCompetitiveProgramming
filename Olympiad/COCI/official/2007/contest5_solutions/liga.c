
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task LIGA
  Programming language C
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ucitaj1()
{
   char buf[5];
   scanf( "%s", buf );
   if ( strcmp(buf, "?") == 0 )
      return -1;
   else
      return atoi(buf);
}

int main()
{
   int n, i;
   int a, b, c, d, e;
   scanf( "%d", &n );

   for ( i=0; i<n; ++i ) {
      int b1, b2, c1, c2;

      a = ucitaj1(); b = ucitaj1(); c = ucitaj1(); d = ucitaj1(); e = ucitaj1();

      if ( b != -1 ) b1 = b2 = b;
      else b1 = 0, b2 = 100;

      if ( c != -1 ) c1 = c2 = c;
      else c1 = 0, c2 = 100;

      if ( a == -1 && d == -1 ) d = 0;

      for ( b=b1; b<=b2; ++b )
         for ( c=c1; c<=c2; ++c ) {
            int ta=a, td=d, te=e;
            if ( a == -1 ) ta = b+c+d;
            else if ( d == -1 ) td = a-b-c;

            if ( e == -1 ) te = 3*b+c;

            if ( ta == b+c+td &&
                 ta >= 0 && ta <= 100 &&
                 td >= 0 && td <= 100 &&
                 te==3*b+c ) {
               printf( "%d %d %d %d %d\n", ta, b, c, td, te );
            }
         }
   }

   return 0;
}
