/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Okropny wiersz                                   *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n + q sqrt(n))                                 *
 *   Opis:              Rozwiazanie powolne (haszowanie)                 *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>

#define _scanf(...) if (scanf(__VA_ARGS__));

using namespace std;

const int maxn = 500002;

const int base = 97;



char A[maxn];
int n, m;
int power[maxn];
int hash[maxn];
int checks = 0;


bool equal(int a, int b, int len)
{
  return (hash[a+len]-hash[a])*power[b]==(hash[b+len]-hash[b])*power[a];
}


int main()
{
  ios_base::sync_with_stdio(0);
  scanf("%d",&n);  
  _scanf("%s\n",A);
  power[0] = 1;
  for(int i=1; i<=n; i++)
    power[i] = power[i-1]*base;
  hash[0] = 0;
  for(int i=1; i<=n; i++)
    hash[i] = hash[i-1]+(A[i-1]-'a')*power[i-1];
  cerr << "Preprocessing done." << endl;
  int q;
  _scanf("%d",&q);
  while(q--)
  {
    int a,b;
  _scanf("%d %d",&a,&b);
    a--; b--;
    int len = b-a+1;
    int sq = (int)sqrt(len) + 1;
    int period = len;
    for(int i=1; i<=sq; i++)
      if (len%i==0)
      {
        if (equal(a,a+i,len-i))
    {
          period = i;
      break;
    }
      }
  if (period==len)
    for(int i=sq; i>=1; i--)
      if (len%i==0)
      {
        if (equal(a,a+len/i,len-len/i) && len/i<period)
    {
          period = len/i;
      break;
    }
      }
    printf("%d\n",period);
  }
}
