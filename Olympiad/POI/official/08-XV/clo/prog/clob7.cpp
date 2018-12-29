/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clob7.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne - buduje losowo graf, przydziela  *
 *             zachlannie i probuje rozwiazywac konflikty.               *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

const int MAX_N=100000;
const int MAX_M=400000;

int n,m,licz,a,b,mindeg,bra_licz,k,t;
bool flag;
int wie[MAX_N];
int sas[MAX_M];
int nas[MAX_M];
int kra[MAX_M][2];
int match[MAX_N];
int conflicts[MAX_N][2];

/* Graph */

inline void adde(int v1,int v2){
    sas[licz]=v2;
    nas[licz]=wie[v1];
    wie[v1]=licz++;
}

inline void add_edge(int v1,int v2){
    adde(v1,v2); adde(v2,v1);
}

inline void init_graph(){
    REP(i,n){wie[i]=-1; match[i]=-1;}
    licz=0;
}

inline void shuffle_kra(){
    REP(i,2*m){
        a=rand()%m;
        b=rand()%m;
        swap(kra[a][0],kra[b][0]);
        swap(kra[a][1],kra[b][1]);
    }
}

inline void shuffle_conflicts(){
    REP(i,2*t){
        a=rand()%t;
        b=rand()%t;
        swap(conflicts[a][0],conflicts[b][0]);
        swap(conflicts[a][1],conflicts[b][1]);
    }
}

inline void make_graph(){
    shuffle_kra();
    init_graph();
    REP(i,m) add_edge(kra[i][0],kra[i][1]);
}

bool resolve_conflict(int v1,int v2){
    int g1=wie[v1];
    while (g1>=0){
        if (match[sas[g1]]!=v1) {break;}
        g1=nas[g1];
    }
    int g2=wie[v2];
    while (g2>=0){
        if (match[sas[g2]]!=v2) {break;}
        g2=nas[g2];
    }
    if ((g1<0)&&(g2<0)) return false;
    if (g1<0) match[v2]=sas[g2];
    else
    if (g2<0) match[v1]=sas[g1];
    else
    if (rand()%2) match[v2]=sas[g2]; else match[v1]=sas[g1];
    return true;
}

void solve(){
    flag=true;
    make_graph();
    t=0;
    REP(i,n){
        if (wie[i]<0){flag=false; return;}
        match[i]=sas[wie[i]];
        if (i==match[match[i]]){
            conflicts[t][0]=i;
            conflicts[t][1]=match[i];
            t++;
        }
    }
    if (t>0) shuffle_conflicts();
    REP(i,t) {
        if (!resolve_conflict(conflicts[i][0],conflicts[i][1])) {flag=false; break;}
    }
}

int main(){
    srand(time(0));
    scanf("%d%d",&n,&m);
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        kra[i][0]=a; kra[i][1]=b;
    }
    int t=0;
    while ((!flag)&&(t<5)){solve(); t++;}
    if (flag){
        printf("TAK\n");
        REP(i,n) printf("%d\n",match[i]+1);
    } else printf("NIE\n");
    return 0;
}
