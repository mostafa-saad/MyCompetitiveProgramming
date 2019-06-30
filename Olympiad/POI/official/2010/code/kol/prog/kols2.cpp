/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kols2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie powolne; backtracking                         *
 *   Zlozonosc czasowa: O(2^d) gdzie d jest liczba wyborow               *
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

const int MAX = 100100;

int c=0;
int n;
int A[MAX];
int colors[MAX];
int flag;
stack<int> st[2];
    
void buildA(){
    n=RI();
    REP(i,n) A[i]=RI()-1;
}

void backtrack(int w){
    int cp=c;
    stack<int> popped[2];
    for(;;){
	flag = 1;
	REP(t,2) if (st[t].top()==c){
	    popped[t].push(c);
	    c++;
	    st[t].pop();
	    flag = 0;
        }
        if (flag) break;
    }
    if (c==n){
        printf("TAK\n");
        REP(i,n) printf("%s%d",(i)?" ":"",colors[i]);
        printf("\n");
        exit(0);
    }
    REP(t,2){
        if (st[t].top()>A[w]){
            st[t].push(A[w]);
            colors[w]=t+1;
            backtrack(w+1);
	    st[t].pop();
    	}
    }
    REP(t,2){
	while (!(popped[t].empty())){
	    st[t].push(popped[t].top());
	    popped[t].pop();
	}
    }
    c=cp;
}

int main(){
    buildA();
    REP(i,2) st[i].push(n+2);
    backtrack(0);
    printf("NIE\n");
    return 0;
}
