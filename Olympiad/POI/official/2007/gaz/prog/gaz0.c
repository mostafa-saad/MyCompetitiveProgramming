/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gaz0.c                                                     *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie wzorcowe. Miotla (NlogN), Y-struktura na       *}
{*            statycznym drzewie przedzialowym                           *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DB 0

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

//drzewo statyczne:

struct staticTreeNode{
  int leaf;
  int left; int right;
  struct lista *L;
};
#define staticTreeSize  (1<<(17+1))

//korzen drzewa:
struct staticTree{
  struct staticTreeNode t[2*staticTreeSize]; //t[0] nie zdefiniowane
};

//inicjacja
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

//dodaj do T nowy nr na pozycji y
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


//wypisz drzewo
void staticTree_print(struct staticTree *T){
  int s;
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

//funkcja porownujaca do sortowania X-struktury
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
  struct punkt copyV[2*MAX_N]; //kopia. Rozrzutnie!

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
//Sortujemy V, zeby dostac X-strukture.
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
//     usun z S upper_bound(v)
//     dodaj do wyniku odleglosc miedzy up_b(v) i v
 
  int W[MAX_N][2];//wynik
  int wCount = 0;//i wyniku
  int k;
  for(k = 0; k < 2*N; k++){
    if(V[k].zrodlo){
      staticTree_add(&T,V[k].y,V[k].numer);
    }
    else{
      int nr = staticTree_findAndRemove(&T,V[k].y);
      W[wCount][0] = nr; 
      W[wCount][1] = V[k].numer;
      wCount++;
    }
  }
  //zsumuj dlugosci
  long long odl = 0;
  for(n = 0; n < N; n++){
    odl += abs(copyV[W[n][0]-1].x - copyV[W[n][1]-1+N].x) + abs(copyV[W[n][0]-1].y - copyV[W[n][1]-1+N].y);
  }
  //wypisz wynik
  printf("%lld\n", odl);
  for(n = 0; n < N; n++){
    printf("%d %d\n", W[n][0], W[n][1]);
  }

  return 0;
}
