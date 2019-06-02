/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              gra3.cpp                                         *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie weryfikujace.                        *
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
    int best=R[0]=T[0];
    FOR(i, 1, n-1){
        best= max(best, T[i]-R[i-1]);
        R[i]=best;
    }
    printf("%d\n",best);
    return 0;
}
