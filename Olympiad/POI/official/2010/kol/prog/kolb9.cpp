/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kolb9.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *             Nieco zmieniona heurystyka Wojtka Tyczynskiego            *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define PB(x)	push_back(x)
#define REP(i,n) for ( int i = 0 ; i < int(n) ; i++ )
#define FOR(i,a,b) for (int i = int(a) ; i <= int(b) ; i++ )
#define minf -1
#define SZ size()

int I[1000000];
int R[1000000];
int B[1000000];

int RI(){int x; scanf("%d",&x); return x;}

stack<int> st[2];
int n;

inline void buildR(){
    REP(i,n) R[I[i]]=i;
}

inline void buildB(){
    int m=minf;
    REP(i,n)
	B[R[i]]=(m=max(m,R[i]));
}


bool ok(int i,int v){
    vector<int> inp;
    int k = I[i];
    inp.PB(v);
    int g=B[i]; if (g==minf) g=n-1;
    FOR(j,i+1,g)
	if (I[j]>k) inp.PB(I[j]);
    REP(j,inp.SZ-1)
	if (inp[j]<inp[j+1]) return false;
    return true;
}

int main(){
    vector<int> result;
    int flag, c = 1, k, l, top[2];
    n=RI();
    REP(i,2) st[i].push(n+2);
    REP(i,n) I[i]=RI();
    buildR();
    buildB();
    REP(i,n){
	for(;;){
	    flag = 1;
	    REP(t,2) if (st[t].top()==c){
		c++;
		st[t].pop();
		flag = 0;
	    }
	    if (flag) break;
	}
	k = I[i];
	REP(t,2) top[t]=st[t].top();
	l = -1;
	if (top[0]>k && top[1]>k){
	    int g = (top[0]>top[1])?0:1;
	    int o = ok(i,top[g^1]);
	    if (o) l=g; else l=(g^1);
	} else {
	    if (top[0]>k) l=0;
	    if (top[1]>k && (l<0 || top[1]<top[0])) l=1;
	}
	if (l<0){
	    printf("NIE\n");
	    return 0;
	}
	st[l].push(k);
	result.PB(l+1);
    }
    printf("TAK\n");
    REP(i,n) printf("%s%d",(i)?" ":"",result[i]);
    printf("\n");
    return 0;
}
