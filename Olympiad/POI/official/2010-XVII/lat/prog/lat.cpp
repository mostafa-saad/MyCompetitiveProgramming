/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Latarnia (LAT)                                   *
 *   Plik:              lat.cpp                                          *
 *   Autor:             Wojciech Smietanka                               *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O((n + m) * W * log ((n + m) * W))               *
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
const int max_r = 603;  
const int max_e = 2610000; 
const double eps = 1e-8; 
#define MAX_H 1000

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
       
        bool cross(const rectangle &A) { 
            double x1 = max(xl, A.xl); 
            double y1 = max(yl, A.yl); 
            double x2 = min(xu, A.xu); 
            double y2 = min(yu, A.yu); 

            return (x1 < x2 && y1 < y2); 
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

} ; 

inline bool is_zero(double x) { return -eps < x && x < eps; } 

class event { 
    public : 
        double y; 
        int x1, x2; 
        int id;  
        bool add;

        event() {}

        event(double _y, int _x1, int _x2, int _id, bool _add) : 
           y(_y), x1(_x1), x2(_x2), id(_id), add(_add) { 
           }  

        bool operator<(const event &A) const { 
            if (is_zero(A.y - y)) { 
                return add < A.add; 
            }            
            return y < A.y; 
        } 
        void write() { 
            printf("y=%lf  x1=%d  x2=%d  id=%d  add=%d\n",y,x1,x2,id,add); 
        } 
} ; 

class tree { 
    public: 
        int smax[max_e], all[max_e]; 
        PII win[max_r]; 
        set<PII > s; 
        set<int> result; 
        int N, O;  

        tree() {}

        void init(int _N, int _O) { 
            O = _O; 
            N = _N; 
            while (N&(N-1)) ++N; 

            REP(i,N*2) { 
                smax[i] = 0; 
                all[i] = 0; 
            } 
            s.clear(); 
            result.clear(); 
        } 

        inline void update_node(int a) { 
            smax[a] = max(smax[2*a] + all[2*a], smax[2*a+1] + all[2*a+1]); 
        }

        int find_max(int a) {           
            if (a >= N) return a; 
            if (smax[2*a]+all[2*a] == smax[a]) return find_max(2*a); 
            return find_max(2*a+1);             
        }  

        void add(int a, int b, int val, int id, bool recursive) { 
            if (id != 0) { 
                if (val > 0) { 
                    s.insert(MP(b,id));  
                    win[id] = MP(a,b); 
                } 
                else { 
                    if (!s.count(MP(b,id))) return ; // change was already done
                    s.erase(MP(b,id)); 
                } 
            } 
            
            int va = a + N, vb = b + N; 
            all[va] += val; 

            while (va / 2 != vb / 2) {                 
                if (va % 2 == 0) 
                    all[va + 1] += val; 

                if (vb % 2 == 1) 
                    all[vb - 1] += val; 

                va /= 2; vb /= 2;
                update_node(va); 
                update_node(vb); 
            } 
            while (va / 2 != 0) { 
                va /= 2; 
                update_node(va); 
            }             

            if (!recursive) return ; 
             

            while (smax[1] + all[1] == O) { 
                int tmp=find_max(1) - N;                    
                PII x = *s.lower_bound(MP(tmp+1, 0)); 
                add(win[x.SE].FI, win[x.SE].SE, -1, x.SE, false); 
                result.insert(x.SE); 
                s.erase(x);                 
            } 
        }         
} ; 

rectangle t[2][max_r]; 
event w[max_e];
tree T; 
int n[2]; 

int convert(double x, const vector<double> &vd) { 
    return lower_bound(ALL(vd), x) - vd.begin(); 
} 


int main()
{
   int cc = scanf("%d%d",&n[0], &n[1]); 
   assert(cc == 2);  

    REP(i,2) 
        REP(j,n[i]) 
            t[i][j].get(j+1); 
    
    int pw = 2; 
    rectangle R; 
    set<int> result; 

    while (pw < 1025) { 
        int ec = 0; 
        vector<double> v, vc; 
        FOR(k,1,pw) { 
            int pos = k % 2; 
            REP(i,n[pos]) { 
                v.PB(t[pos][i].xl / k); 
                v.PB(t[pos][i].xu / k); 
            }                 
        } 
        sort(ALL(v)); 
        vc.PB(v[0]); 
        FOR(i,1,SIZE(v)-1) 
            if (!is_zero(v[i] - vc.back())) vc.PB(v[i] + eps / 2); 
       
        double max_val = (double)MAX_H / pw;    

        FOR(k,1,pw) 
        { 
            int pos = k % 2;             
            REP(i,n[pos]) {  
                R = t[pos][i].scale(1.0 / k); 
                if (R.yl >= max_val || R.xu <= -max_val || max_val <= R.xl) 
                    continue;  
                int a = convert(R.xl, vc), b = convert(R.xu, vc); 
                w[ec] = event(R.yl, a, b, ((k == pw)?R.id:0), true); 
                ++ec; 
                w[ec] = event(R.yu, a, b, ((k == pw)?R.id:0), false); 
                ++ec; 
            } 
        }

        sort(w, w + ec); 
        T.init(SIZE(vc), pw); 
        REP(i, ec) { 
            T.add(w[i].x1, w[i].x2, (w[i].add?1:-1), w[i].id, true); 
        } 
        
        FORE(e,T.result) result.insert(*e);  

        pw *= 2; 
    } 
   
    printf("%d\n", SIZE(result));  
    FORE(e, result) printf("%d ",*e); puts("");  

	return 0;
}

