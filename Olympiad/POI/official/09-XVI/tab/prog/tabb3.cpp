/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb3.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie bledne O(1). Sprawdza po 1000 pierwszych i    *
 *             ostatnich permutacji wierszy i kolumn.                    *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1001, INF = 2000000007, M = 1000000, ILP = 1000;

int t, n, m, i, j, tmp[2*M+1], a, perw[N], perk[N], tab[2][N][N];

bool sprawdz(int perw[],int perk[]){
  bool f=true;
  for(i=0;i<n && f;i++)
    for(j=0;j<m;j++)
      if(tab[0][i][j] != tab[1][perw[i]][perk[j]]){
        f = false;
       break;
     }
  return f;
}

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
    odp=false;
    int lpw,lpk;
    /* przy nr=0 sprawdza pocz±tkowe permutacje, a przy nr=1 koñcowe */
    for(int nr=0; nr<2; nr++){
      for(i=0; i<n; i++){
        if(nr)
          perw[i]=n-i-1;
        else
          perw[i]=i;
      }
      lpw=0;
      do{
        /* pocz±tkowe permutacje */
        for(j=0; j<m; j++)
          perk[j]=j;
        lpk=0;
        do{
          odp |= sprawdz(perw,perk);
          lpk++;
        }while(!odp && next_permutation(perk,perk+m) && lpk<ILP);
        if(lpk<ILP){
          continue;
        }
        /* koñcowe permutacje */
        for(j=0; j<m; j++)
          perk[j]=n-j-1;
        lpk=0;
        do{
          odp |= sprawdz(perw,perk);
          lpk++;
        }while(!odp && prev_permutation(perk,perk+m) && lpk<ILP);
        lpw++;
        /* dla nr=0 wykonuje sie next_permutation, a dla nr=1 prev_permutation */
      }while(!odp && (nr==0 ? next_permutation(perw,perw+n) : prev_permutation(perw,perw+n)) && lpw<ILP);
      if(lpw<ILP)
        break;
    }
    if(odp)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}

