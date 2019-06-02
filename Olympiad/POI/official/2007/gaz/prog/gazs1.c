/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gazs1.c                                                    *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie za wolne. Edmonds-Karp                         *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DB 0

struct list{
  struct list *next;
  struct list *dual;
  int matched;
  int nr;
};

struct list* list_push(struct list *L, int v,int m){//zwraca wskaznik do zmodyfikowanej listy
  struct list *n = malloc(sizeof(struct list));
  n->nr = v;
  n->next = L;
  n->matched = m;
  L = n;
  return L;
}

struct list* list_pop(struct list *L){//zwraca wskaznik do zmodyfikowanej listy
  assert(L != NULL);
  struct list *n = L;
  L = L->next;
  free(n);
  return L;
}

void list_print(struct list *L){
  printf("[");
  struct list *n = L;
  while(n != NULL){
    printf("%d %d", n->nr, n->matched);
    if(n->next != NULL){
      printf(" ");
    }
    n = n->next;
  }
  printf("]\n");
}


struct vertex{
  int x;
  int y;
  int nr;
  struct list *nb;  //neighbours
};

void vertex_print(struct vertex *p){
  printf("x: %d; y: %d; nr:%d\n", p->x,p->y, p->nr);
  return;
}


const int MAX_X = 100000;
const int MAX_Y = 100000;
const int MAX_N = 50000;

int main(){
//wczytaj
  int N;
  int n;
  struct vertex L[2*MAX_N+2];

  scanf("%d", &N);
  int t = N+1;
  int s = 0;

  L[s].x = -1; L[s].y = MAX_Y+1; L[s].nr = 0;//s[ource]
  L[t].x = MAX_X+1; L[t].y = -1; L[t].nr = N+1;//t

  for(n = 1; n <= N; n++){
    scanf("%d %d", &L[n].x, &L[n].y);
    L[n].nr = n;

    L[s].nb = list_push(L[s].nb, L[n].nr,0);//s[ource]
    L[n].nb = list_push(L[n].nb, L[s].nr,1);
    L[s].nb->dual = L[n].nb;
    L[n].nb->dual = L[s].nb;
  }
  for(n = N+2; n < 2*N+2; n++){
    scanf("%d %d", &L[n].x, &L[n].y);
    L[n].nr = n;

    L[n].nb = list_push(L[n].nb, L[t].nr,0);//t
    L[t].nb = list_push(L[t].nb, L[n].nr,1);
    L[n].nb->dual = L[t].nb;
    L[t].nb->dual = L[n].nb;

    int k;
    for(k = 1; k <= N; k++){
      if(L[k].x <= L[n].x && L[k].y >= L[n].y){
        L[k].nb = list_push(L[k].nb,L[n].nr,0);
        L[n].nb = list_push(L[n].nb,L[k].nr,1);
        L[k].nb->dual = L[n].nb;
        L[n].nb->dual = L[k].nb;
      }
    }
  }
  int count = 0;
//  printf("N: %d\n\n",N);
  do{
    int Q[100010];  //queue;
    int prev[100010];
    struct list *prevEdges[100010];

    int i; for(i = 0; i < 100010; i++) prev[i] = Q[i] = -1;

    int pQ = 1;
    int lQ = 0;
    Q[0] = s;  //s[ource]
    prev[s] = 0;
    prevEdges[s] = NULL;
    int cur;
    do{
      assert(lQ < 100010);
      cur = Q[lQ++];
#if DB
      printf("cur: %d\n", cur);
#endif
      struct list *l;
      for(l = L[cur].nb; l != NULL; l = l->next){
        if(prev[l->nr] == -1 && l->matched == 0){
#if DB
        printf("%d ", l->nr);
#endif
          Q[pQ++] = l->nr;
          prev[l->nr] = cur;
          prevEdges[l->nr] = l;
        }
      }
#if DB
      printf("\n");
#endif
    }while(lQ < pQ && cur != t);

    if(cur == t){  //founded
#if DB
      printf("A\n");
#endif
      count++;
      //cur == t;
      while(cur != s){
        assert(prevEdges[cur] != NULL);
        prevEdges[cur]->matched = 1;
        prevEdges[cur]->dual->matched = 0;
        cur = prev[cur];
      }
    }
    else break;
  }while(1);
  assert(count == N);

  int i;
  long long sum = 0;    //oszczednosc pamieci...
  for(i = 1; i <= N; i++){
    struct list *l;
    for(l = L[i].nb; l != NULL; l = l->next){
      if(l->matched){
        sum += (L[l->nr].x - L[i].x) + (L[i].y - L[l->nr].y);
        break;
      }
    }
  }

  printf("%lld\n", sum);
  for(i = 1; i <= N; i++){
    struct list *l;
    for(l = L[i].nb; l != NULL; l = l->next){
      if(l->matched){
        printf("%d %d\n", i, l->nr - t);
        break;
      }
    }
  }
  return 0;
}
