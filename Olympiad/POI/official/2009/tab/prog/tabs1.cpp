/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabs1.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne O(n!*m!*n*m). Sprawdza wszystkie        *
 *             permutacje wierszy i kolumn.                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1001, INF = 2000000007, M = 1000000;

int t, n, m, i, j, tmp[2*M+1], a, perw[N], perk[N], tab[2][N][N];

int main()
{
  scanf("%d",&t);
  for(int tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    bool odp=true;
    for(int nr=0; nr<2; nr++)
      for(i=0; i<n; i++)
        for(j=0; j<m; j++){ 
          scanf("%d",&tab[nr][i][j]);
          tab[nr][i][j]+=M;
          if(!nr)
            tmp[tab[nr][i][j]] = tnr;
          else
            if(tmp[tab[nr][i][j]] != tnr)
              odp=false;
        }
    if(!odp){
      printf("NIE\n");
      continue;
    }
    for(i=0; i<n; i++)
      perw[i]=i;
    for(j=0; j<m; j++)
      perk[j]=j;
    odp=false;
    do{
      do{
        bool f = true;
        for(i=0;i<n && f;i++)
          for(j=0;j<m;j++)
            if(tab[0][i][j] != tab[1][perw[i]][perk[j]]){
              f = false;
              break;
            }
        odp |= f;
      }while(!odp && next_permutation(perk,perk+m));
    }while(!odp && next_permutation(perw,perw+n));
    if(odp)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}

