/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tets1.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie za wolne.                          *
 *                        Kolejny klocek sprawdza ze wszystkimi          *
 *                        poprzednimi czy sie nie pokrywa.               *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int a,b; /* Lewy dolny rog */
  int c,d; /* Prawy gory rog */
  int w; /* Wysokosc klocka */
  int wys; /* Bezwzgledna wysokosc gory klocka */
} klocek;

klocek k[20000];
int n,w,h; /* Ilosc klockow, rozmiary planszy */

/* Czy klocki sie nachodza na siebie? */
int czy_przecina(int i,int j){
  if (k[i].a >= k[j].c || k[j].a >= k[i].c
      || k[i].b >= k[j].d || k[j].b >= k[i].d)
    return 0;
  else
    return 1;
}

/* Makro wybierajace wieksza z dwoch liczb i aktualizujace */
#define AKT(x,y) ((x)=(((x)>(y))?(x):(y)))

int main(void){
  int i,j,wynik;

  wynik = 0;
  scanf("%d%d%d",&w,&h,&n);
  for (i=0;i<n;++i){
    scanf("%d%d%d%d%d",&(k[i].c),&(k[i].d), &(k[i].w), &(k[i].a), &(k[i].b));
    k[i].c += k[i].a; k[i].d += k[i].b;
    k[i].wys = 0;
    for (j=0;j<i;++j)
      if (czy_przecina(i,j))
        AKT(k[i].wys, k[j].wys);
    k[i].wys += k[i].w;
    AKT(wynik, k[i].wys);
  }
  printf("%d\n",wynik);
  return 0;
}


