/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Latarnia (LAT)                                            *
 *   Plik:     latb3.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *             Kilkaset losowych punktow z kazdego okna.                 *
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

const int iters=50000;
const int nmx=607;
int n[2];
int X[2][nmx][2], Y[2][nmx][2];
bool BR[nmx];
bool B[2][1003][2003];
const int move=1001;


int main(){
    REP(i,2) scanf("%d",n+i);
    REP(i,2){
        REP(j, n[i]){
            REP(k,2) scanf("%d%d",X[i][j]+k, Y[i][j]+k);
            FOR(y,Y[i][j][0],Y[i][j][1]-1)
                FOR(x,X[i][j][0], X[i][j][1]-1) B[i][y][x+move]=1;
        }
    }
    REP(j, n[0]){
        REP(it, iters){
            double px=((rand()%99999)+1)/100000.;
            double py=((rand()%99999)+1)/100000.;
            double x=px*X[0][j][0] + (1-px)*X[0][j][1];
            double y=py*Y[0][j][0] + (1-py)*Y[0][j][1];
            FOR(m, 0, 9){
                int den = 2*(1<<m);
                if(BR[j]) break;
                bool ok=1;
                FOR(i,1,den-1){
                    int k=i%2;
                    double xc = x*i/ (double)den;
                    double yc = y*i/ (double)den;
                    if(!B[k][(int)yc][(int)(xc+move)]){ ok=0; break;} 
                }
                if(ok) BR[j]=1;
            }
        }
    }
    int r=0;
    REP(i,n[0]) r+=BR[i];
    printf("%d\n",r);
    REP(i,n[0]) if(BR[i]) printf("%d ",i+1);
    puts("");
    return 0;
}
