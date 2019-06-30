/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kolb2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *             Heurystyka odkladajaca na stos o nizszym czubku           *
 *             w sytuacjach wyboru.                                      *
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

int RI(){int x; scanf("%d",&x); return x;}

int main(){
    vector<int> result;
    stack<int> st[2];
    int flag, c = 1, k, l, n = RI(), top[2];
    REP(i,2) st[i].push(n+2);
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
	k = RI();
	REP(t,2) top[t]=st[t].top();
	l = -1;
	if (top[0]>k) l=0;
	if (top[1]>k && (l<0 || top[1]<top[0])) l=1;
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
