/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kols1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie powolne.                                      *
 *   Zlozonosc czasowa: O(n*2^n)                                         *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

inline int RI(){int x; scanf("%d",&x); return x;}

const int MAX  = 	100100;

int n;

int A[MAX];

/* czyta wejscie */
inline void buildA(){
    n=RI();
    REP(i,n) A[i]=RI()-1;
}

int c=0;		/* jaki jest kolejny element do zdjecia */
stack<int> st[2];	/* stosy do zdejmowania */

/* zdejmuje ze stosow tyle, ile mozna */
void flush(){
    int flag;
    for(;;){
        flag = 1;
        REP(t,2) if (st[t].top()==c){
	    c++;
	    st[t].pop();
	    flag = 0;
	}
	if (flag) break;
    }
}

/* wyciaga zapalenie i-tego bitu z m */
#define C(i,m) (!!(m&(1<<i)))

/* sprawdza, czy rozwiazanie z mask jest poprawne */
bool checkSolution(unsigned int mask){
    c=0;
    REP(i,2) st[i].push(n+2);
    REP(i,n){
	st[C(i,mask)].push(A[i]);
	flush();
    }
    return (c>=n);
}

/* buduje i wypisuje odpowiedz na wyjscie */
inline bool tryBuildAnswer(unsigned int mask){
    if (checkSolution(mask)){
	printf("TAK\n");
	REP(i,n) printf("%s%d",(i)?" ":"",C(i,mask)+1);
	printf("\n");
	return true;
    }
    return false;
}

int main(){
    buildA();
    REP(t,1<<((n<=30)?n:30))
        if (tryBuildAnswer(t)) return 0;
    printf("NIE\n");
    return 0;
}
