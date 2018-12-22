
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task TENIS
  Programming language C
*/

#include <stdio.h>
#include <string.h>

int provjeri_jedan_set( int g1, int g2, int koji_set, const char *ime1, const char *ime2, int pob[2] )
{
   if ( g1 == g2 ) return 0;

   if ( g1 < g2 ) {
      int t; const char *p;

      t = g1; g1 = g2; g2 = t;
      p = ime1; ime1 = ime2; ime2 = p;
      ++pob[1];
   }
   else
      ++pob[0];

   if ( strcmp( ime2, "federer" ) == 0 ) return 0;

   if ( g1 < 6 ) return 0;
   if ( g1 == 6 ) return g2 <= 4;
   if ( g1 == 7 && koji_set < 3 ) return g2 == 5 || g2 == 6;
   if ( g1 >= 7 && koji_set == 3 ) return g1 == g2+2;
   return 0;
}

int main()
{
   char ime1[21], ime2[21];
   int n, i;
   scanf( "%s%s", ime1, ime2 );
   scanf( "%d\n", &n );

   for ( i=0; i<n; ++i ) {
      int ok = 1;
      char red[100];
      char *p = red;
      int pob[2] = { 0, 0 };
      int koji_set, g1, g2, ucitano;

      fgets( red, sizeof red, stdin );

      for ( koji_set=1; sscanf( p, "%d:%d%n", &g1, &g2, &ucitano ) == 2; ++koji_set ) {
         p += ucitano;
         ok &= pob[0] < 2 && pob[1] < 2;
         ok &= provjeri_jedan_set( g1, g2, koji_set, ime1, ime2, pob );
      }
      ok &= pob[0] == 2 || pob[1] == 2;

      puts( ok ? "da" : "ne" );
   }

   return 0;
}
