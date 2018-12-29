/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              grab8.cpp                                        *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Usprawniona heurystyka z pliku grab2.cpp.        *
 *   Zlozonosc czasowa: O(n * log n)                                     *
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
VI T;
int R[nmx];
int main() {
    int n, a;
    scanf("%d",&n);
    REP(i,n) {scanf("%d",&a); T.PB(a);}
    sort(ALL(T));
    T.erase(unique(ALL(T)), T.end());
    n=SIZE(T);
    int res=0;
    int x=0;
    while(n){
        if(n==1){
            if(x) res-=T[0];
            else res+=T[0];
            break;
        }else{
            int r=n-1;
            if(T[r] < T[0]*2) r=0;
            n=r;
            if(x) res-=T[r];
            else res+=T[r];
        }
        x=1-x;
    }
    printf("%d\n",res);
    return 0;
}
