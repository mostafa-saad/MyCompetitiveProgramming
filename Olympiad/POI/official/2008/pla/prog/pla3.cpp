/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla3.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) - prostsza wersja: drzewo *
 *             licznikowe.                                               *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)
#define PB push_back
#define SB struct block

const int zz=262200;
const int MAX=270000;
const int MAX2=700000;
const int inf=200000000;

SB{
    int x;
    int num;
};

int tree[MAX2];
SB dosor[MAX];
int p,q,h,n,k,dump,result,c,j;
SB p1,p2;

int comp(const void *a,const void *b){
    p1=*(SB *)a;
    p2=*(SB *)b;
    if (p1.x!=p2.x){return p1.x-p2.x;} else {return p1.num-p2.num;}
}

void reset(){
    REP(i,2*MAX){tree[i]=0;}
}

void insert(int gdzie){
    p=gdzie+zz;
    while (p>0){tree[p]++; p=(p>>1);}
}

void count(int a,int b){
    p=zz+a-1;
    q=zz+b+1;
    c=0;
    while ((p>>1)!=(q>>1)){
        if (p%2==0){c+=tree[p+1];}
        if (q%2==1){c+=tree[q-1];}
        p=(p>>1); q=(q>>1);
    }
}

int main(){
    reset();
    scanf("%d\n",&n);
    REP(i,n){
        scanf("%d %d\n",&dump,&dosor[i].x);
        dosor[i].num=i;
    }
    qsort(dosor,n,sizeof(SB),comp);
    for(j=0;j<n;j++){
        result++;
        insert(dosor[j].num);
        while((j<(n-1))&&(dosor[j].x==dosor[j+1].x)){
            insert(dosor[j+1].num);
            count(dosor[j].num+1,dosor[j+1].num-1);
            if (c>0){result++;}
            j++;
        }
    }
    printf("%d\n",result);
    return 0;
}
