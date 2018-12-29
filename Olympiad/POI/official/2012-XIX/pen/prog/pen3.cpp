/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Zlozonosc czasowa: O(n log n)                                       *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************/

// headers {{{
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cctype>
#include <cstring>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef long double LD;
typedef long long LL;
typedef pair<LD,LD> PD;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<string> VS;

#define VAR(v,n) __typeof(n) v=(n)
#define REP(i,n) for(int i=0; i<(n); i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)
#define FORD(i,a,b) for(int i=(a); i>=(b); i--)
#define FORE(i,c) for(VAR(i,(c).begin()); i!=(c).end(); i++)

#define ALL(x) x.begin(),x.end()
#define CLR(A,v) memset((A),v,sizeof((A)))
#define FI first
#define MP make_pair
#define PB push_back
#define SE second
#define SIZE(x) ((int)(x).size())
// }}}

const int nmx=1000003;

int n;
int P[nmx], S[nmx], SR[nmx], TS[nmx];
VI E[nmx];
VI Q;
int fre;
int fresum;

int treesize(int v){
  if(TS[v]) return TS[v];
  TS[v]=1;
  FORE(i, E[v]) {
    TS[v] += treesize(*i);
  }
  return TS[v];
}


int main() {
  CLR(SR, -1);
  scanf("%d",&n);
  REP(i, n) {
    scanf("%d%d",P+i, S+i);
    P[i]--;
    if(P[i] == i){
      S[i]=n;
    } else if (S[i]==0){
      E[P[i]].PB(i);
    }
    SR[S[i]]=i;
  }
  int last;
  FOR(i, 1, n) {
    int v=SR[i];
    if (v==-1) {
      Q.PB(i);
      fre++;
    } else {
      if (fre == treesize(v)-1) { // wypelnij
        while(SIZE(E[v])==1) {
          v=E[v][0];
          S[v] = Q.back();
          Q.pop_back();
        } 
        fre -= (treesize(SR[i])-1);
      }
      else {
        fresum += treesize(v)-1;
        if (fresum == fre) {
          while(SIZE(E[v])==1) {
            v=E[v][0];
            S[v] = Q.back();
            if (S[v] < last) {
              S[v]=0;
              break;
            }
            Q.pop_back();
          } 
          fresum=0;
          fre=0;
        }
        if (treesize(v)-1) {
          last = i;
        }
      }    
    }
  }
  REP(i,n)
    printf("%d\n",S[i]);



  return 0;
}
