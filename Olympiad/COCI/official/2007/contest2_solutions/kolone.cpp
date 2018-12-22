
/*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak KOLONE
  Programski jezik C++

  Zadatak se moze rijesiti tako da sekundu po sekundu simuliramo
  preskakanja (vidi rjesenje u Pascalu za implementaciju).

  Efikasniji pristup je za svakog mrava izracunati na kojem ce
  se mjestu nalaziti.

  Neka se jedan mrav nalazi na poziciji i u svojoj koloni (pozicije
  brojimo od 0). Mozemo izracunati njegovu poziciju P u konacnom nizu
  u trenutku T=0: P=N1-i-1 za prvu (lijevu) kolonu i P=N1+i za drugu
  (desnu) kolonu.

  Razlikujemo 3 slucaja:
  1. Ako je broj sekundi T manji od i, tada mrav nece preskociti
     nijednog mrava te ce ostati na svojoj poziciji P.
  2. Ako je broj sekundi T veci od ili jednak i+(broj mrava u drugoj
     koloni), mrav ce preskociti sve mrave iz suprotne kolone (hoce li
     mu se pozicija smanjiti ili povecati ovisi o tome nalazi li se
     mrav s lijeve ili desne strane).
  3. U preostalom slucaju pozicija mrava promijenit ce se za (T-i)
     (takoder ovisno o strani).
*/

#include <algorithm>
#include <cstdio>

using namespace std;

int main()
{
   char k1[31], k2[31], rez[61];
   int n1, n2, t, P, i;

   scanf("%d%d", &n1, &n2);
   scanf("%s%s", k1, k2);
   scanf("%d", &t);

   for(i=0;i<n1;i++)
   {
      P = n1-i-1;
      P += min( max(t-i,0), n2 );
      rez[P] = k1[i];
   }
   for(i=0;i<n2;i++)
   {
      P = n1+i;
      P -= min( max(t-i,0), n1 );
      rez[P] = k2[i];
   }
   rez[n1+n2] = '\0';
   printf("%s\n",rez);

   return 0;
}
