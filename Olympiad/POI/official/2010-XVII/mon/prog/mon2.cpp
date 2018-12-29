/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mon2.cpp                                         *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie alternatywne.                        *
 *   Zlozonosc czasowa: O(n^2)                                           *
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
int F[nmx][kmx];

int T[kmx][nmx];
int V[kmx][nmx];

int MX[kmx];

int resbest, rpos;
int R[nmx];


int compare(int a,int b){
    if(a<b) return -1;
    else if(a==b) return 0;
    return 1;
}

void update(int x, int res){
    if(res==-1) return;
    int p = (res-1)%k;
    switch(K[p]){
        case -1:
            if( T[p][(res-1)/k]==-1 || A[T[p][(res-1)/k]] > A[x]){
                T[p][(res-1)/k]=x;
                MX[p]= max(MX[p], (res-1)/k + 1);
            }
            break;
        case 0:
            if(V[p][A[x]] < res){
                T[p][A[x]] = x;
                V[p][A[x]] = res;
            }
            break;
        case 1:
            if( T[p][(res-1)/k]==-1 || A[T[p][(res-1)/k]] < A[x]){
                T[p][(res-1)/k]=x;
                MX[p]= max(MX[p], (res-1)/k + 1);
            
            }
            break;
    }
}

int main() {
    scanf("%d%d",&n,&k);    
    CLR(T,-1);
    VI tmp;
    REP(i,n) {scanf("%d",A+i); tmp.PB(A[i]);}
    sort(ALL(tmp));
    tmp.erase(unique(ALL(tmp)), tmp.end());
    REP(i,n) A[i]= lower_bound(ALL(tmp), A[i]) - tmp.begin();
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
    resbest=1;
    REP(i,n){
        int r[kmx];
        CLR(r, -1);
        REP(j, k){
            int res=-1;
            int resf=-1;
            if(K[j] == -1){
                FORD(vl, MX[j]-1, 0) if (A[T[j][vl]] < A[i]){         
                    res = vl * k + j + 2;
                    resf = T[j][vl];
                    break;
                }
            }
            else if(K[j] == 0){
                if(T[j][A[i]] != -1){
                    res= V[j][A[i]]+1;
                    resf= T[j][A[i]];
                }
            }
            else{
                FORD(vl, MX[j]-1, 0) if (A[T[j][vl]] > A[i]){         
                    res = vl * k + j + 2;
                    resf = T[j][vl];
                    break;
                }
            }
            if( res != -1){
                F[i][(j+1)%k]=resf;
            }
            r[j]=res;
            if (resbest < res){
                resbest = res;
                rpos = i;
            }
        }
        REP(j, k) update(i, r[j]);
        update(i, 1);
    }
    printf("%d\n",resbest);
    REP(i, resbest){
        R[resbest-i-1] = A[rpos];
        rpos = F[rpos][ (resbest - i - 1)%k];
    }
    REP(i, resbest) printf("%d ",tmp[R[i]]); 
    puts("");
    return 0;
}
