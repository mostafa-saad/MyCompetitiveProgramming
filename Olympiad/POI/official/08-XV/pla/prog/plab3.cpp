/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     plab3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie hybrydowe O(n^2), sprytny brute-force         *
 *             +dla duzych n scinanie zbioru poszukiwan.                 *
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
int last[MAX];
int hei[MAX];
int n,result,dump,k,akt,nx,t,ok,c,m,x;
SB p1,p2;

int comp(const void *a,const void *b){
    p1=*(SB *)a;
    p2=*(SB *)b;
    if (p1.h==p2.h){return p1.num-p2.num;} else {return p1.h-p2.h;}
}

void reindex(){
    qsort(input,n,sizeof(SB),comp);
    c=0;
    REP(i,n){
        hei[input[i].num]=c;
        if ((i<n-1)&&(input[i].h!=input[i+1].h)){c++;}
    }
    c++;
}

int main(){
    scanf("%d\n",&n);
    REP(i,n){
        scanf("%d %d\n",&dump,&input[i].h);
        input[i].num=i;
    }
    reindex();
    REP(i,c){last[i]=(-1);}
    m=MAX; result=0;
    if (n>20020){x=2010;} else {x=10010;}
    REP(i,n){
        akt=hei[i];
        if (last[akt]<0){
            if (akt<m){m=akt;}
            last[akt]=i;
            result++;
        } else {
            ok=0;
            if ((akt-m)<(i-last[akt])){
                if ((akt-m)<2*x){
                    FORD(j,akt-1,m){
                        if ((last[akt]<=last[j])&&(last[j]<=i)){ok=1; break;}
                    }
                } else {
                    FORD(j,akt-1,akt-x){
                        if ((last[akt]<=last[j])&&(last[j]<=i)){ok=1; break;}
                    }
                    if (!ok){
                        FORD(j,m+x,m){
                            if ((last[akt]<=last[j])&&(last[j]<=i)){ok=1; break;}
                        }
                    }
                }
            } else {
                if ((i-last[akt])<2*x){
                    FOR(j,last[akt]+1,i-1){
                        if (hei[j]<akt){ok=1; break;}
                    }
                } else {
                    FOR(j,last[akt]+1,last[akt]+x){
                        if (hei[j]<akt){ok=1; break;}
                    }
                    if (!ok){
                        FOR(j,i-x,i-1){
                            if (hei[j]<akt){ok=1; break;}
                        }
                    }
                }
            }
            if (ok){result++;}
            last[akt]=i;
        }
    }
    printf("%d\n",result);
    return 0;
}
