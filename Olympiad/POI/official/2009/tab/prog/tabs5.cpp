/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabs5.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne O(min(n,m)*n*m). Sprowadza do postaci   *
 *             kanonicznej bez sortowania.                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1001, INF = 2000000007;

int t,n,m,tab[2][N][N];

void ustalPostac(int t[N][N]){
  int i,j;
  int kon = min(n,m);
  for(int l=0;l<kon;l++){
    int mw = INF,w=l,k=l;
    for(i=l;i<n;i++)
      for(j=l;j<m;j++)
        if(t[i][j]<mw){
          w = i;
          k = j;
          mw = t[i][j];
        }
    /*zamiana odpowiednich wierszy i kolumn*/
    if(w!=l)
      for(j=0;j<m;j++)
        swap(t[w][j],t[l][j]);
    if(k!=l)
      for(i=0;i<n;i++)
        swap(t[i][k],t[i][l]);
  }
  /* sortowanie leksykograficzne nadmiarowych wierszy lub kolumn*/
  if(kon<n){
    int w;
    for(int l=kon;l<n;l++){
      w=l;
      for(i=l+1;i<n;i++)
        if(t[i][0]<t[w][0])
          w=i; 
      if(w!=l)
        for(j=0;j<m;j++)
          swap(t[w][j],t[l][j]);
    }
  }
  if(kon<m){
    int k;
    for(int l=kon;l<m;l++){
      k=l;
      for(j=l+1;j<m;j++)
        if(t[0][j]<t[0][k])
          k=j;
      if(k!=l)
        for(i=0;i<n;i++)
          swap(t[i][k],t[i][l]);
    }
  }
}

int i,j;

int main()
{
  scanf("%d",&t);
  for(int tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    for(int nr=0; nr<2; nr++){
      for(i=0; i<n; i++)
        for(j=0; j<m; j++) 
          scanf("%d",&tab[nr][i][j]);
      ustalPostac(tab[nr]);
    }
    bool f=true;
    for(i=0;i<n && f;i++)
      for(j=0;j<m;j++)
        if(tab[0][i][j]!=tab[1][i][j]){
          f=false;
          break;
        }
    if(f)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}

