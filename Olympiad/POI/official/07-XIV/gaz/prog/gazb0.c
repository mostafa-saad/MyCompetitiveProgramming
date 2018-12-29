/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gazb0.c                                                    *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie niepoprawne. Miotla (NlogN), Y-struktura na    *}
{*            statycznym drzewie przedzialowym                           *}
{*            blad: zamiast long longa w odpowiedzi sa tylko inty => zla *}
{*            dlugosc sumaryczna                                         *}
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

/*  bool operator==(punkt p1, punkt p2){
    return (p1.x == p2.x && p1.y == p2.y && p1.numer == p2.numer);
  }
ostream &operator<<(ostream &os, const punkt &m1){
  os <<"(x: "<<m1.x<<"; y: "<<m1.y<<"; zrodlo?: "<<m1.zrodlo<<"; nr: "<<m1.numer<<") ";
  return os;
}
*/

/*
struct ltMiotla{
  bool operator()(punkt m1, punkt m2) const{
    if(m1.y < m2.y) return true;
    if(m1.y == m2.y && m1.x > m2.x) return true;
    return false;
  }
};
*/

struct staticTreeNode{
  int leaf;
  int left; int right;
  struct lista *L;
};
#define staticTreeSize  (1<<(17+1))

struct staticTree{
  struct staticTreeNode t[2*staticTreeSize]; //t[0] nie zdefiniowane
};

void staticTree_initialize(struct staticTree *T){
  int s;
  for(s = 0; s < staticTreeSize/2; s++){
    T->t[s] =(struct staticTreeNode){0,0,0,0};
  }
  for(s = staticTreeSize/2; s < staticTreeSize; s++){
    T->t[s] =(struct staticTreeNode){1,0,0,0};
  }
  return;
};

void staticTree_add(struct staticTree *T, int y, int nr){
  y = y + (staticTreeSize/2);
  T->t[y].L = lista_push(T->t[y].L, nr);
  int cur = y/2;
  int prev = y;
  while(cur >= 1){
    if((prev & 1) == 1) T->t[cur].right++;
    else                T->t[cur].left++;
    prev = cur;
    cur /= 2;
  }
  return;
}

int staticTree_findAndRemove(struct staticTree *T, int min){
  //zwraca pierwsza z brzegu wartosc z listy odpowiadajacej elementowi tablicy >= min
  
  int cur = min+staticTreeSize/2;
  int prev = cur*2;
  int ret;
  if(T->t[cur].L == NULL){
#if DB
      printf("(cur: %d; left:%d; right:%d)\n", cur,T->t[cur].left, T->t[cur].right);
#endif
    while(cur >= 1){
      if(T->t[cur].right > 0 && prev == cur*2) break;
      prev = cur;
      cur /= 2;
#if DB
      printf("(cur: %d; left:%d; right:%d)\n", cur, T->t[cur].left, T->t[cur].right);
#endif
    }
    assert(cur > 0);
#if DB
    printf("cur: %d;%d\n", cur, T->t[cur].right);
#endif
    cur = cur*2+1;
#if DB
    printf("(cur: %d; left:%d; right:%d)\n", cur, T->t[cur].left, T->t[cur].right);
#endif

    while( ! (T->t[cur].leaf) ){
      if(T->t[cur].left > 0){
        cur = cur *2;
      }
      else{
        assert(T->t[cur].right > 0);
        cur = cur*2+1;
      }
#if DB
    printf("(cur: %d; left:%d; right:%d)\n", cur, T->t[cur].left, T->t[cur].right);
#endif
    }
  }
  assert(T->t[cur].L != NULL);
  ret = T->t[cur].L->value;
  T->t[cur].L = lista_pop(T->t[cur].L);

  prev = cur;
  cur /= 2;
  while( cur >= 1){
    if((prev % 2) == 1){ assert(T->t[cur].right >0); T->t[cur].right--;}
    else               { assert(T->t[cur].left > 0);  T->t[cur].left--;}
    prev = cur;
    cur /= 2;
  }

  return ret;
}

void staticTree_printF(struct staticTree *T){
  int s;
  for(s = 1; s < staticTreeSize/2; s++){
    if(((s - 1) & s) == 0){ //s jest potega 2
      printf("\n");
    }
    printf("(%d: left:%d; right:%d) ", s,T->t[s].left, T->t[s].right);
  }
  printf("\n");
  for(s = staticTreeSize-1; s >= staticTreeSize/2; s--){
    if(T->t[s].L == NULL) continue;
    printf("%d: ", s - staticTreeSize/2);
    lista_print(T->t[s].L);
  }
  printf("\n\n");
  return;
}

void staticTree_print(struct staticTree *T){
  int s;
/*  for(s = 1; s < staticTreeSize/2; s++){
    if(((s - 1) & s) == 0){ //s jest potega 2
      printf("\n");
    }
    printf("(left:%d; right:%d) ", T->t[s].left, T->t[s].right);
  }
  printf("\n");*/
  for(s = staticTreeSize-1; s >= staticTreeSize/2; s--){
    if(T->t[s].L == NULL) continue;
    printf("%d: ", s - staticTreeSize/2);
    lista_print(T->t[s].L);
  }
  printf("\n\n");
  return;
}


typedef struct staticTreeNode node;
typedef struct staticTree     tree;

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
  tree T;
  staticTree_initialize(&T);

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
      staticTree_add(&T,V[k].y,V[k].numer);
    }
    else{
#if DB
      printf("szukam: %d; ", V[k].y); 
      if(V[k].y == 11426){
      staticTree_printF(&T);
      }
#endif
      int nr = staticTree_findAndRemove(&T,V[k].y);
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
  staticTree_print(&T);
   #endif
  }
  int odl = 0;
  for(n = 0; n < N; n++){
    odl += abs(copyV[W[n][0]-1].x - copyV[W[n][1]-1+N].x) + abs(copyV[W[n][0]-1].y - copyV[W[n][1]-1+N].y);
  }
  printf("%d\n", odl);
  for(n = 0; n < N; n++){
    printf("%d %d\n", W[n][0], W[n][1]);
#if DB2
printf("%d\n", abs(copyV[W[n][0]-1].x - copyV[W[n][1]-1+N].x) + abs(copyV[W[n][0]-1].y - copyV[W[n][1]-1+N].y));
#endif
  }

  return 0;
}
