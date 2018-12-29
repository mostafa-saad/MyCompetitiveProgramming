/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Multidrink                                    *
 *   Autor:                Krzysztof Leszczynski                         *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe,                         *
 *                         zachlanny wybor o najwyzszym priorytecie      *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int MAX=500010;

int n;
vector<int> graf[MAX];
bool lisc[MAX];
bool mainRoad[MAX];
int vis[MAX];
int visCounter;
int priorytet[MAX];
int st[MAX];

void read()
{
    int a,b;
    if(scanf("%d", &n)==EOF);
    for(int i=0; i<n-1; i++) {
        if(scanf("%d%d", &a,&b)==EOF);
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    for(int i=1; i<=n; i++) {
        for(vector<int>::iterator it=graf[i].begin(); it!=graf[i].end(); it++) if(graf[*it].size()>1) st[i]++;
    }
    for(int i=1; i<=n; i++) graf[i].push_back(i);
}

void ustawLiscie()
{
    for(int i=1; i<=n; i++) {
        if(graf[i].size()==2) lisc[i]=true;
    }
    lisc[1]=false;
    lisc[n]=false;
}

bool dfs(int a) {
    if(a==n) return true;
    vis[a]=visCounter;
    for(vector<int>::iterator it=graf[a].begin(); it!=graf[a].end(); it++) {
        if(vis[*it]==visCounter) continue;
        mainRoad[a]|=dfs(*it);
    }
    return mainRoad[a];
}

void znajdzSciezke() {
    mainRoad[n]=true;
    visCounter++;
    dfs(1);
}

void posortuj() {
    for(int i=1; i<=n; i++) {
        bool bol=1;
        while(bol) {
            bol=0;
            for(int j=graf[i].size()-1; j>0; j--) {
                if(lisc[graf[i][j]]<lisc[graf[i][j-1]]) {
                    bol=1;
                    swap(graf[i][j],graf[i][j-1]);
                }
            }
        }
    }
}

vector<int> odp;
void dfs2(int a) {
    vis[a]=visCounter;
    int max_pri=-1;
    int max_ind=0;

    if(lisc[a]) {
        for(int i=graf[graf[a][0]].back(); lisc[i]; i=graf[graf[a][0]].back()) {
            odp.push_back(i);
            graf[graf[a][0]].pop_back();
        }
    }
    else odp.push_back(a);

    for(vector<int>::iterator it=graf[a].begin(); it!=graf[a].end(); it++) {
        if(lisc[*it]) break;
        for(vector<int>::iterator jt=graf[*it].begin(); jt!=graf[*it].end(); jt++) {
            if(vis[*jt]==visCounter) continue;
            if(priorytet[*jt]>max_pri) {
                max_ind=*jt;
                max_pri=priorytet[*jt];
            }
            if(lisc[*jt]) break;
        }
    }
    if(max_ind!=0) return dfs2(max_ind);
}

void nadajPriorytet(int a, int par) {
    vis[a]=visCounter;
    if(mainRoad[a]) priorytet[a]=priorytet[par]-1;
    else {
        if(mainRoad[par]) priorytet[a]=priorytet[par]+n;
        else priorytet[a]=priorytet[par]+2;
        if(lisc[a]) priorytet[a]++;
    }
    for(vector<int>::iterator it=graf[a].begin(); it!=graf[a].end(); it++) if(vis[*it]!=visCounter) nadajPriorytet(*it,a);
}

void znajdzOdpowiedz() {
    visCounter++;
    dfs2(1);
}

bool sprawdzOdpowiedz() {
    visCounter++;
    for(vector<int>::iterator it=odp.begin(); it!=odp.end(); it++) {
        if(vis[*it]==visCounter) return false;
        vis[*it]=visCounter;
    }
    for(int i=1; i<=n; i++) if(vis[i]!=visCounter) return false;
    if(odp.front()!=1 || odp.back()!=n) return false;
    return true;
}

int main()
{
    read();
    for(int i=1; i<=n; i++) if(st[i]>5) {
            printf("BRAK\n");
            return 0;
        }
    ustawLiscie();
    znajdzSciezke();
    posortuj();
    priorytet[1]=n;
    visCounter++;
    nadajPriorytet(1,1);
    znajdzOdpowiedz();
    if(!sprawdzOdpowiedz()) {
        printf("BRAK\n");
        return 0;
    }
    for(vector<int>::iterator it=odp.begin(); it!=odp.end(); it++) printf("%d\n", *it);
    return 0;
}
