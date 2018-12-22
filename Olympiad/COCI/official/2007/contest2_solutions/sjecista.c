
/*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak SJECISTA
  Programski jezik C

  Oznacimo vrhove poligona od 0 do N-1 u smjeru kazaljke na satu.
  Promotrimo dijagonalu iz vrha 0 do nekog vrha i. Vrhovi od 1 do i-1
  nalaze se s jedne strane, a vrhovi od i+1 do N-1 s druge strane
  dijagonale. Promatranu dijagonalu sijeku samo one dijagonale kojima
  se jedna tocka nalazi s jedne, a druga tocka s druge strane
  promatrane dijagonale i njih ima (i-1) * (N-1-i).

  Koristeci to saznanje izbrojimo sva sjecista na dijagonalama iz
  tocke 0, te dobiveni broj pomnozimo s brojem vrhova n (jer smo mogli
  bilo koji vrh oznaciti kao vrh 0, a dobili bismo jednak
  rezultat). Time smo sjecista na svakoj dijagonali ubrojili dvaput
  (po jednom iz oba vrha), a time svako sjeciste tocno cetiri puta
  (buduci da se svako sjeciste nalazi na dvije dijagonale). Dakle,
  potrebno je dobiveni broj podijeliti s 4.
*/

#include <stdio.h>

int main()
{
   int rez, i, n;

   scanf("%d", &n);

   rez = 0;
   for (i=2; i<n-1; i++) {
      rez += (i-1)*(n-1-i);
   }
   rez *= n;
   rez /= 4;
   printf("%d\n", rez);

   return 0;
}
