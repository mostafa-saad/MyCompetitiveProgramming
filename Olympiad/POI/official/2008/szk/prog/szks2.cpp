/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szks2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieoptymalne 2 - symulacja z przegladaniem    *
 *             calego brzegu O(S*l)                                      *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)
#define VAR(a,b) __typeof (b) a=b
#define FORE(i,a) for(VAR(i,a.begin()); i!=a.end(); ++i)

#define SP struct point

const int MAX1=150000;
const int MAX2=510000;

SP{
    int kind;
    int crd[2];
};

SP side[MAX2];
int len[MAX1];
int n,m,a,b,x,y,k,c,dir,sz,p;
SP temp,akt;
int bylo[MAX1];

void find(){
    p=(-1);
    REP(j,sz){if ((side[j].crd[0]==temp.crd[0])&&(side[j].crd[1]==temp.crd[1])){p=j; break;}}
}

void ins(int wh){
    side[sz].crd[0]=a;
    side[sz].crd[1]=b;
    side[sz].kind=wh;
    sz++;
}

void make_move(){
    if (dir==0){temp.crd[0]--; temp.crd[1]--;}
    if (dir==1){temp.crd[0]--; temp.crd[1]++;}
    if (dir==2){temp.crd[0]++; temp.crd[1]++;}
    if (dir==3){temp.crd[0]++; temp.crd[1]--;}
}

int pp(int g){return (g+n)%n;}

int main(){
    int rev=0; int c=-1,d;
    scanf("%d\n",&n);
    printf("%d\n",n/2);
    REP(i,n){
        scanf("%d %d\n",&a,&b);
        if (i==0){c=a; d=b;}
        if ((i==1)&&(c==a)){rev=1;}
        len[i]=a+b;
    }
    c=len[n-1];
    a=0; b=0;
    FORD(i,n-1,1){len[i]-=len[i-1];}
    len[0]-=c;
    REP(i,n){
        if ((i+rev)%2){
            if (len[i]>0){
                side[sz].crd[0]=a;
                side[sz].crd[1]=b;
                if (len[pp(i-1)]>0){side[sz].kind=4*i+3;} else {side[sz].kind=4*i+0;}
                sz++;
                FOR(j,1,len[i]-1){a++; ins(-1);} a++;
            } else {
                side[sz].crd[0]=a;
                side[sz].crd[1]=b;
                if (len[pp(i-1)]<0){side[sz].kind=4*i+1;} else {side[sz].kind=4*i+2;}
                sz++;
                FOR(j,1,(-1)*len[i]-1){a--; ins(-1);} a--;
            }
        } else {
            if (len[i]>0){
                side[sz].crd[0]=a;
                side[sz].crd[1]=b;
                if (len[pp(i-1)]>0){side[sz].kind=4*i+3;} else {side[sz].kind=4*i+2;}
                sz++;
                FOR(j,1,len[i]-1){b++; ins(-2);} b++;
            } else {
                    side[sz].crd[0]=a;
                side[sz].crd[1]=b;
                if (len[pp(i-1)]<0){side[sz].kind=4*i+1;} else {side[sz].kind=4*i+0;}
                sz++;
                FOR(j,1,(-1)*len[i]-1){b--; ins(-2);} b--;
            }
        }
    }
    REP(i,sz){
        if (((side[i].kind)>=0)&&(bylo[side[i].kind/4]==0)){
            dir=(side[i].kind)%4;
            printf("%d ",(side[i].kind<4)?n:(side[i].kind/4));
            bylo[side[i].kind/4]=1;
            temp.crd[0]=side[i].crd[0]; temp.crd[1]=side[i].crd[1];
            for(;;){
                find();
                if (p>=0){
                    if ((side[p].kind>=0)&&((((side[p].kind)+2)%4)==dir)){
                        printf("%d\n",(side[p].kind<4)?n:(side[p].kind/4));
                        bylo[side[p].kind/4]=1;
                        break;
                    }
                    if (side[p].kind==(-1)){dir^=1;}
                    if (side[p].kind==(-2)){dir^=3;}
                }
                make_move();
            }
        }
    }
    return 0;
}
