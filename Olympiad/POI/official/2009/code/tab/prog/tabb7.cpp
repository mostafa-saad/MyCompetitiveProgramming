/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb7.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie bledne O(n*m*lg n). Podobne do wzorcowego,    *
 *             ale zamiast sprawdzania rownosci permutacji sprawdza      *
 *             jedynie ich ilosc inwersji.                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1001, INF = 2000000007, M = 1000000;

int t, n, m, tab[2][N][N], i, j, tmp[2*M+1];
/* tablice zawieraj± najmniejsze liczby z wierszy tablic a i b oraz numery odpowiadaj±cych wierszy*/
pair<int,int> tr[2][N];

int ta[N];

int l_inwer(int per[],int p, int k){
  if(p==k)
    return 0;
  int i, j, w = 0, m = (p+k)/2, l=0;
  w += l_inwer(per, p, m);
  w += l_inwer(per, m+1, k);
  for(i=p, j=m+1;i<=m && j<=k;l++){
    if(per[i]<=per[j]){
      ta[l] = per[i];
      i++;
    }
    else{
      ta[l] = per[j];
      j++;
      w += m-i+1;
    }
  }
  while(i<=m)
    ta[l++] = per[i++];
  while(j<=k)
    ta[l++] = per[j++];
  for(i=p;i<=k;i++)
    per[i] = ta[i-p];
  return w;
}

int main()
{
  scanf("%d",&t);
  for(int tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    for(int nr=0; nr<2; nr++)
      for(i=0; i<n; i++)
        for(j=0; j<m; j++){ 
          scanf("%d",&tab[nr][j][i]);
          tab[nr][j][i]+=M;
        }
    swap(n,m);
    for(int nr=0; nr<2; nr++){
      for(i=0; i<n; i++){
        int mel = INF;
        for(j=0; j<m; j++)
          mel = min(mel,tab[nr][i][j]);
        tr[nr][i] = make_pair(mel, i);
      }
      sort(tr[nr],tr[nr]+n);
    }
    bool odp = true;
    for(i=0; i<n; i++)
      if(tr[0][i].first != tr[1][i].first)
        odp = false;
    if(!odp){
      printf("NIE\n");
      continue;
    }
    memset(tmp,0,sizeof(tmp));
    /* generowanie permutacji elementów w wierszu */
    int nra = tr[0][0].second, nrb = tr[1][0].second, perm[N];
    for(i=0; i<m; i++)
      tmp[tab[1][nrb][i]] = i+1;
    for(i=0; i<m; i++){
      int a = tmp[tab[0][nra][i]];
      if(a==0){
        odp=false;
        break;
      }
      a %= N;
      perm[i] = a;
    }
    int lin = l_inwer(perm,0,m-1)%2;
    if(!odp){
      printf("NIE\n");
      continue;
    }
    /* sprawdzenie czy permutacje maj± tak± sam± parzysto¶æ dla wszystkich wierszy */
    for(i=1; i<n && odp; i++){
      int nra = tr[0][i].second, nrb = tr[1][i].second, perm[N];
      for(j=0; j<m; j++)
        tmp[tab[1][nrb][j]] = i*N+j+1;
      for(j=0; j<m; j++){
        int a = tmp[tab[0][nra][j]];
        if(a<=i*N){
          odp=false;
          break;
        }
        a %= N;
        perm[j] = a;
      }
      if(lin != l_inwer(perm,0,m-1)%2)
        odp = false;
    }
    if(!odp)
      printf("NIE\n");
    else
      printf("TAK\n");
  }
  return 0;
}

