/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szkb3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Heurystyka parzystosciowa, wersja 3.                      *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)
#define SP struct point

const int MAX1=150000;
const int MAX2=510000;

SP {
    int num;
    int val1;
    int val2;
};

int inp[MAX1][2];
int with[MAX1];
int jakie[MAX1];
SP s[4][MAX1];
int c[4];
int a[4];
int n,akt;
int h,e;
SP p1,p2;

int kk(int x){return (x+1)%n;}
int ll(int x){return (x+n-1)%n;}

int how(int s){
    if (akt){
        return (((inp[ll(s)][0]>inp[s][0])?1:0)^((inp[s][1]<inp[kk(s)][1])?1:0));
    } else {
        return (((inp[ll(s)][1]>inp[s][1])?1:0)^((inp[s][0]<inp[kk(s)][0])?1:0));
    }
}

int even(int s){
    return (((inp[s][0]+inp[s][1])%2+2)%2);
}

int comp(const void *x,const void *y){
    p1=*(SP *)x;
    p2=*(SP *)y;
    if (p1.val1==p2.val1){return p1.val2-p2.val2;} else {return p1.val1-p2.val1;}
}

void make(int wh,int i){
    s[wh][c[wh]].num=i;
    if (h==0){
        s[wh][c[wh]].val1=inp[i][0]-inp[i][1];
        s[wh][c[wh]].val2=inp[i][0]+inp[i][1];
    } else {
        s[wh][c[wh]].val1=inp[i][0]+inp[i][1];
        s[wh][c[wh]].val2=inp[i][0]-inp[i][1];
    }
    c[wh]++;
}

void wyp(){
    akt=((inp[0][1]==inp[1][1])?0:1);
//    printf("akt: %d\n",akt);
    REP(i,n){
        h=how(i);
        e=even(i);
//        printf("%d %d\n",h,e);
        if ((h==0)&&(e==0)){make(0,i);}
        if ((h==1)&&(e==0)){make(1,i);}
        if ((h==0)&&(e==1)){make(2,i);}
        if ((h==1)&&(e==1)){make(3,i);}
        akt^=1;
    }
//    REP(i,4){REP(j,c[i]) printf("%d ",s[i][j].num); printf("\n");}
//    printf("TTTT\n");
    REP(i,4){qsort(s[i],c[i],sizeof(SP),comp);}
}

void mc(int p,int q){
    with[p]=q;
    with[q]=p;
}

void do_one(int wh){
    int i;
    for(i=0;i<(c[wh]-1);i++){
        if (s[wh][i].val1==s[wh][i+1].val1){
            mc(s[wh][i].num,s[wh][i+1].num);
            s[wh][i].num=(-1);
            s[wh][i+1].num=(-1);
            i++;
        }
    }
    a[wh]=(-1);
    REP(i,c[wh]){
        if (s[wh][i].num>=0){
            if (a[wh]<0){a[wh]=i;} else {
                mc(s[wh][i].num,s[wh][a[wh]].num);
                s[wh][i].num=(-1);
                s[wh][a[wh]].num=(-1);
                a[wh]=(-1);
            }
        }
    }
}

void match(){
    do_one(0);
    do_one(1);
    do_one(2);
    do_one(3);
    if (a[0]>=0){mc(s[0][a[0]].num,s[1][a[1]].num);}
    if (a[2]>=0){mc(s[2][a[2]].num,s[3][a[3]].num);}
}

void show(){
    REP(i,n){
        if (with[i]>i){
            printf("%d %d\n",i+1,with[i]+1);
        }
    }
}

int main(){
    scanf("%d\n",&n);
    printf("%d\n",n/2);
    REP(i,n){
        scanf("%d %d\n",&inp[i][0],&inp[i][1]);
    }
    wyp();
    match();
    show();
    return 0;
}
