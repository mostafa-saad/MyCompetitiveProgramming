/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n*lglg(n))                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Minimalizuje liczbe, a nie indeks                *
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

const int MAX_N = 1000100;
const int MAX_A = 1000100;
const int INF = 100;

int p[MAX_N], c[MAX_A], prev[MAX_A];
int gdzie1[MAX_A], gdzie2[MAX_A];
pair<char, int> best1[MAX_A], best2[MAX_A];

inline pair<char, int> operator+(pair<char, int> a, int x) {
  return MP(a.first+x, a.second);
}

void upd(int i, int j) {
  if(best1[j]>best1[i]+1) {
    if(best1[j].second!=best1[i].second)
      best2[j]=best1[j];
    best1[j]=best1[i]+1;
  }
  if(best2[j]>best1[i]+1 && best1[j].second!=best1[i].second)  {
    best2[j]=best1[i]+1;
  }
  else if(best2[j]>best2[i]+1)
    best2[j]=best2[i]+1;
}

int main(void) {
  int n, A=0; assert(scanf("%d", &n)==1);
  FOR(i,1,n+1) {
    assert(scanf("%d", &p[i])==1);
    if(gdzie1[p[i]]==0)
      gdzie1[p[i]]=i;
    else if(gdzie2[p[i]]==0)
      gdzie2[p[i]]=i;
    A=max(A, p[i]);
  }
  for(int i=2; i*i<=A; ) {
    for(int j=i+i; j<=A; j+=i)
      c[j]=i;
    while(c[++i]);
  }
  prev[1]=-1; VI pri;
  for(int i=2; i<=A; ++i) {
    if(!c[i]) {
      prev[i]=1;
      c[i]=i;
      pri.PB(i);
    }
    else if(c[i]!=c[i/c[i]])
      prev[i]=i/c[i];
    else
      prev[i]=prev[i/c[i]];
  }
  for(int i=1; i<=A; ++i) {
    best2[i]=MP(INF, -2);
    if(gdzie1[i]!=0)
      best1[i]=MP(0, i);
    else
      best1[i]=MP(INF, -2);
  }
  for(int i=A; i>0; --i) {
    for(int k=i; k!=1; k=prev[k])
      upd(i, i/c[k]);
  }
  for(int i=1; i<=A; ++i) {
    REP(l,SZ(pri)) {
      int j=i*pri[l];
      if(j>A)
        break;
      upd(i, j);
    }
  }
  for(int i=1; i<=n; ++i) {
    int k=p[i], res=-1;
    if(gdzie2[k]!=0) {
      if(i==gdzie1[k])
        res=gdzie2[k];
      else
        res=gdzie1[k];
    }
    else {
      // tu blad moze?
      if(best1[k].second==k)
        res=gdzie1[best2[k].second];
      else
        res=gdzie1[best1[k].second];
    }
    printf("%d\n", res);
  }
  return 0;
}
