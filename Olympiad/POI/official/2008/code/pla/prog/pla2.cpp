/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla2.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) za pomoca drzew           *
 *             przedzialowych wedlug pomyslu Marka Cygana.               *
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

const int zz=262200;
const int MAX=270000;
const int MAX2=700000;
const int inf=2000*1000*1000;

typedef vector<int> VI;

int tree[MAX2];
int local_left[30];
int local_right[30];
int p,q,h,n,k,dump,result,c_l,c_r;

void reset(){
    REP(i,2*MAX){tree[i]=inf;}
}

void insert(int gdzie,int co){
    p=gdzie+zz;
    while ((p>0)&&(tree[p]>co)){tree[p]=co; p=(p>>1);}
}

void ff(int gdzie,VI &aku){
    if ((gdzie>=zz)&&(tree[gdzie]=h)){aku.PB(gdzie-zz);} else {
        if (tree[gdzie<<1]==h){ff(gdzie<<1,aku);}
        if (tree[(gdzie<<1)+1]==h){ff((gdzie<<1)+1,aku);}
    }
}

void find(int a,int b,VI &aku){
    p=a+zz-1;
    q=b+zz+1;
    h=inf;
    while ((p>>1)!=(q>>1)){
        if (((p%2)==0)&&(tree[p+1]<h)){h=tree[p+1];}
        if (((q%2)==1)&&(tree[q-1]<h)){h=tree[q-1];}
        p=(p>>1); q=(q>>1);
    }
    p=a+zz-1;
    q=b+zz+1;
    c_l=0; c_r=0;
    while ((p>>1)!=(q>>1)){
        if ((p%2==0)&&(tree[p+1]==h)){local_left[c_l++]=(p+1);}
        if ((q%2==1)&&(tree[q-1]==h)){local_right[c_r++]=(q-1);}
        p=(p>>1); q=(q>>1);
    }        
    FOR(i,0,c_l-1){ff(local_left[i],aku);}
    FORD(i,c_r-1,0){ff(local_right[i],aku);}
}

void zaglebiaj(int lo,int hi){
    if (lo<=hi){
        result++;
        VI cur;
        find(lo,hi,cur);
        int m=cur.size();
        zaglebiaj(lo,cur[0]-1);
        REP(i,m-1){
            zaglebiaj(cur[i]+1,cur[i+1]-1);
        }
        zaglebiaj(cur[m-1]+1,hi);
    }
}

int main(){
    reset();
    scanf("%d\n",&n);
    REP(i,n){
        scanf("%d %d\n",&dump,&k);
        insert(i,k);
    }
    zaglebiaj(0,n-1);
    printf("%d\n",result);
    return 0;
}
