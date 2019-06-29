/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kols0.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie za wolne, zlozonosc O(n^3).                    *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>
#include <stdlib.h>

const int N=1000; //max. liczba wierzch.
const int M=1000000; //max. liczba kraw.
const int INF=1000000000; //liczba wieksza niz max koszt N krawedzi

struct edge{
  int from, to, cost;
};

int n,m; //liczba wierzcholkow i krawedzi
int edges[N+1][N+1]; //tablica najkrotszych sciezek
int prev[N+1][N+1]; //tablica nastepnikow do sciezek
int used[N+1][N+1]; //czy dana krawedz zostala uzyta(1-tak,0-nie)
edge e[N*(N-1)/2]; //sciezki, posortowane zwn. dlugosc
int stays[N+1]; //czy wierzcholek musi pozostac (1-tak/0-nie)
int st; //ile wierzcholkow ma zostac
int conn[N+1]; //numer rodzica wierzcholka w drzewie find-union skladowych
int cost=0, cnt=0;    //laczny koszt, liczba uzytych krawedzi
int left; //ile jest rozlacznych 'czarnych' skladowych

/************************ wejscie / wyjscie *************************/

void input() {
  int v1,v2,c;
  scanf("%d %d ",&n,&m);
  if (n>N) while (true) ;//i tak sie nie zmiesci w czasie i w pamieci
  for (int i=1; i<=n; i++)
    for (int j=1; j<=n; j++) {
      edges[i][j]=INF;
      prev[i][j]=-1;
    }
  for (int i=1; i<=n; i++) {
    edges[i][i]=0;
    prev[i][i]=i;
  }
  for (int i=0; i<m; i++) {
    scanf ("%d %d %d ",&v1,&v2,&c);
    edges[v1][v2]=c;
    prev[v1][v2]=v2;
    edges[v2][v1]=c;
    prev[v2][v1]=v1;
  }
  scanf("%d ", &st); //ile wierzcholkow pozostaje
  for (int i=1; i<=n; i++) stays[i]=0;
  for (int i=0; i<st; i++) {
    scanf("%d ",&v1);
    stays[v1]=1;
  }
}

void write() {
    printf("%d %d\n", cost, cnt);
    for(int i=1;i<=n;i++) 
      for (int j=i+1;j<=n;j++) 
        if (used[i][j]==1) printf("%d %d\n", i,j);
}

/******************************************************************/

int find(int a) {
    if (conn[a]==-1) return a;
    else {
    conn[a] = find(conn[a]);
    return conn[a];
    }
}

void connect(int a, int b) {
    conn[find(a)]=find(b);
}

void min_dist() {
  for (int k=1; k<=n; k++)
    for (int i=1; i<=n; i++)
      for (int j=1; j<=n; j++)
        if (edges[i][k]+edges[k][j]<edges[i][j]) {
          edges[i][j]=edges[i][k]+edges[k][j];
          prev[i][j]=prev[i][k];
        }
}

int comp(const void *a, const void *b) {
    return ((edge*)a)->cost -  ((edge*)b)->cost;
}

void add_path(int v1, int v2) {
  if (v1==v2) return;
  int k =prev[v1][v2];
  if (k==-1) return; //nie ma sciezki
  if (used[v1][k]==0) {
    used[v1][k]=1;
    used[k][v1]=1;
    cost+=edges[v1][k];
    cnt++;
  }
  add_path(k,v2);
}

void find_tree() {
  int act=0;
  for (int i=1; i<=n; i++)
    for (int j=i+1; j<=n; j++) 
      if (stays[i]==1 && stays[j]==1) {
          e[act].from=i;
          e[act].to=j;
          e[act].cost=edges[i][j];
          act++;
        }
  qsort(e, act, sizeof(edge), comp);
  left=st-1;
  for (int i=1; i<=n; i++) conn[i]=-1;
  for (int i=1; i<=n; i++) for(int j=1;j<=n;j++) used[i][j]=0;
  for (int i=0;i<act;i++) {
    int v1 = e[i].from, v2 = e[i].to, c = e[i].cost;
    if (find(v1)!=find(v2)) {
        connect(v1,v2);
            add_path(v1,v2);
            left--;
            if(left==0) return;
    }
    }
}

int main() {
  input(); //wczytanie krawedzi
  if (st==1) {printf("%d %d\n", 0, 0); return 0;}
  min_dist(); //obliczenie min. odl. miedzy kazda para wierzchoklow
  find_tree(); //znalezienie drzewa rozpinajacego
  write();
  return 0;
}
