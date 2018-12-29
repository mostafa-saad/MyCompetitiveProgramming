/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb2.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie bledne O(n*m). Sprawdza jedynie rownosc       *
 *             zbiorow elementow w obu tablicach.                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1001, INF = 2000000007, M = 1000000;

int t, n, m, i, j, tmp[2*M+1], a;

int main()
{
  scanf("%d",&t);
  for(int tnr=1; tnr <= t; tnr++){
    scanf("%d %d",&n,&m);
    for(i=0; i<n; i++)
      for(j=0; j<m; j++){ 
        scanf("%d",&a);
        tmp[a+M] = tnr;
      }
    bool f=true;
    for(i=0; i<n; i++)
      for(j=0; j<m; j++){ 
        scanf("%d",&a);
        if(tmp[a+M] != tnr)
          f=false;        
      }
    if(!f)
      printf("NIE\n");
    else
      printf("TAK\n");
  }
  return 0;
}

