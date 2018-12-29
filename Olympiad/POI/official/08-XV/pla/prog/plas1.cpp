/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     plas1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^2), przeszukiwanie           *
 *             horyzontalne zwykla implementacja.                        *
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
#define SB struct block

SB{
    int h;
    int num;
};

const int MAX=270000;

SB input[MAX];
int hei[MAX];
int n,result,dump,k,akt,nx,t,ok;
SB p1,p2;

int comp(const void *a,const void *b){
    p1=*(SB *)a;
    p2=*(SB *)b;
    if (p1.h==p2.h){return p1.num-p2.num;} else {return p1.h-p2.h;}
}

int main(){
    scanf("%d\n",&n);
    REP(i,n){
        scanf("%d %d\n",&dump,&input[i].h);
        input[i].num=i;
        hei[i]=input[i].h;
    }
    qsort(input,n,sizeof(SB),comp);
    for(t=0;t<n;t++){
        result++;
        akt=input[t].h;
        while((t<n-1)&&(akt==input[t+1].h)){
            ok=0;
            FOR(s,input[t].num+1,input[t+1].num-1){if (hei[s]<akt){ok=1; break;}}
            result+=ok;
            t++;
        }
    }
    printf("%d\n",result);
    return 0;
}
