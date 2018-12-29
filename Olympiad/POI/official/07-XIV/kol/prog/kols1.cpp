/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kols1.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie za wolne, zlozonosc wykladnicza.               *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>
#include<stdlib.h>

const int N=1000; //max. liczba wierzch.
const int M=1000000; //max. liczba kraw.
const int INF=1000000000; //liczba wieksza niz max koszt N krawedzi

struct edge {
    int u,v,c;
};

int n,m; //wierzcholki,krawedzie
edge e[M];
int stays[N+1]; //czy wierzcholek musi pozostac (1-tak/0-nie)
int st; //ile wierzcholkow ma zostac
int not_obligatory[N+1]; //numery wierzcholkow, ktore nie musza byc w drzewie
int act_vertices; //akt. liczba wierzcholkow
int cnt, min_cnt, cost, min_cost;
int used[M], min_used[M]; //numery uzytych krawedzi
int conn[N]; //numer rodzica wierzcholka w drzewie find-union skladowych


int comp(const void *a, const void *b) {
    return ((edge*)a)->c -  ((edge*)b)->c;
}

void input() {
  scanf("%d %d", &n, &m);
  if (n>N) while (true) ; //i tak sie nie zmiesci w czasie i pamieci
  for (int i=1;i<=n;i++) stays[i]=0;
  for (int i=0;i<m;i++) scanf("%d %d %d ", &(e[i].u), &(e[i].v), &(e[i].c));
  scanf("%d ", &st);
  int tmp;
  for (int i=0;i<st;i++) { scanf("%d ", &tmp); stays[tmp]=1; }
  tmp=0;
  for (int i=1;i<=n;i++) if (stays[i]==0) {not_obligatory[tmp]=i; tmp++;}
  act_vertices=st;
}

//generuje nastepny podzbior, 1-ok/0-koniec
int next_subset() {
  int tmp=0;
  while (tmp<n-st && stays[not_obligatory[tmp]]==2) {stays[not_obligatory[tmp]]=0; tmp++; act_vertices--;}
  if (tmp>=n-st) return 0;//koniec
  stays[not_obligatory[tmp]]=2;
  act_vertices++;
  return 1;
}

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

void go() {
  int left;
  min_cost=INF;
  min_cnt=0;
  while (true) {
    for (int i=1;i<=n;i++) conn[i]=-1;
    cnt=0;
    cost=0;
    left=act_vertices-1;
    for (int i=0;i<m;i++) {
    int u = e[i].u, v = e[i].v, c = e[i].c;
    if (stays[u]!=0 && stays[v]!=0 && find(u)!=find(v)) {
        connect(u,v);
        used[cnt]=i;
        cnt++;
        cost+=c;
            left--;
//            if (left==0) break;
    }
    }
    //czy to bylo optymalne rozwiazanie (o ile bylo)
    if (left==0 && cost<min_cost) {
      min_cost=cost;
      min_cnt=cnt;
      for(int i=0;i<cnt;i++) min_used[i]=used[i];
    }
    //kolejny krok
    if (next_subset()==0) return;
  }
}

void write() {
    printf("%d %d\n", min_cost, min_cnt);
    for(int i=0;i<min_cnt;i++) printf("%d %d\n", e[min_used[i]].u, e[min_used[i]].v);
}

int main() {
  input();
  if (st==1) {printf("%d %d\n", 0, 0); return 0;}
  qsort(e, m, sizeof(edge), comp);
  go();
  write();
  return 0;
}
