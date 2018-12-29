/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    megs1.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Program poprawny, ale za wolny: dla kazdego wierzcholka    *}
{*            trzymamy jego aktualna odleglosc od wioski numer 1         *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>

#define MAXN 250000

int first_son[MAXN+1];
int next_brother[MAXN+1];
int act_depth[MAXN+1];

int n;

void read_input() {
  scanf("%d ", &n);
  for (int i=1; i<=n; i++) {
    first_son[i]=0;
    next_brother[i]=0;
  }
  int a,b;
  for (int i=1; i<n; i++) {
    scanf("%d %d ", &a, &b);
    next_brother[b]=first_son[a];
    first_son[a]=b;
  }  
}

void count_depth(int vertex, int value) {
  act_depth[vertex]=value;
  int son = first_son[vertex];
  while (son != 0) {
    count_depth(son, value+1);
    son = next_brother[son];
  }
}

void change_road(int vertex) {
  act_depth[vertex]--;
  int son = first_son[vertex];
  while (son != 0) {
    change_road(son);
    son = next_brother[son];
  }
}

int main() {
  read_input();
  count_depth(1,0);
  
  int m,a,b;
  char z;
  scanf("%d ", &m);
  for (int i=1; i<=m+n-1; i++) {
    scanf("%c ",&z);
    if (z=='A') {
      scanf("%d %d ", &a, &b);
      if (a>b) b=a;
      change_road(b);
    }
    else {
      scanf("%d ", &a);
      printf("%d\n", act_depth[a]);
    }
  }
  return 0;
}
