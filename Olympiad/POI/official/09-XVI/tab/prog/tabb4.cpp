/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb4.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie bledne O(n*m*lg n). Sortuje kazdy wiersz      *
 *             z osobna i sprawdza, czy istnieje odpowiednik w drugiej   *
 *             macierzy.                                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1001, INF = 2000000007, M = 1000000;

int t, n, m, tab[2][N][N], i, j, tmp[2*M+1];
/* tablice zawieraj± najmniejsze liczby z wierszy macierzy a i b oraz numery odpowiadaj±cych wierszy*/
pair<int,int> tr[2][N];

int main()
{
  scanf("%d",&t);
  for(int tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    for(int nr=0; nr<2; nr++){
      for(i=0; i<n; i++){
        for(j=0; j<m; j++){ 
          scanf("%d",&tab[nr][i][j]);
          tab[nr][i][j]+=M;
        }
        sort(tab[nr][i],tab[nr][i]+m);
        tr[nr][i] = make_pair(tab[nr][i][0], i);
      }
      sort(tr[nr],tr[nr]+n);
    }
    bool pod = true;
    for(i=0; i<n; i++)
      if(tr[0][i].first != tr[1][i].first)
        pod = false;
    if(!pod){
      printf("NIE\n");
      continue;
    }
    int nra, nrb;
    /* sprawdzenie czy posortowane wiersze maj± swoje odpowiedniki */
    for(i=0; i<n && pod; i++){
      nra = tr[0][i].second;
      nrb = tr[1][i].second;
      for(j=0;j<m;j++)
        if(tab[0][nra][j] != tab[1][nrb][j]){
          pod = false;
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

