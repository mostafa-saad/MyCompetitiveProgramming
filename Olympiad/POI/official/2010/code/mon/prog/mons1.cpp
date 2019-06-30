/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mons1.cpp                                        *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie powolne - bez drzewa przedzialowego. *
 *   Zlozonosc czasowa: O(n^2 * k)                                       *
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
int T[nmx][kmx];
int F[nmx][kmx];
int res, rpos;
int R[nmx];

int compare(int a,int b){
    if(a<b) return -1;
    else if(a==b) return 0;
    return 1;
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
    res = 1;
    REP(i,n){
        T[i][0]=1;
        REP(j, k){
            REP(x, i) if( K[j] == compare(A[x],A[i]) && T[x][j] && T[x][j]+1 > T[i][(j+1)%k]){
                T[i][(j+1)%k] = T[x][j] + 1;
                F[i][(j+1)%k] = x;
            }
            if(T[i][(j+1)%k] > res){
                res = T[i][(j+1)%k];
                rpos= i; 
            }
        }   
    }
    printf("%d\n",res);
    REP(i, res){
        R[res-i-1] = A[rpos];
        rpos = F[rpos][ (res - i - 1)%k];
    }
    REP(i, res) printf("%d ",R[i]); 
    puts("");
    return 0;
}
