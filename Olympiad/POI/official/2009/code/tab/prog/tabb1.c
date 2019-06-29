/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb1.c                                                   *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie bledne i wolne O(min(n,m)*n*m). Sprowadza     *
 *             do postaci kanonicznej, ale brakuje sortowania            *
 *             nadmiarowych wierszy lub kolumn.                          *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define N 1001
#define INF 2000000007 
#define M 1000000

int t, n, m, tab[2][N][N];

void ustalPostac(int t[N][N]){
  int i, j, l, kon = (n<m)?n:m;
  for(l=0;l<kon;l++){
    int mw = INF, w=l, k=l, tmp;
    for(i=l;i<n;i++)
      for(j=l;j<m;j++)
        if(t[i][j]<mw){
          w = i;
          k = j;
          mw = t[i][j];
        }
    /*zamiana odpowiednich wierszy i kolumn*/
    if(w!=l)
      for(j=0;j<m;j++){
        tmp = t[w][j];
        t[w][j] = t[l][j];
        t[l][j] = tmp;
      }
    if(k!=l)
      for(i=0;i<n;i++){
        tmp = t[i][k];
        t[i][k] = t[i][l];
        t[i][l] = tmp;
      }
  }
}

int main()
{
  scanf("%d",&t);
  int tnr,nr,i,j;
  for(tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    for(nr=0; nr<2; nr++){
      for(i=0; i<n; i++)
        for(j=0; j<m; j++) 
          scanf("%d",&tab[nr][i][j]);
      ustalPostac(tab[nr]);
    }
    short f=1;
    for(i=0;i<n && f;i++)
      for(j=0;j<m;j++)
        if(tab[0][i][j]!=tab[1][i][j]){
          f=0;
          break;
        }
    if(f)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}

