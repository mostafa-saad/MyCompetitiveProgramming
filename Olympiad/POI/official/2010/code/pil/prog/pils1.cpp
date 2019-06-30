/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils1.cpp                                        *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie powolne - klasyczne RMQ.             *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/


// Headers {{{
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cassert> 
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<assert.h>
using namespace std;
#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
#define CLR(A,v) memset((A),v,sizeof((A)))
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SIZE(x) (int)(x.size())
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long LL;
typedef long double LD; 
typedef vector<string> VS;
// }}}

const int max_n = 3003000; 
const int max_log = 23; // 2 ^ max_log > max_n 
int max_pow[max_n], a[max_n]; // 2 ^ max_pow[i] <= i < 2 ^ (max_pow[i] + 1) 

class rmq { 
    public: 
        vector<vector<int> > x;  
        int n, l;  

        rmq(VI v) {
            x.clear();             
            n = SIZE(v); 
            vector<int> y; 
            REP(i,max_log) x.PB(y); 
            REP(i,n) x[0].PB(v[i]); 
            int pow = 1, lev = 1;             
            l = 0; 
            while (1) {    
                REP(i,n-pow*2+1) x[lev].PB(0); 
                ++l; 
                REP(i,n-pow*2+1) x[lev][i] = min(x[lev - 1][i], x[lev-1][i+pow]); 
                ++lev; 
                pow *= 2; 
                if (pow * 2 > n) break;                 
            }                 
        }   

        int query(int a, int b) { 
            int lev = max_pow[b - a]; 
            return min(x[lev][a], x[lev][b - (1<<lev) + 1]); 
        }  

        ~rmq() {
        } 
} ; 

int main()
{
    int t,n; 
    assert(scanf("%d%d",&t,&n) == 2);   
    REP(i,n) assert(scanf("%d",&a[i]) == 1);
    max_pow[0] = 0;     
    max_pow[1] = 0; 
    FOR(i,2,n)
        if ((1<<max_pow[i-1]) * 2 == i) max_pow[i] = max_pow[i-1] + 1;    
        else max_pow[i] = max_pow[i-1]; 

    VI v;
    REP(i,n) v.PB(a[i]); 
    rmq* A = new rmq(v); 

    v.clear(); 
    REP(i,n) v.PB(-a[i]); 
    rmq* B = new rmq(v); 

    int res = 0, j = 0; 


    REP(i,n) { 
        while (j + 1 < n) { 
            if (-B->query(i, j + 1) - A->query(i, j + 1) <= t) ++j; 
            else break; 
        } 
        res = max(res, j - i + 1); 
    } 


    printf("%d\n",res);    
        
        
	return 0;
}
