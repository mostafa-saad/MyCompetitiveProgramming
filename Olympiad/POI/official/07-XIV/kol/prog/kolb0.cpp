/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kolb0.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie niepoprawne.                                   *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N 5000
#define M 1000000

#define WHITE 0
#define BLACK 1

typedef struct Edge {
    int u,v,c;
};

Edge e[M];
int color[N];        //kolor wierzcholka
int conn[N];        //numer rodzica wierzcholka w drzewie find-union skladowych
int tchd[N];        //czy wierzcholek zostal uzyty
int used[M];        //numery uzytych krawedzi
int cost=0, cnt=0;    //laczny koszt, liczba uzytych krawedzi
int n,m,bl;

int comp(const void *a, const void *b) {
    return ((Edge*)a)->c -  ((Edge*)b)->c;
}

void read() {
    scanf("%d%d", &n, &m);
    for (int i=0;i<n;i++) color[i]=WHITE;
    for (int i=0;i<m;i++) scanf("%d%d%d", &(e[i].u), &(e[i].v), &(e[i].c));
    scanf("%d", &bl);
    int b;
    for (int i=0;i<bl;i++) { scanf("%d", &b); color[b]=BLACK; }
}

void write() {
    printf("%d %d\n", cost, cnt);
    for(int i=0;i<cnt;i++) printf("%d %d\n", e[used[i]].u, e[used[i]].v);
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

void seek() {
    for (int i=0;i<n;i++) conn[i]=-1, tchd[i]=0;
    for (int i=0;i<m;i++) {
    int u = e[i].u, v = e[i].v, c = e[i].c;
    if (find(u)!=find(v)) {
        connect(u,v);
        used[cnt]=i;
        cnt++;
        cost+=c;
        if (tchd[u]==0&&color[u]==BLACK) tchd[u]=1, bl--;
        if (tchd[v]==0&&color[v]==BLACK) tchd[v]=1, bl--;
        if (bl==0&&cnt==n-1) return;
    }
    }
}

int main() {
    read();
    qsort(e, m, sizeof(Edge), comp);
    seek();
    write();
    return 0;
}
