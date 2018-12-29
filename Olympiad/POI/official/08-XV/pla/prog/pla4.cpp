/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla4.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) - listy wskaznikowe       *
 *             wedlug pomyslu Marcina Kubicy.                            *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)
#define SE struct elem
#define SB struct block

SE{
    int val;
    int next;
    int prev;
};

SB{
    int num;
    int h;
};

const int MAX=270000;

SE list[MAX];
SB input[MAX];
int n,result,dump,k;
SB p1,p2;

void reset(){
    list[0].prev=0;
    list[0].next=1;
    list[0].val=(-1);
    FOR(i,1,n){
        list[i].prev=i-1;
        list[i].next=i+1;
        list[i].val=input[i].h;
    }
    list[n+1].prev=n;
    list[n+1].next=n+1;
    list[n+1].val=(-1);
}

int nx_val(int g){return list[list[g].next].val;}

void del(int g){
    list[list[g].next].prev=list[g].prev;
    list[list[g].prev].next=list[g].next;
}

int comp(const void *a,const void *b){
    p1=*(SB *)a;
    p2=*(SB *)b;
    if (p1.h==p2.h){return p1.num-p2.num;} else {return p2.h-p1.h;}
}

int main(){
    scanf("%d\n",&n);
    FOR(i,1,n){
        scanf("%d %d\n",&dump,&input[i].h);
        input[i].num=i;
    }
    reset();
    qsort(input+1,n,sizeof(SB),comp);
    FOR(i,1,n){
        k=input[i].num;
        if (list[k].val!=nx_val(k)){result++;}
        del(k);
    }
    printf("%d\n",result);
    return 0;
}
