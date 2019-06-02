/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kolb8.cpp                                                 *
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

int I[1000000];

int RI(){int x; scanf("%d",&x); return x;}

stack<int> st[2];
stack<int> st2[2];
int d;

bool ok(int s, int i){
    int flag,l;
    int top[2];
    for(;;){
	flag = 1;
	REP(t,2) if (st2[t].top()==d){
	    d++;
	    st2[t].pop();
	    flag = 0;
	}
	if (flag) break;
    }
    if (d>=s) return true;
    int k=I[i];
    REP(t,2) top[t]=st[t].top();
    l = -1;
    if (top[0]>k) l=0;
    if (top[1]>k && (l<0 || top[1]<top[0])) l=1;
    if (l<0) return false;
    st2[l].push(k);    
    return ok(s,i+1);
}

int main(){
    vector<int> result;
    int flag, c = 1, k, l, n = RI(), top[2];
    REP(i,2) st[i].push(n+2);
    REP(i,n) I[i]=RI();
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
	    d=c;
	    st2[0]=st[0]; st2[1]=st[1];
	    st2[g].push(k);
	    int o = ok(k,i);
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
