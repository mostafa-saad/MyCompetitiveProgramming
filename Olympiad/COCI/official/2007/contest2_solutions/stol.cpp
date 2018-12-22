
/*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak STOL
  Programski jezik C++

  Pretpostavimo jednu dimenziju stola. Konkretno, pretpostavimo da se
  stol proteze od stupca s1 do stupca s2. Da bi se stol mogao nalaziti
  u nekom retku, moraju sva polja tog retka izmedu stupaca s1 i s2
  biti prazna.

  Za svaki red moguce je utvrditi postoji li neki zid izmedu stupaca
  s1 i s2 u konstantnom vremenu: na pocetku za svaki stupac nekog reda
  izracunamo koliko se zidova nalazi lijevo od njega i to sapisemo u
  matricu suma[red][stupac]. Nakon sto smo to izracunali, izraz
  suma[red][s2] - suma[red][s1-1] ce nam reci koliko je zidova izmedu
  stupaca s1 i s2 (ako je on nula, stol se moze nalaziti u promatranom
  retku).

  Jednostavnim algoritmom nademo najveci uzastopni niz redova koji
  nemaju zidova izmedu s1 i s2 i time smo dobili maksimalno rjesenje
  za pocetnu pretpostavku. Isprobamo sve pretpostavke i izaberemo onu
  koja nam daje maksimalno rjesenje.

  Broj pretpostavki proporcionalan je s N^2. Koristenjem strukture
  podataka koja u konstantnom vremenu odgovara na pitanje nalazi li se
  neki zid u nekom retku izmedu dvaju stupaca provjeru radimo u
  linearnom vremenu, sto daje ukupno N^3.
*/

#include <algorithm>
#include <cstdio>

using namespace std;

#define MAXN 400

int main()
{
   int r, s;
   scanf( "%d%d", &r, &s );

   static char ploca[MAXN][MAXN+1];
   for ( int i=0; i<r; ++i )
      scanf( "%s", ploca[i] );

   static int sum[MAXN][MAXN+1];
   for ( int i=0; i<r; ++i ) {
      sum[i][0] = 0;
      for ( int j=1; j<=s; ++j )
         sum[i][j] = sum[i][j-1] + ( ploca[i][j-1] == 'X' );
   }

   int rez = 0;
   for ( int s1=1; s1<=s; ++s1 )
      for ( int s2=s1; s2<=s; ++s2 ) {
         int sad = 0, najdulje = 0;
         for ( int i=0; i<r; ++i ) {
            if ( sum[i][s2] - sum[i][s1-1] == 0 ) {
               if ( ++sad > najdulje ) {
                  najdulje = sad;
               }
            }
            else {
               sad = 0;
            }
         }

         if ( najdulje > 0 ) {
            rez = max( rez, 2*najdulje + 2*(s2-s1+1) );
         }
      }

   printf( "%d\n", rez-1 );

   return 0;
}
