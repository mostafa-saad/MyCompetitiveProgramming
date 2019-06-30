/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Monotonicznosc (MON)                                      *
 *   Plik:     monb2.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie niepoprawne - back-tracking.                  *
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

const int nmx=20003;
const int kmx=103;

int n,k;
int A[nmx];
int K[kmx];
VI res;

int compare(int a,int b){
    if(a<b) return -1;
    else if(a==b) return 0;
    return 1;
}


VI tmp;

void back_track(int x,int l, int r){
    if(x==n){
        if(SIZE(tmp) > SIZE(res)) res=tmp;
        return;
    }
    if(n-x <= SIZE(res) - r) return;
    
    if(compare(l, A[x]) == K[(r-1)%k]){
        tmp.PB(A[x]);
        back_track(x+1, A[x], r+1);
        tmp.pop_back();
    }
    back_track(x+1, l, r);

} 


int main() {
    scanf("%d%d",&n,&k);    
    REP(i,n) scanf("%d",A+i);
    char buf[3];
    REP(i,k){
        scanf("%s",buf);
        switch(buf[0]){
            case '<':
                K[i]=-1;
                break;
            case '>':
                K[i]=1;
                break;
            case '=':
                K[i]=0;
                break;
        }
    }
    
    REP(i,min(100,n)){
        int b=i;
        tmp.clear();
        tmp.PB(A[b]);
        back_track(b+1, A[b], 1);
    }
    printf("%d\n",SIZE(res));
    FORE(i,res) printf("%d ",*i);
    puts("");
    return 0;
}
