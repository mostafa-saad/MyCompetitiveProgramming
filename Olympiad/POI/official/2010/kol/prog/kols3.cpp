/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kols3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie powolne; dwukolorowanie grafu                 *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

int RI(){int x; scanf("%d",&x); return x;}

const int minf = -1;

int n;			
vector<int> A;	
vector<int> R;
vector<int> B;
vector<int> colors;

void buildA(){
    n=RI();
    REP(i,n) A.push_back(RI()-1);
    colors=vector<int>(n,-1);
}

void buildR(){
    R=vector<int>(n,0);
    REP(i,n) R[A[i]]=i;
}

void buildB(){
    B=vector<int>(n,0);
    int m=minf;
    REP(i,n)
	B[R[i]]=(m=max(m,R[i]));
}

int isEdge(int v,int w){
    if (v==w) return 0;
    if (v>w) return isEdge(w,v);
    return (A[w]>A[v] && B[v]>=w);
}

void dfs(int v, int c){
    colors[v]=c;
    REP(e,n)
	if (isEdge(v,e)){
	    if (colors[e]==c){
		printf("NIE\n");
		exit(0);
	    }
	    if (colors[e]<0)
		dfs(e,c^1);
	}
}

void buildSolution(){
    REP(t,n) if (colors[t]<0) dfs(t,0);
}

void buildAnswer(){
    printf("TAK\n");
    REP(i,n) printf("%s%d",(i)?" ":"",colors[i]+1);
    printf("\n");
}

int main(){
    buildA();
    buildR();
    buildB();
    buildSolution();
    buildAnswer();
    return 0;
}
