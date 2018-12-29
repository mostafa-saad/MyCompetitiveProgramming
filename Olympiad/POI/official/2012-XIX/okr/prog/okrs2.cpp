/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Okropny wiersz                                *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n^2 + q)                                    *
 *   Zlozonosc pamieciowa: O(n + q)                                      *
 *   Opis:                 Rozwiazanie powolne (KMP offline)             *
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
const int maxq = 2000*1000;

char A[maxn];
vector<PI> questions[maxn];
int answers[maxq];
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
  questions[x-1].push_back(MP(y-x+1,i));
  }
  n=strlen(A);
  for(int j=0; j<n; j++)
  {
    if (questions[j].size()==0)
      continue;
    KMP[0] = KMP[1] = 0;
  int d = 0;
  for(int i=2; i+j<=n; i++)
  {
    while(d>0 && A[j+i-1]!=A[j+d])
      d = KMP[d];
    if (A[j+i-1]==A[j+d])
      d++;
    KMP[i] = d;
  }
  for(int r=0; r<(int)questions[j].size(); r++)
  {
      int k  = questions[j][r].first;
    int a = questions[j][r].second;
    if (k%(k-KMP[k])==0)
      answers[a] = k-KMP[k];
    else
      answers[a] = k;
  }
  }
  for(int i=0; i<q; i++)
    printf("%d\n",answers[i]);
}
