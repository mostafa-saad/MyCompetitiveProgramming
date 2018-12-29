/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tets6.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie za wolne.                          *
 *                        Kolejny klocek sprawdza ze wszystkimi          *
 *                        poprzednimi, czy sie nie pokrywa. Z heurystyka:*
 *                        wyrzucamy ze stosu rzeczy te, co przykrylismy  *
 *                        nowym w calosci.                               *
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
int ile; /* Ile jest teraz dobrych klockow */

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
  int i,j,wynik,nr;

  wynik = 0;
  scanf("%d%d%d",&w,&h,&n);
  for (i=0;i<n;++i){
    scanf("%d%d%d%d%d",&(k[ile].c),&(k[ile].d), &(k[ile].w), &(k[ile].a), &(k[ile].b));
    k[ile].c += k[ile].a; k[ile].d += k[ile].b;
    k[ile].wys = 0;
    nr = 0;
    for (j=0;j<ile;++j){
      if (czy_przecina(ile,j))
        AKT(k[ile].wys, k[j].wys);
      /* Czy przykrylismy w calosci? */
      if (! (k[ile].a <= k[j].a && k[j].c <= k[ile].c && k[ile].b <= k[j].b && k[j].d <= k[ile].d)){
        k[nr].a = k[j].a;
        k[nr].b = k[j].b;
        k[nr].c = k[j].c;
        k[nr].d = k[j].d;
        k[nr].w = k[j].w;
        k[nr].wys = k[j].wys;
        nr++;
      }
    }
    k[ile].wys += k[ile].w;
    AKT(wynik, k[ile].wys);
    k[nr].a = k[ile].a;
    k[nr].b = k[ile].b;
    k[nr].c = k[ile].c;
    k[nr].d = k[ile].d;
    k[nr].w = k[ile].w;
    k[nr].wys = k[ile].wys;
    nr++;
    ile = nr;
  }
  printf("%d\n",wynik);
  return 0;
}


