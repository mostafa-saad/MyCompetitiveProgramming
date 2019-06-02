/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo14.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie na BFS-ie przy uzycia listowej reprezentacji  *
 *             grafu.                                                    *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

const int MAX_N=100000;
const int MAX_M=400000;

int n,m,licz,a,b,kolp,kolk;
bool flag,temp_flag;
int bylo[MAX_N];
int wie[MAX_N];
int sas[MAX_M];
int nas[MAX_M];
int kol[MAX_N][2];
int match[MAX_N];

inline void adde(int v1,int v2){
    sas[licz]=v2;
    nas[licz]=wie[v1];
    wie[v1]=licz++;
}

inline void add_edge(int v1,int v2){
    adde(v1,v2); adde(v2,v1);
}

inline void init_graph(){
    REP(i,n){wie[i]=-1;}
    licz=0;
}

void bfs_1(int p){
    int v,from,where;
    kolp=1; kolk=0;
    kol[0][0]=p; kol[0][1]=-1;
    while (kolp>kolk){
        v=kol[kolk][0]; from=kol[kolk][1];
        bylo[v]=1;
        where=wie[v];
        while (where>=0){
            if (sas[where]!=from){
                if (bylo[sas[where]]) {a=sas[where]; match[a]=v; temp_flag=true; break;}
                bylo[sas[where]]=1;
                kol[kolp][0]=sas[where];
                kol[kolp][1]=v;
                kolp++;
            }
            where=nas[where];
        }
        if (temp_flag) break;
        kolk++;
    }
}

void bfs_2(int p){
    int v,where;
    kolp=1; kolk=0;
    kol[0][0]=p;
    while (kolp>kolk){
        v=kol[kolk][0];
        bylo[v]=2;
        where=wie[v];
        while (where>=0){
            if ((bylo[sas[where]]<2)&&(sas[where]!=match[v])) {
                match[sas[where]]=v;
                bylo[sas[where]]=2;
                kol[kolp][0]=sas[where];
                kolp++;
            }
            where=nas[where];
        }
        kolk++;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    init_graph();
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        add_edge(a,b);
    }
    REP(i,n){
        if (!bylo[i]){
            temp_flag=false;
            bfs_1(i);
            flag=temp_flag;
            if (!flag) break;
            bfs_2(a);
        }
    }
    if (flag){
        printf("TAK\n");
        REP(i,n) printf("%d\n",match[i]+1);
    } else printf("NIE\n");
    return 0;
}
