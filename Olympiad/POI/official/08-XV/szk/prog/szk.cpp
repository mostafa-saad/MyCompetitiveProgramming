/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szk.cpp                                                   *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(l*log l) (l - obwod figury).       *
 *             Implementacja w C++ bez uzywania STL.                     *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)
#define SP struct point

const int MAX1=150000;
const int MAX2=510000;

SP {
    int x;
    int y;
    int ver;
    int num;
};
/* struct dla punktu */

SP p1,p2;

int comp1(const void *aa,const void *bb){
    p1=*(SP *)aa;
    p2=*(SP *)bb;
    if (p1.x!=p2.x) return (p1.x-p2.x); else return (p1.y-p2.y);
}
/* comparator porzadku 0 */

int comp2(const void *aa,const void *bb){
    p1=*(SP *)aa;
    p2=*(SP *)bb;
    if (p1.y!=p2.y) return (p1.y-p2.y); else return (p1.x-p2.x);
}
/* comparator porzadku 1 */

int len[MAX1];                // dlugosci kolejnych bokow
int next[MAX2][2];        // sasiedzi w porzadkach
SP side[MAX2];                // obwod 
int n,m,akt,a,b,c,p;

void make_next(int wh){
    qsort(side,n,sizeof(SP),(wh)?comp2:comp1);
    akt=(-1);
    REP(i,n){
        if ((side[i].ver>=0)&&((side[i].ver%2)!=wh)){next[side[i].num][wh]=(-side[i].ver/2-1); continue;}
        if (akt<0){akt=i;} else {next[side[akt].num][wh]=side[i].num; next[side[i].num][wh]=side[akt].num; akt=(-1);}
    }
}
// wypelnianie sasiadow

void insert(){
    side[n].x=a-b;
    side[n].y=a+b;
    side[n].ver=(-1);
    side[n].num=n;
    n++;
}
// wstawianie punktu z obwodu

void find(int fr){
    p=fr; akt=((next[fr][0]>=0)?0:1);
    for(;;){if (next[p][akt]<0){break;} else {p=next[p][akt]; akt^=1;}}
    p=(next[p][akt]*=(-1));
}
// znajdowanie sparowanego wierzcholka

int pp(int k){return (k+m)%m;}

int main(){
    scanf("%d\n",&m);
    printf("%d\n",m/2);
    REP(i,m){
        scanf("%d %d\n",&a,&b);
        len[i]=a+b;
    }
    c=len[m-1];
    FORD(i,m-1,1){len[i]-=len[i-1];}
    len[0]-=c;
    // obliczamy dlugosci bokow 
    a=0; b=0;
    REP(i,m){
        if (i%2){
            if (len[i]>0){
                REP(j,len[i]){insert(); a++;}
                side[n-len[i]].ver=((len[pp(i-1)]>0)?(2*i+1):(2*i));
            } else {
                REP(j,(-1)*len[i]){insert(); a--;}
                side[n+len[i]].ver=((len[pp(i-1)]<0)?(2*i+1):(2*i));
            }
        } else {
            if (len[i]>0){
                REP(j,len[i]){insert(); b++;}
                side[n-len[i]].ver=((len[pp(i-1)]>0)?(2*i+1):(2*i));
            } else {
                REP(j,(-1)*len[i]){insert(); b--;}
                side[n+len[i]].ver=((len[pp(i-1)]<0)?(2*i+1):(2*i));
            }
        }
    }
    // tworzymy obwod
    make_next(0); make_next(1);
    // oraz listy sasiadow
    REP(i,n){
        if ((next[i][0]<0)||(next[i][1]<0)){
            find(i);
            printf("%d %d\n",pp(((next[i][0]<0)?(next[i][0]*(-1)):(next[i][1]*(-1)))-2)+1,pp(p-2)+1);
        }
    }
    // i znajdujemy sparowanie
    return 0;
}
