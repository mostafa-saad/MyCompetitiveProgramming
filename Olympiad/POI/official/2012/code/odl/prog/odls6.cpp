/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Nie uzywa redukcji do grafow                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

#define REP(AA,BB) for(int AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(int AA=(BB); AA<(CC); ++AA)
#define FC(AA,BB) for(__typeof((AA).begin()) BB=(AA).begin(); BB!=(AA).end(); ++BB)
#define SZ(AA) ((int)((AA).size()))
#define ALL(AA) (AA).begin(), (AA).end()
#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;  
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

const int MAX_A = 1000010;
const int MAX_N = 1000010;
const int INF = 1000000;

int p[MAX_N], gdzie[MAX_A], gdzie2[MAX_A];
int c[MAX_A], s[MAX_A], best[MAX_A], best2[MAX_A];
int res[MAX_A], wyn[MAX_A];

int main(void) {
  int n, A=0; assert(scanf("%d", &n)==1);
  FOR(i,1,n+1) {
    assert(scanf("%d", &p[i])==1);
    if(gdzie[p[i]]==0)
      gdzie[p[i]]=i;
    else if(gdzie2[p[i]]==0)
      gdzie2[p[i]]=i;
    A=max(A, p[i]);
  }
  for(int i=2; i*i<=A; ) {
    for(int j=i+i; j<=A; j+=i)
      c[j]=i;
    while(c[++i]);
  }
  FOR(i,2,A+1) {
    if(!c[i])
      s[i]=1;
    else
      s[i]=1+s[i/c[i]];
  }
  memset(best, -1, sizeof(int)*(A+1));
  for(int i=1; i<=A; ++i) {
    for(int j=i; j<=A; j+=i) {
      if(gdzie[j]==0)
        continue;
      int b1=best[i], b2=best2[i];
      if(b1==-1 || (s[b1]>s[j] || (s[b1]==s[j] && gdzie[j]<gdzie[b1]))) {
        best2[i]=b1;
        best[i]=j;
      }
      else if(b2==-1 || (s[b2]>s[j] || (s[b2]==s[j] && gdzie[j]<gdzie[b2])))
        best2[i]=j;
    }
  }
  for(int i=1; i<=A; ++i)
    res[i]=INF;
  for(int i=1; i<=A; ++i) {
    for(int j=i; j<=A; j+=i) {
      if(gdzie[j]==0 || gdzie2[j]!=0)
        continue;
      int x=(best[i]==j ? best2[i] : best[i]);
      if(x!=-1) {
        int can=s[j]+s[x]-2*s[i];
        if(can<res[j] || (can==res[j] && gdzie[x]<wyn[j])) {
          res[j]=can;
          wyn[j]=gdzie[x];
        }
      }
    }
  }
  FOR(i,1,n+1) {
    int a=p[i];
    if(gdzie[a]!=i) {
      printf("%d\n", gdzie[a]);
      continue;
    }
    else if(gdzie2[a]!=0) {
      printf("%d\n", gdzie2[a]);
      continue;
    }
    else
      printf("%d\n", wyn[a]);
  }
  return 0;
}

