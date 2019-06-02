/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Latarnia (LAT)                                            *
 *   Plik:     lats1.cpp                                                 *
 *   Autor:    Wojciech Smietanka                                        *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             Przecina prostokaty kazdy z kazdym.                       *
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
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
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
#include <cassert> 
const int max_r = 2001000; 
const int max_n = 606; 

class rectangle { 
    public : 
        double xl, yl, xu, yu; 
        int id;   

        rectangle () {}

        rectangle (double _xl, double _yl, double _xu, double _yu, int _id) : 
            xl(_xl), yl(_yl), xu(_xu), yu(_yu), id(_id) 
        { 
        } 

        void get(int _id) { 
            int c = scanf("%lf%lf%lf%lf",&xl,&yl,&xu,&yu); 
            assert(c == 4); 
            id = _id; 
        }

        bool cross(const rectangle &A, rectangle &res) { 
            double x1 = max(xl, A.xl); 
            double y1 = max(yl, A.yl); 
            double x2 = min(xu, A.xu); 
            double y2 = min(yu, A.yu); 

            if (x1 < x2 && y1 < y2) { 
                res.xl = x1; 
                res.yl = y1; 
                res.xu = x2; 
                res.yu = y2; 
                res.id = id; 
                return true; 
            } 
            return false; 
        } 

        rectangle scale(double a) { 
            return rectangle(xl * a, yl * a, xu * a, yu * a, id); 
        } 

        void write() const { 
            printf("xl=%lf  yl=%lf  xu=%lf  yu=%lf  id=%d\n",xl,yl,xu,yu,id);  
        } 

} t[2][max_n]; 

rectangle w[2][max_r]; 

int main()
{   
   int n, m;  
    int c = scanf("%d %d", &n, &m); 
    assert(c == 2); 

    FOR(i,1,n) t[0][i-1].get(i);  
    FOR(i,1,m) t[1][i-1].get(i); 

    int c1 = 0, c2 = 0; 

    REP(j,m) 
        w[0][c1++] = t[1][j]; 

    set<int> result;     

    FOR(k,2,1024) {  
        int x = (k - 2) % 2; 
        int y = (k - 1) % 2; 
        rectangle R; 
        int pos = k % 2; 
        c = (pos?m:n); 
        c2 = 0;
        REP(i,c) { 
            R = t[pos][i].scale(1.0 / k);                           
                REP(j,c1) 
                    if (w[x][j].cross(R, w[y][c2])) { 
                        ++c2; 
                        if (k % 2 == 0) 
                            result.insert(R.id); 
                    } 
            } 
        if (!c1) break; 
        c1 = c2; 
    }     

    printf("%d\n", SIZE(result)); 
    FORE(e,result) printf("%d ",*e); 
    puts(""); 
	return 0;
}

