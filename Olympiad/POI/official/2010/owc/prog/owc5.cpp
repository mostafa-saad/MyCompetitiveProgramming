/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owc5.cpp                                         *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie weryfikujace.                        *
 *   Zlozonosc czasowa: O(n * k * log k + n^3)                           *
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

const int max_n = 666; 
const int max_k = 20200; 
const int DB = 0; 

class point { 
    public: 
        int x,y; 
        point() {}
        point(int _x, int _y) : x(_x), y(_y) { 
        } 
        void read() { 
            scanf("%d%d",&x,&y);
        }
        void write() { 
            printf("%d %d\n",x,y); 
        } 
        bool operator<(const point &A) const { 
            return x * A.y < y * A.x; 
        }         
        
} ; 

point P[max_n], S[max_k]; 
bool can[max_n][max_n]; 
int n,k,m,res[max_n][max_n]; 

void translate(const point &A) { 
    REP(j,n) { 
        P[j].x -= A.x; 
        P[j].y -= A.y; 
    } 
    REP(j,k) { 
        S[j].x -= A.x; 
        S[j].y -= A.y; 
    } 
} 

inline int next(int a) { 
    ++a; 
    if (a == n) return 0; 
    return a; 
}
 

int main()
{
    scanf("%d%d%d",&n,&k,&m); 
    REP(i,n) P[i].read(); 
    REP(i,k) S[i].read();
    CLR(can, 0);  
   
    REP(i,n) {       
        point A(P[i].x, P[i].y);               
        translate(A); 
        sort(S, S + k); 

        int l = (i + 2) % n; 
        int p = 0; 

        while ((l + 1) % n != i) { 
            while (S[p] < P[l] && p < k) ++p; 
            if (!((p < k && !(P[l] < S[p])) || p % 2 != 0)) 
                can[i][l] = 1; 
            l = next(l); 
        } 
               
        P[i].x *= -1; 
        P[i].y *= -1; 
        translate(A);
    }   

    
    CLR(res,0);     
    REP(i,n) res[i][(i+1)%n] = 1;  
    REP(i,n) if (can[i][(i+2)%n]) res[i][(i+2)%n] = 1; 
    REP(i,n) can[i][(i+1)%n] = 1; 
    REP(i,n) can[(i+1)%n][i] = 1;  

    FOR(d,3,n-1) 
        REP(i,n) { 
            int a = (i+1) % n, b = (i + d) % n; 
            LL acc = 0;  
            while (a != b) { 
                if (can[i][a] && can[a][b] && can[i][b])  
                    acc += res[i][a] * res[a][b]; 
                a = next(a); 
            } 
            res[i][b] = acc % m; 
        } 

   printf("%d\n",res[0][n-1]); 
  
	return 0;
}

