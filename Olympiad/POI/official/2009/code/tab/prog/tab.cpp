/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tab.cpp                                                   *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wzorcowe O(n*m+n*log n).                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1001, INF = 2000000007, M = 1000000;

int t, n, m, tab[2][N][N], i, j, tmp[2*M+1];
/* tablice zawieraj± najmniejsze liczby z wierszy tablic a i b oraz numery odpowiadaj±cych wierszy*/
pair<int,int> tr[2][N];

int main()
{
  scanf("%d",&t);
  for(int tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    for(int nr=0; nr<2; nr++){
      for(i=0; i<n; i++){
        int mel = INF;
        for(j=0; j<m; j++){ 
          scanf("%d",&tab[nr][i][j]);
          tab[nr][i][j]+=M;
          mel = min(mel,tab[nr][i][j]);
        }
        tr[nr][i] = make_pair(mel, i);
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
    /* generowanie permutacji elementów w wierszu */
    int nra = tr[0][0].second, nrb = tr[1][0].second, perm[N];
    for(i=0; i<m; i++)
      tmp[tab[1][nrb][i]] = tnr*N+i;
    for(i=0; i<m; i++){
      int a = tmp[tab[0][nra][i]];
      if(a<tnr*N){
        pod=false;
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
      nra = tr[0][i].second;
      nrb = tr[1][i].second;
      for(j=0;j<m;j++)
        if(tab[0][nra][j] != tab[1][nrb][perm[j]]){
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

