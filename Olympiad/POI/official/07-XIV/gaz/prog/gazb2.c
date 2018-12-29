/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gazb2.c                                                    *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie niepoprawne.                                   *}
{*            Rozwiazanie zachlanne; wybieram pierwsza z brzegu pare.    *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DB 0
#define DB2 0
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

struct lista{
  struct lista *next;
  int value;
};

struct lista* lista_push(struct lista *L, int v){//zwraca wskaznik do zmodyfikowanej listy
  struct lista *n = malloc(sizeof(struct lista));
  n->value = v;
  n->next = L;
  L = n;
  return L;
}

struct lista* lista_pop(struct lista *L){//zwraca wskaznik do zmodyfikowanej listy
  assert(L != NULL);
  struct lista *n = L;
  L = L->next;
  free(n);
  return L;
}

void lista_print(struct lista *L){
  printf("[");
  struct lista *n = L;
  while(n != NULL){
    printf("%d", n->value);
    if(n->next != NULL){
      printf(" ");
    }
    n = n->next;
  }
  printf("]\n");
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
    if(tab[i][1] >= min && (curMin == -1 || tab[i][1] < tab[curMin][1])){
      curMin = i;
      break;
    }
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
//  vector<punkt> B;
//  sort(B.begin(), B.end(),lt1());
//lt1: posortuj wszystko po x-ach; potem po tym czy jest zrodlem (wczesniej); potem po tym czy jest wyzej (wczesniej rozwazam te o wiekszym y-ku) V.
  qsort(V,2*N,sizeof(struct punkt), cmp1);
#if DB
  for( n = 0; n < 2*N; n++){
    punkt_wypisz(&V[n]);
  }
#endif
//stworz drzewo przedzialowe: T.


//dla kazdego elementu z V (po kolei): 
// jesli v jest zrodlem to dodaj do miotly
// jesli v jest ujsciem to dodaj do wyniku pare (upper_bound(v),v);
//     usun z S upper_bound(v): erase(ub(v),ub(v)
//     dodaj do wyniku odleglosc miedzy up_b(v) i v
 
  int W[MAX_N][2];
  int wCount = 0;
#if DB
  printf("\n\n");
#endif
  int k;
  for(k = 0; k < 2*N; k++){
    if(V[k].zrodlo){
      tab_add(V[k].y,V[k].numer);
    }
    else{
#if DB
      printf("szukam: %d; ", V[k].y); 
#endif
      int nr = tab_findAndRemove(V[k].y);
#if DB
      printf("znalazlem: %d\n", nr);
#endif

      W[wCount][0] = nr; 
      W[wCount][1] = V[k].numer;
#if DB
      printf("para: %d %d\n", nr, V[k].numer);
#endif
      wCount++;
    }
#if DB
//  staticTree_print(&T);
   #endif
  }
  long long odl = 0;
  for(n = 0; n < N; n++){
    odl += abs(copyV[W[n][0]-1].x - copyV[W[n][1]-1+N].x) + abs(copyV[W[n][0]-1].y - copyV[W[n][1]-1+N].y);
  }
  printf("%lld\n", odl);
  for(n = 0; n < N; n++){
    printf("%d %d\n", W[n][0], W[n][1]);
#if DB2
printf("%d\n", abs(copyV[W[n][0]-1].x - copyV[W[n][1]-1+N].x) + abs(copyV[W[n][0]-1].y - copyV[W[n][1]-1+N].y));
#endif
  }

  return 0;
}
