/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gazb4.c                                                    *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie niepoprawne i za wolne. Miotla (N^2),          *}
{*            Y-struktura na tablicy. B³ad: sumaryczna d³ugosc           *}
{*            przechowywana w int, zamiast w long long.                  *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct punkt{
  int x;
  int y;
  int zrodlo;
  int numer;
};
void punkt_wypisz(struct punkt *p){
  printf("x: %d; y: %d; zrodlo: %d; nr:%d\n", p->x,p->y,p->zrodlo, p->numer);
  return;
}

int cmp1(const void *p1, const void *p2) {
  struct punkt P1 = *(struct punkt *)p1;
  struct punkt P2 = *(struct punkt *)p2;

  if(P1.x > P2.x) return 1;
  if(P1.x == P2.x){
    if(P1.y < P2.y) return 1;
    if(P1.y == P2.y) return 0;
  }
  return -1;
}

const int MAX_N = 50005;
const int MAX_SIZE = 100005;

int tab[50001][2];
int tabCount = 0;

void tab_add(int y, int nr){
  tab[tabCount][0] = nr;
  tab[tabCount][1] = y;
  tabCount++;
  return;
}

int tab_findAndRemove(int min){
  int i;
  int curMin = -1;
  for(i = 0; i < tabCount; i++){
    if(tab[i][1] >= min && (curMin == -1 || tab[i][1] < tab[curMin][1]))
      curMin = i;
  }
  tab[curMin][1] = -1;
  return tab[curMin][0];
}

int main(){

//wczytaj
  int N;
  int n;
  struct punkt V[2*MAX_N];
  struct punkt copyV[2*MAX_N];

  scanf("%d", &N);
  for(n = 0; n < N; n++){
    scanf("%d %d", &V[n].x, &V[n].y);
    copyV[n].x = V[n].x;
    copyV[n].y = V[n].y;
    copyV[n].zrodlo = V[n].zrodlo = 1;
    copyV[n].numer = V[n].numer = n+1;
  }
  for(n = N; n < 2*N; n++){
    scanf("%d %d", &V[n].x, &V[n].y);
    copyV[n].x = V[n].x;
    copyV[n].y = V[n].y;
    copyV[n].zrodlo = V[n].zrodlo = 0;
    copyV[n].numer = V[n].numer = n-N+1;
  }
  qsort(V,2*N,sizeof(struct punkt), cmp1);

//dla kazdego elementu z V (po kolei): 
// jesli v jest zrodlem to dodaj do tablicy
// jesli v jest ujsciem to dodaj do wyniku pare (upper_bound(v),v);
//     usun z S upper_bound(v)
//     dodaj do wyniku odleglosc miedzy up_b(v) i v
 
  int W[MAX_N][2];
  int wCount = 0;
  int k;
  for(k = 0; k < 2*N; k++){
    if(V[k].zrodlo){
      tab_add(V[k].y,V[k].numer);
    }
    else{
      int nr = tab_findAndRemove(V[k].y);

      W[wCount][0] = nr; 
      W[wCount][1] = V[k].numer;
      wCount++;
    }
  }
  int odl = 0;
  for(n = 0; n < N; n++){
    odl += abs(copyV[W[n][0]-1].x - copyV[W[n][1]-1+N].x) + abs(copyV[W[n][0]-1].y - copyV[W[n][1]-1+N].y);
  }
  printf("%d\n", odl);
  for(n = 0; n < N; n++){
    printf("%d %d\n", W[n][0], W[n][1]);
  }

  return 0;
}
