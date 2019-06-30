/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pil.cpp                                          *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************/

// Headers {{{
#include<iostream>
#include<cstdio>
#include<cctype>
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
#include<deque>
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


class rmq { 
    public: 
        deque<PII > q; 

        inline void pf(int pos) { 
            if (q.front().SE == pos) { 
                q.pop_front(); 
            } 
        } 

        inline void add_elem(int val, int pos) { 
            while (SIZE(q) && q.back().FI > val) { 
                q.pop_back(); 
            } 
            q.push_back(MP(val, pos)); 
        } 

        inline int get_min() { 
            return q.front().FI; 
        } 
} mx, mn; 

int n, t, a[3000300], last_added = -1, res = 0; 

int main()
{
    assert(scanf("%d%d",&t,&n) == 2); 
    REP(i,n) assert(scanf("%d", &a[i]) == 1); 
    a[n] = a[n - 1] - t - 1;  

    REP(i,n) { 
        if (last_added < i) { 
            mx.add_elem(-a[i], i); 
            mn.add_elem(a[i], i);  
            ++last_added; 
        } 

        while (last_added < n && -mx.get_min() - mn.get_min() <= t) { 
            ++last_added;     
             mx.add_elem(-a[last_added], last_added); 
             mn.add_elem(a[last_added], last_added);  
        } 
        res = max(res, last_added - i);                 
        mn.pf(i); mx.pf(i); 
    } 
    printf("%d\n",res);  

	return 0;
}

