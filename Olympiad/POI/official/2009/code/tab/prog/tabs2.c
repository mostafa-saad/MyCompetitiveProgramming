/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabs2.c                                                   *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne O(n!*m!*n*m). Sprawdza wsztstkie        *
 *             premutacje wierszy i kolumn.                              *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define N 1001
#define M 1000000

int t, n, m, i, j, tmp[2*M+1], a, perw[N], perk[N], tab[2][N][N];

int next_permutation(int t[],int n){
  int i, j, tmp, res = 1;
  for(i=n-1; i>0; i--)
    if(t[i]>t[i-1])
      break;

  if(i==0)
    res = 0;
  else {
    for(j=i; j<n; j++)
      if(t[i-1]>=t[j])
        break;
    tmp = t[i-1];
    t[i-1] = t[j-1];
    t[j-1] = tmp;
  }
  for(j=n-1;i<j;i++,j--){
    tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
  }
  return res;
}

int main()
{
  scanf("%d",&t);
  int nr, tnr;
  for(tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    int odp=1;    
    for(nr=0; nr<2; nr++)
      for(i=0; i<n; i++)
        for(j=0; j<m; j++){ 
          scanf("%d",&tab[nr][i][j]);
          tab[nr][i][j]+=M;
          if(!nr)
            tmp[tab[nr][i][j]] = tnr;
          else
            if(tmp[tab[nr][i][j]] != tnr)
              odp=0;
        }
    if(!odp){
      printf("NIE\n");
      continue;
    }
    for(i=0; i<n; i++)
      perw[i]=i;
    for(j=0; j<m; j++)
      perk[j]=j;
    odp=0;
    do{
      do{
        int f = 1;
        for(i=0;i<n && f;i++)
          for(j=0;j<m;j++)
            if(tab[0][i][j] != tab[1][perw[i]][perk[j]]){
              f = 0;
              break;
            }
        odp |= f;
      }while(!odp && next_permutation(perk,m));
    }while(!odp && next_permutation(perw,n));
    if(odp)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}

