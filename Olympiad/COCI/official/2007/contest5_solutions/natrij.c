
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task NATRIJ
  Programming language C
*/

#include <stdio.h>

int main()
{
   int h1, m1, s1;
   int h2, m2, s2;
   int sekundi;
   scanf( "%d:%d:%d", &h1, &m1, &s1 );
   scanf( "%d:%d:%d", &h2, &m2, &s2 );

   sekundi = (h2-h1)*60*60 + (m2-m1)*60 + s2-s1;
   if ( sekundi <= 0 ) sekundi += 24*60*60;
   printf( "%02d:%02d:%02d\n", sekundi/60/60, sekundi/60%60, sekundi%60 );

   return 0;
}
