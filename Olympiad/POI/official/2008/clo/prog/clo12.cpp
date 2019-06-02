/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo12.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie na dfs-ie przy uzyciu listowej reprezentacji  *
 *             grafu.                                                    *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

const int MAX_N=100000;
const int MAX_M=400000;

int n,m,licz,a,b;
bool flag,temp_flag;
int bylo[MAX_N];
int wie[MAX_N];
int sas[MAX_M];
int nas[MAX_M];
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

void dfs_1(int v,int from){
    bylo[v]=1;
    int next=wie[v];
    while (next>=0){
        if (temp_flag){break;}
        if (sas[next]!=from){
            if (bylo[sas[next]])
                {match[sas[next]]=v; temp_flag=true; a=sas[next];} 
            else
                {dfs_1(sas[next],v);}
        }
        next=nas[next];
    }
}

void dfs_2(int v,int from){
    bylo[v]=2;
    match[v]=from;
    int next=wie[v];
    while (next>=0){
        if ((bylo[sas[next]]<2)&&(sas[next]!=from)) dfs_2(sas[next],v);
        next=nas[next];
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
            dfs_1(i,-1);
            flag=temp_flag;
            if (!flag) break;
            dfs_2(a,match[a]);
        }
    }
    if (flag){
        printf("TAK\n");
        REP(i,n) printf("%d\n",match[i]+1);
    } else printf("NIE\n");
    return 0;
}
