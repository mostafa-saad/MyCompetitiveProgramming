/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                lusb2.cpp                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Niewyszukana heurystyka: ogolnie zwraca        *
 *                        x-1,y-1,z-1 chyba ze przypadkiem ktores dwa    *
 *                        sa rowne, wowczas zwraca x i x-1 zamiast       *
 *                        dwukrotnie x-1, jesli x=y=z, to zwraca         *
 *                        x,x-1,x-2.                                     *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
int main(void)
{
  int d, x, y, z;
  scanf("%d", &d);
  while (d--) {
    scanf("%d%d%d", &x, &y, &z);
    if (x == y) {
      if (y == z)
        printf("%d %d %d\n", x - 2, x - 1, x);
      else
        printf("%d %d %d\n", x, x - 1, z - 1);
    }
    
    else {
      if (y == z)
        printf("%d %d %d\n", x - 1, y, y - 1);
      else {
        if (x == z)
          printf("%d %d %d\n", x, y - 1, x - 1);
        else
          printf("%d %d %d\n", x - 1, y - 1, z - 1);
      }
    }
  }
  return 0;
}
