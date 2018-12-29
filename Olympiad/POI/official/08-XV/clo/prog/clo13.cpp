/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo13.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie alternatywne na podstawie kubelkowego pomyslu *
 *             Adama Iwanickiego. Implementacja listowa zarowno grafu    *
 *             jak i kubelkow.                                           *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

const int MAX_N=100000;
const int MAX_M=400000;

int n,m,licz,a,b,mindeg,bra_licz;
bool flag;
int degree[MAX_N];
int wie[MAX_N];
int sas[MAX_M];
int nas[MAX_M];
int pop[MAX_M];
int match[MAX_N];
int bra[MAX_N];
int bra_sas[MAX_M];
int bra_nas[MAX_M];
int bra_pop[MAX_M];
int where[MAX_N];

/* Graph */

inline void adde(int v1,int v2){
    sas[licz]=v2;
    nas[licz]=wie[v1];
    pop[licz]=-(v1+1);
    if (wie[v1]>=0){pop[wie[v1]]=licz;}
    wie[v1]=licz++;
}

inline void add_edge(int v1,int v2){
    adde(v1,v2); adde(v2,v1);
    degree[v1]++; degree[v2]++;
}

inline void dele(int m){
    if (nas[m]>=0){pop[nas[m]]=pop[m];}
    if (pop[m]>=0){nas[pop[m]]=nas[m];} else {wie[(-pop[m])-1]=nas[m];}
}

inline void delete_edge(int m){
    dele(m); dele(m^1);
}

inline void init_graph(){
    REP(i,n){wie[i]=-1;}
    licz=0;
}

/* Brackets */

inline void add_bracket(int bracket,int v){
    where[v]=bra_licz;
    bra_sas[bra_licz]=v;
    bra_nas[bra_licz]=bra[bracket];
    bra_pop[bra_licz]=-(bracket+1);
    if (bra[bracket]>=0){bra_pop[bra[bracket]]=bra_licz;}
    bra[bracket]=bra_licz++;
}

inline void delb(int m){
    where[bra_sas[m]]=-1;
    if (bra_nas[m]>=0){bra_pop[bra_nas[m]]=bra_pop[m];}
    if (bra_pop[m]>=0){bra_nas[bra_pop[m]]=bra_nas[m];} else {bra[(-bra_pop[m])-1]=bra_nas[m];}
}

inline void init_brackets(){
    REP(i,n){bra[i]=-1;}
    bra_licz=0;
    mindeg=n;
    REP(i,n){add_bracket(degree[i],i); if (mindeg>degree[i]) mindeg=degree[i];}
}

/* Solution */

inline void check_min(){
    while (bra[mindeg]<0) {mindeg++;}
}

inline void solve(){
    flag=true;
    int v,w;
    REP(i,n){
        if (mindeg==0){flag=false; break;}
        v=bra_sas[bra[mindeg]];
        w=sas[wie[v]];
        match[v]=w;
        delb(bra[mindeg]);
        delete_edge(wie[v]);
        if (where[w]>=0){
            degree[w]--;
            delb(where[w]);
            add_bracket(degree[w],w);
        }
        if (degree[w]<mindeg){mindeg=degree[w];}
        check_min();
    }
}

int main(){
    scanf("%d%d",&n,&m);
    init_graph();
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        add_edge(a,b);
    }
    init_brackets();
    solve();
    if (flag){
        printf("TAK\n");
        REP(i,n) printf("%d\n",match[i]+1);
    } else printf("NIE\n");
    return 0;
}
