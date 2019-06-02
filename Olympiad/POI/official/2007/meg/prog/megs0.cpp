/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    megs0.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Program poprawny, ale za wolny: dla kazdej krawedzi w      *}
{*            drzewie pamietamy, czy jest ona droga czy autostrada i za  *}
{*            kazdym razem sprawdzamy wszystkie krawedzie do wioski 1    *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>

#define MAXN 250000

int par[MAXN+1];
int is_road[MAXN+1]; //czy droga do ojca jeszcze nie zostala autostrada
int n; //liczba wiosek

void read_input() {
  int a,b;

  scanf("%d ",&n);
  for(int i=1; i<=n; i++) is_road[i]=1;
  for(int i=1; i<n; i++) {
    scanf("%d %d ", &a, &b);
    par[b]=a;
  }
}

int count_roads(int vertex) {
  int act=0;
  while (vertex!=1) {
    act+=is_road[vertex];
    vertex=par[vertex];
  }
  return act;
}

int main() {
  read_input();
  
  char z;
  int m,a,b;
  scanf("%d ", &m);
  for (int i=1; i<=n+m-1; i++) {
    scanf("%c ", &z);
    if (z=='A') {
     scanf("%d %d ", &a, &b);
     if (a>b) b=a;
     is_road[b]=0; //zamiana drogi z b do ojca na autostrade
    }
    else{
     scanf("%d ", &a);
     printf("%d\n", count_roads(a));
    }
  }
  
  return 0;
}
