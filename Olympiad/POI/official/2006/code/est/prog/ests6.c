/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                ests6.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Zlozonosc: O(n^3)                              *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int m,n;
int dlug[2000];
int sumy[2001];
int t[2001][2001];

void wczyt(void){
  int i;
  scanf("%d%d",&m,&n);
  for (i=0;i<n;++i) scanf("%d",&(dlug[i]));
  for (i=0;i<n;++i) sumy[i+1]=sumy[i]+dlug[i];
}
int abs(int x){ return x>0?x:-x; }
void licz(void){
  int i,j,k,a;
  for (i=0;i<=n;++i)
    for (j=0;j<=n;++j)
      t[i][j]=-1;
  t[0][0]=0;
  for (i=1;i<=n && i-1+sumy[i]<=m;++i)
    t[i][i]=0;
  for (i=1;i<=n;++i)
    for (j=1;j<=i;++j)
      if (sumy[i] - sumy[i-j] + j - 1 <= m)
        for (k=0;k<=i-j;++k)
          if (t[i-j][k]!=-1){
            a = abs(sumy[i] - 2*sumy[i-j] + sumy[i-j-k] + j - k) + t[i-j][k];
            if (t[i][j]==-1 || a < t[i][j])
              t[i][j] = a;
          }
}

int main(void){
  int i,m=2100000000;
  wczyt();
  licz();
  for (i=1;i<=n;++i)
    if (t[n][i] >= 0 && m > t[n][i])
      m = t[n][i];
  printf("%d\n",m);
  return 0;
}
