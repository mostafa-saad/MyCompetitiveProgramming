/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tets2.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie za wolne.                          *
 *                        Ma dana kratke 1000x1000 z wysokosciami        *
 *                        i za kazdym razem jak przychodzi nowy klocek   *
 *                        aktualizuje kratke.                            *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int k[1000][1000];

int n,w,h;

/* Makro wybierajace wieksza z dwoch liczb i aktualizujace */
#define AKT(x,y) ((x)=(((x)>(y))?(x):(y)))

int main(void){
  int i,j,a,b,c,d,w,akt,wynik;

  wynik = 0;
  scanf("%d%d%d", &w, &h, &n);
  while(n--){
    scanf("%d%d%d%d%d", &c, &d, &w, &a, &b);
    c+=a; d+=b;
    akt = 0;
    for (i=a; i<c; ++i)
      for (j=b; j<d; ++j)
        AKT(akt, k[i][j]);
    akt += w;
    for (i=a; i<c; ++i)
      for (j=b; j<d; ++j)
        k[i][j]=akt;
    AKT(wynik, akt);
  }
  printf("%d\n",wynik);
  return 0;
}

