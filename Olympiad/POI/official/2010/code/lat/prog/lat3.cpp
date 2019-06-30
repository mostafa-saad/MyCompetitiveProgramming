/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Latarnia (LAT)                                   *
 *   Plik:              lat3.cpp                                         *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie weryfikujace.                        *
 *   Zlozonosc czasowa: O((n + m) * W * log ((n + m) * W))               *
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

#define RATT int
struct Rational{
	RATT top,bot;
	
    Rational():top(0),bot(1){}
	Rational(RATT t):top(t),bot(1){}
	Rational(RATT t,RATT b):top(t),bot(b){}
	
	/* Operatory porownawcze */
	#define OPER1(op) bool operator op (const Rational &b) const
	OPER1(==) {
		return top*b.bot == b.top*bot;
	}
	OPER1(<) {
		return top*b.bot < b.top*bot;
	}
	OPER1(>) { return b<*this; } /* Wymaga < */
	OPER1(<=) { return !(b<*this); } /* Wymaga < */
	OPER1(>=) { return !(*this<b); } /* Wymaga < */
	OPER1(!=) { return !(*this==b); } /* Wymaga == */
};
typedef vector<Rational> VR;

VR val;
const int tsize=3388699;
struct range_tree_scaled{
    int T[tsize],MX[tsize],m;
    void init(){
        sort(ALL(val));
        val.erase(unique(ALL(val)),val.end());
        m=SIZE(val);
        CLR(T,0); CLR(MX,0);
    }   
    void update(int x,int l,int r,int tl,int tr,int tv){
        if( l==tl && r==tr)
            T[x]+=tv;    
        else{
            int s=(l+r)/2;
            if(tr <= s) update(x*2,l,s,tl,tr,tv);
            else if(s <= tl) update(x*2+1,s,r,tl,tr,tv);
            else{
                update(x*2,l,s,tl,s,tv);
                update(x*2+1,s,r,s,tr,tv);
            }
        }
        if(l+1 == r) MX[x]=T[x];
        else MX[x]=T[x]+max(MX[x*2],MX[x*2+1]);
    }
    int range(int x,int l,int r,int tl,int tr){
        if( l==tl && r==tr)
            return T[x];
        int s=(l+r)/2;
        if(tr <= s) return range(x*2,l,s,tl,tr);
        else if(s <= tl) return range(x*2+1,s,r,tl,tr);
        else return range(x*2,l,s,tl,s) + range(x*2+1,s,r,s,tr);
    }
    void update(Rational l,Rational r,int v){
        update(1, 0, m-1 ,lower_bound(ALL(val), l)-val.begin(),
                lower_bound(ALL(val), r)-val.begin(), v);
    }
    int find_occ(int x,int l,int r){
        while(l+1 != r){
            int s=(l+r)/2;
            if(MX[x*2] >= MX[x*2+1]){
                x=x*2;
                r=s;
            }else{
                x=x*2+1;
                l=s;
            } 
        }
        return l;
    }
    Rational find_occ(){
        return val[find_occ(1, 0, m-1)];
    }
};
struct event{
    Rational y;
    int id;
    void set(Rational _y, int _id){
        y=_y;
        id=_id;
    }
    bool operator<(const event &e) const{
        if (y!=e.y) return y < e.y;
        return id < e.id;
    }
} E[tsize];

const int nmx=607;
int n[2];
int X[2][nmx][2], Y[2][nmx][2];
bool BR[nmx];
range_tree_scaled R;

inline bool inrec(int i,int d, Rational x, Rational y){
    return Rational(X[0][i][0],d) <= x && x < Rational(X[0][i][1],d) &&
            Rational(Y[0][i][0],d) <= y && y< Rational(Y[0][i][1],d);
}

int main(){
    REP(i,2) scanf("%d",n+i);
    REP(i,2){
        REP(j, n[i]){
            REP(k,2) scanf("%d%d",X[i][j]+k, Y[i][j]+k);
        }
    }
    bool RM[nmx];
    FOR(m, 0, 9){
        CLR(RM,0);
        val.clear();
        int d=1;
        int en=0;
        REP(j, 1<<m){
            FORD(k,1,0){
                REP(i, n[k]){
                    val.PB( Rational(X[k][i][0], d));
                    val.PB( Rational(X[k][i][1], d)); 
                    E[en++].set(Rational(Y[k][i][0],d), i+1);
                    E[en++].set(Rational(Y[k][i][1],d), -i-1);      
                }
                d++;
            }
        }
        R.init();
        sort(E, E+en);
        int it=0;
        int den = 2*(1<<m);
        while(it < en){
            Rational y = E[it].y;
            while(it < en && E[it].y == y){
                int d = E[it].y.bot;
                int k = d%2;
                int id=E[it].id;
                int v=1;
                if (id < 0){
                    v=-1;
                    id=-id;
                }
                id--;
                if(!(v==-1 && d == den && RM[id]))
                    R.update(Rational(X[k][id][0],d), Rational(X[k][id][1],d), v);
                it++;
            }
            while(R.MX[1] == den){
               Rational x = R.find_occ();
               REP(i,n[0]) if(inrec(i, den, x, y)){
                    RM[i]=1;
                    BR[i]=1;
                    R.update(Rational(X[0][i][0],den), Rational(X[0][i][1],den), -1);
    
               }
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
