/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Okropny wiersz                                *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n*q)                                        *
 *   Opis:                 Rozwiazanie powolne (KMP przy kazdym          *
 *                         zapytaniu)                                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define PI pair<int,int>
#define MP make_pair<int,int>

#define _scanf(...) if (scanf(__VA_ARGS__));

using namespace std;

const int maxn = 500002;

char A[maxn];
int KMP[maxn];

int main()
{
  int q,n;
  scanf("%d",&n);  
  _scanf("%s\n",A);
  _scanf("%d\n",&q);
  for(int i=0; i<q; i++)
  {
    int x,y;
    _scanf("%d %d",&x,&y);
    x--;
    char *B = A+x;
    int k = y-x;
    KMP[0] = KMP[1] = 0;
    int d = 0;
    for(int j=2; j<=k; j++)
    {
      while(d>0 && B[j-1]!=B[d])
        d = KMP[d];
      if (B[j-1]==B[d])
        d++;
      KMP[j] = d;
    }
    if (k%(k-KMP[k])==0)
      printf("%d\n",k-KMP[k]);
    else
      printf("%d\n",k);
  }
}
