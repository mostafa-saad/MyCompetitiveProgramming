/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Egzamin na prawo jazdy (EGZ)                               *}
{*   Plik:    egz3.c                                                     *}
{*   Autor:   Michal Brzozowski                                          *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000
int n,m,p,k;
typedef struct {
  int num,wys,zbud;
} droga;
droga ul[2][MAXN];
int ile[2];
int zbud[2][MAXN];

int cmp(const void *a, const void *b){
  droga *x=(droga *)a, *y=(droga *)b;
  if (x->num<y->num || ((x->num==y->num)&&(x->wys<y->wys))) return -1;
  return 1;

}

void podciag(int d){
  int l=0,i;
  int m[MAXN+1];
  qsort(ul[d],ile[d],sizeof(droga),cmp);
  for (i=0;i<=MAXN;++i) m[i]=0;
  for (i=0;i<ile[d];++i){
    int a=1,b=l+1;
    while (a<b) {
      int c=(a+b)/2;
      if (ul[d][m[c]].wys<ul[d][i].wys) b=c; else a=c+1;
    }
    if (a>0) --a;
    if (a==l || ul[d][i].wys>=ul[d][m[a+1]].wys){
      m[a+1]=i;
      if (l<a+1) l=a+1;
    }
    ul[d][i].zbud=ul[d][i].num-l;
    if (ul[d][i].zbud<zbud[d][ul[d][i].num]) zbud[d][ul[d][i].num]=ul[d][i].zbud;
  }
  for (i=1;i<n;++i)
    if (zbud[d][i]>zbud[d][i-1]+1) zbud[d][i]=zbud[d][i-1]+1;
}

int main(){
  int i,l,wyn;
  ile[0]=ile[1]=0;
  scanf("%d%d%d%d",&n,&m,&p,&k);
  for (i=0;i<p;++i){
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if (c==1){
      ul[0][ile[0]].num=a;
      ul[0][ile[0]].wys=b;
      ul[0][ile[0]].zbud=a-1;
      ++ile[0];
    } else {
      ul[1][ile[1]].num=n-a;
      ul[1][ile[1]].wys=b;
      ul[1][ile[1]].zbud=n-a-1;
      ++ile[1];
    }
  }
  for (i=0;i<n;++i) zbud[0][i]=zbud[1][i]=i;
  podciag(0);
  podciag(1);
  for (i=0;i<=(n-1)/2;++i) {
    int t;
    t=zbud[1][i];
    zbud[1][i]=zbud[1][n-i-1];
    zbud[1][n-i-1]=t;
  }
  l=n-1;
  while (zbud[1][0]+zbud[0][l]>k && l>0) --l;
  if (zbud[1][0]+zbud[0][l]<=k) wyn=l+1; else wyn=0;
  for (i=0;i<n;++i) 
    while (l<n-1 && zbud[1][i]+zbud[0][l+1]<=k){
      ++l;
      if (l-i+1>wyn) wyn=l-i+1;
    }
  for (i=0;i<n;++i)
    if (zbud[0][i]==0 && zbud[1][i]==0) --wyn;
  printf("%d\n",wyn);
  return 0;
}
