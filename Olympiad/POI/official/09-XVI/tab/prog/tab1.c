/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tab1.c                                                    *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wzorcowe O(n*m+n*log n).                      *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (((a)<(b))?(a):(b))

#define N 1001
#define INF 2000000007
#define M 1000000

typedef struct{
  int wart,nr;
} para;

static int porpara(const void *p1, const void *p2)
{
  return ((para *)p1)->wart - ((para *)p2)->wart;
}


int t, n, m, tab[2][N][N], i, j, tmp[2*M+1];
/* tablice zawieraj± najmniejsze liczby z wierszy tablic a i b oraz numery odpowiadaj±cych wierszy*/
para tr[2][N];

int main()
{
  scanf("%d",&t);
  int tnr;
  for(tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    int nr;
    for(nr=0; nr<2; nr++){
      for(i=0; i<n; i++){
        int mel = INF;
        for(j=0; j<m; j++){ 
          scanf("%d",&tab[nr][i][j]);
          tab[nr][i][j]+=M;
          mel = min(mel,tab[nr][i][j]);
        }
        tr[nr][i].wart = mel;
        tr[nr][i].nr = i;
      }
      qsort(tr[nr], n, sizeof(para), porpara);
    }
    int pod = 1;
    for(i=0; i<n; i++)
      if(tr[0][i].wart != tr[1][i].wart)
        pod = 0;
    if(!pod){
      printf("NIE\n");
      continue;
    }
    /* generowanie permutacji elementów w wierszu */
    int nra = tr[0][0].nr, nrb = tr[1][0].nr, perm[N];
    for(i=0; i<m; i++)
      tmp[tab[1][nrb][i]] = tnr*N+i;
    for(i=0; i<m; i++){
      int a = tmp[tab[0][nra][i]];
      if(a<tnr*N){
        pod=0;
        break;
      }
      a %= N;
      perm[i] = a;
    }
    if(!pod){
      printf("NIE\n");
      continue;
    }
    /* sprawdzenie czy permutacje zgadzaj± siê dla wszystkich wierszy */
    for(i=1; i<n && pod; i++){
      nra = tr[0][i].nr;
      nrb = tr[1][i].nr;
      for(j=0;j<m;j++)
        if(tab[0][nra][j] != tab[1][nrb][perm[j]]){
          pod = 0;
          break;
        }
    }
    if(!pod)
      printf("NIE\n");
    else
      printf("TAK\n");
  }
  return 0;
}

