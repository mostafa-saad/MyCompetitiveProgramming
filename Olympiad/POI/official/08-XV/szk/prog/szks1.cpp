/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szks1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieoptymalne 1 - symulacja na secie z STL     *
 *             O(S*log l).                                               *
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
#define F first
#define S second

const int MAX1=150000;
const int MAX2=510000;

struct point{
    int kind;
    int crd[2];
};

struct comp{
    bool operator ()(const point & xx,const point & yy) const
    {
        if (xx.crd[0]!=yy.crd[0])
                return (xx.crd[0]<yy.crd[0]);
        else
            return (xx.crd[1]<yy.crd[1]);
    }
};

set <point,comp> Side;
int len[MAX1];
int n,m,a,b,x,y,k,c,dir;
SP temp;
int bylo[MAX1];

void ins(int wh){
    temp.crd[0]=a;
    temp.crd[1]=b;
    temp.kind=wh;
    Side.insert(temp);
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
                temp.crd[0]=a;
                temp.crd[1]=b;
                if (len[pp(i-1)]>0){temp.kind=4*i+3;} else {temp.kind=4*i+0;}
                Side.insert(temp);
                FOR(j,1,len[i]-1){a++; ins(-1);} a++;
            } else {
                temp.crd[0]=a;
                temp.crd[1]=b;
                if (len[pp(i-1)]<0){temp.kind=4*i+1;} else {temp.kind=4*i+2;}
                Side.insert(temp);
                FOR(j,1,(-1)*len[i]-1){a--; ins(-1);} a--;
            }
        } else {
            if (len[i]>0){
                temp.crd[0]=a;
                temp.crd[1]=b;
                if (len[pp(i-1)]>0){temp.kind=4*i+3;} else {temp.kind=4*i+2;}
                Side.insert(temp);
                FOR(j,1,len[i]-1){b++; ins(-2);} b++;
            } else {
                    temp.crd[0]=a;
                temp.crd[1]=b;
                if (len[pp(i-1)]<0){temp.kind=4*i+1;} else {temp.kind=4*i+0;}
                Side.insert(temp);
                FOR(j,1,(-1)*len[i]-1){b--; ins(-2);} b--;
            }
        }
    }
    __typeof (Side.begin()) akt;
    FORE(it,Side){
        if (((it->kind)>=0)&&(bylo[it->kind/4]==0)){
            dir=(it->kind)%4;
            printf("%d ",(it->kind<4)?n:(it->kind/4));
            bylo[it->kind/4]=1;
            temp=(*it);
            for(;;){
                akt=Side.find(temp);
                if (akt!=Side.end()){
                    if ((akt->kind>=0)&&((((akt->kind)+2)%4)==dir)){
                        printf("%d\n",(akt->kind<4)?n:(akt->kind/4));
                        bylo[akt->kind/4]=1;
                        break;
                    }
                    if (akt->kind==(-1)){dir^=1;}
                    if (akt->kind==(-2)){dir^=3;}
                }
                make_move();
            }
        }
    }
    return 0;
}
