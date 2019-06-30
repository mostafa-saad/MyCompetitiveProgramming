/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mon.cpp                                          *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n * k * log n)                                 *
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

// RangeTree {{{
struct RangeTree{
    int T[77777];
    int F[77777];
    int n;
    RangeTree(){
        n=32768;
    }
    void update(int x, int val, int frm){
        x+= n;
        while(x){
            if(T[x] < val){
                T[x]=val;
                F[x]=frm;
            }
            x>>=1;
        }
    }
#define popraw(x) { if(res < T[x]) { res=T[x]; resf=F[x]; } }
    PII get_range(int l,int r){
        if(l>r) return MP(0, 0);
        l+=n, r+=n;
        int resf=F[l];
        int res=T[l];
        popraw(r);
        while( (l>>1) != (r>>1)){
            if(!(l&1)) popraw(l+1);
            l>>=1;
            if(r&1) popraw(r-1);
            r>>=1;
        }
        return MP(res, resf);
    }
};
// }}}

const int nmx= 100003, kmx= 101;
RangeTree R[101];
int f[nmx][kmx];
int r_val[nmx];
int a[nmx];
int p[kmx];
int n, k;

int main()
{
    scanf("%d%d",&n, &k);
    VI tmp;
    REP(i, n){
        scanf("%d",a+i);
        tmp.PB(a[i]);
    }
    sort(ALL(tmp));
    tmp.erase(unique(ALL(tmp)), tmp.end());
    int m= SIZE(tmp);
    REP(i, m) r_val[i]=tmp[i];
    REP(i, n) a[i]= lower_bound(ALL(tmp), a[i]) - tmp.begin();
    char buf[3];
    REP(i,k){
        scanf("%s",buf);
        switch(buf[0]){
            case '<':
                p[i]=0;
                break;
            case '>':
                p[i]=1;
                break;
            case '=':
                p[i]=2;
                break;
        };
    }
    int t[kmx]; 
    int best=-2, bestx=-1, bestj=-1;
    REP(i,n){
        REP(j, k){
            t[j]=0;
            if(j==0) t[j]=1;
            f[i][j]=-1;
            PII pr;
            int frm=(j-1+k)%k;
            switch(p[frm]){
                case 0:
                    pr=R[j].get_range(0, a[i]-1);
                    break;
                case 1:
                    pr=R[j].get_range(a[i]+1, m);
                    break;
                case 2:
                    pr=R[j].get_range(a[i], a[i]);
                    break;
            }
            if(pr.FI){
                t[j]=pr.FI+1;
                f[i][j]=pr.SE;
            }
            if(best < t[j]){
                best=t[j];
                bestx= i;
                bestj= j;

            }
        }
        REP(j,k)
            if(t[j]){
                R[(j+1)%k].update(a[i], t[j], i);
            }

    }
    printf("%d\n",best);
    VI res;
    do{
        res.PB(r_val[ a[bestx] ]);
        bestx= f[bestx][bestj];
        bestj = (k+bestj-1)%k;
    }while(bestx!=-1);
    reverse(ALL(res));
    FORE(i,res) printf("%d ",*i);
    puts("");
    return 0;
}
