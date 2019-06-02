/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Zlozonosc czasowa: O((n*lg(n)+(m+k)*lg(m))*lg(k))                   *
 *   Opis:              Rozwiazanie alternatywne                         *
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

const int nmx=300007,kmx=300007;
LL POW_TREE[nmx],max_pt;
inline int fun_pt(int x){return (((x-1)^x)+1) >> 1;}
void update_pt(int x,int vl)
{
	while (x <= max_pt) { POW_TREE[x]+=vl; x+=fun_pt(x);}	
}
LL pref_pt(int x)
{
	LL res=0;
	while(x) {res+=POW_TREE[x]; x-=fun_pt(x); }
	return res;
}
VI P[nmx];
int R[nmx];
int n, m, k;
int RR[kmx],LR[kmx],A[kmx];
int BSL[nmx],BSR[nmx],BSG[nmx];

VI S[nmx];

void add_range(int l,int r,int a) {
  if(l<=r) {
    update_pt(l,a);
    update_pt(r+1,-a);
  } else {
    add_range(1,r,a);
    add_range(l,m,a);
  }
}

bool binsearch(){
  bool found=0;
  REP(i,n) if(BSL[i] <= BSR[i]) {
    found=true;
    S[(BSL[i]+BSR[i])/2].PB(i);
  }
  if(!found) return 0;
  REP(i,k){
    add_range(LR[i],RR[i],A[i]);
    FORE(j, S[i+1]) {
      int g = *j;
      LL sum = 0;
      FORE(p, P[g]) {
        if(sum >= R[g]) break;
        sum+=pref_pt(*p);
      }
      if (sum >= R[g]) {
        BSG[g]=i+1;
        BSR[g]=i;
      } else {
        BSL[g]=i+2;
      }

    }
  }
  CLR(POW_TREE,0);
  FOR(i,1,k) S[i].clear();
  return true;
}


int main() {
  int a;
  scanf("%d%d",&n,&m);
  max_pt = m+2;
  REP(i,m) {
    scanf("%d",&a);
    P[a-1].PB(i+1);
  }
  REP(i,n) scanf("%d",R+i);
  scanf("%d",&k);
  REP(i,k) scanf("%d%d%d",LR+i,RR+i,A+i);
  CLR(BSG,-1);
  REP(i,n) BSL[i]=1,BSR[i]=k;
  while(binsearch());
  REP(i,n) {
    if(BSG[i]==-1) puts("NIE");
    else printf("%d\n",BSG[i]);

  }
  return 0;
}
