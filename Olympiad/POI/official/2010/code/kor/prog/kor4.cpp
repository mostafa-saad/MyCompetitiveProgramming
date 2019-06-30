/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Korale (KOR)                                              *
 *   Plik:     kor4.cpp                                                  *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie weryfikacyjne.                                *
 *                                                                       *
 *************************************************************************/



// {{{
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cctype>
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
typedef pair<int,int> PI;
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


const LL prim = 1383572491513LL;
const int nmx=200003;
int D[nmx],n,res;
VI R;
LL H[nmx],RH[nmx],P[nmx];
LL TS[nmx],h;
int main() {
    scanf("%d",&n);
    REP(i,n) scanf("%d",D+i);
    FORD(i,n-1,0) H[i]=D[i]+prim*H[i+1];
    RH[0]=D[0];
    FOR(i,1,n-1) RH[i]=RH[i-1]*prim + D[i];
    P[0]=1;
    FOR(i,1,n-1) P[i]=P[i-1]*prim;
    
    FOR(k,1,n){
        h=0;
        LL hs1,hs2;
        for(int i = 0; i+k <= n ; i+=k){
            hs1 = H[i] - P[k]*H[i+k];
            hs2 = RH[i+k-1] - (i?(RH[i-1]*P[k] ):(0));
            TS[h++]=min(hs1,hs2)*P[k]*max(hs1,hs2);
        }            
        sort(TS,TS+h);
        int r= unique(TS,TS+h) - TS;
        if ( r >= res ){
            if(r > res){
                R.clear();
                res=r;
            }
            R.PB(k);
        }       
    }
    printf("%d %d\n",res,SIZE(R));
    FORE(i,R) printf("%d\n",*i);
    return 0;
}
