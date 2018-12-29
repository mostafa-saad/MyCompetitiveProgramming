/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clob6.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne - przeglada wzdluz stopni         *
 *             wierzcholkow (przy rownym losowo) i przydziela losowo,    *
 *             robi kilka razy.                                          *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <ctime>
#include <cstdlib>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

const int MAX_N=100000;
const int MAX_M=400000;

int n,m,licz,a,b,mindeg,bra_licz,k;
bool flag;
int degree[MAX_N][2];
int wie[MAX_N];
int sas[MAX_M];
int nas[MAX_M];
int pop[MAX_M];
int match[MAX_N];

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
    degree[v1][0]++; degree[v2][0]++;
}

inline void dele(int m){
    if (nas[m]>=0){pop[nas[m]]=pop[m];}
    if (pop[m]>=0){nas[pop[m]]=nas[m];} else {wie[(-pop[m])-1]=nas[m];}
}

inline void delete_edge(int m){
    dele(m); dele(m^1);
}

inline void init_graph(){
    REP(i,n){wie[i]=-1; degree[i][1]=i;}
    licz=0;
}

int comp(const void *a,const void *b){
    int* x=(int*) a;
    int* y=(int*) b;
    if (x[0]!=y[0]) return x[0]-y[0]; else return ((x[1]%k)-(y[1]%k));
}

void solve(){
    flag=true;
    k=7+rand()%30;
    qsort(degree,n,2*sizeof(int),comp);
    int v,where;
    REP(i,n){
        v=degree[i][1];
        where=wie[v];
        if (where<0){flag=false; break;}
        while ((nas[where]>=0)&&(!(rand()%4))) where=nas[where];
        match[v]=sas[where];
        delete_edge(where);
    }
}

int main(){
    srand(time(0));
    scanf("%d%d",&n,&m);
    init_graph();
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        add_edge(a,b);
    }
    int t=0;
    while ((!flag)&&(t<5)){solve(); t++;}
    if (flag){
        printf("TAK\n");
        REP(i,n) printf("%d\n",match[i]+1);
    } else printf("NIE\n");
    return 0;
}
