/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Okropny wiersz                                *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n*q*sqrt(n))                                *
 *   Opis:                 Rozwiazanie powolne (naiwne sprawdzanie       *
 *                         dzielnikow)                                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

#define PI pair<int,int>
#define MP make_pair<int,int>

#define _scanf(...) if (scanf(__VA_ARGS__));


using namespace std;

const int maxn = 500002;
const int maxq = 2000*1000;

char A[maxn];

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
  int k = y-x+1;
  int s = (int)sqrt(k)+1;
  int period = k;
  for(int i=1; i<=s; i++)
  {
    if (k%i==0)
    {
      bool ok = true;
    for(int j=x; j+i<=y; j++)
      if (A[j-1]!=A[j+i-1])
      {
        ok = false;
      break;
      }
    if (ok) period = i;
    }
    if (period<k) break;
  }
  if (period==k)
  for(int i=s; i>1; i--)
  {
    if (k%i==0)
    {
      bool ok = true;
    for(int j=x; j+k/i<=y; j++)
      if (A[j-1]!=A[j+k/i-1])
      {
        ok = false;
      break;
      }
    if (ok) period = k/i;
    }
    if (period<k) break;
  }
  printf("%d\n",period);
  }
}
