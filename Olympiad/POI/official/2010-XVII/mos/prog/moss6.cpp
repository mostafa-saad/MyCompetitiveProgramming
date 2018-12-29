/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mosty (MOS)                                               *
 *   Plik:     moss6.cpp                                                 *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             Szukamy sciezki za pomoca DFSa.                           *
 *             Nie używamy wyszukiwania binarnego.                       *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

const int MAXN = 1007;
const int MAXM = 2007;
const int MAXMM = 8*MAXM;
const int INF = 1000000000;

int n, m, st, en, edges = 0;
int deg[MAXN];
::std::vector< ::std::pair<int, int> > tab[MAXN];
::std::vector< ::std::pair< ::std::pair<int, int>, ::std::pair<int, int> > > t;

int T;
::std::vector< ::std::pair<int, int> > flow[MAXN+MAXM]; // [sasiad, numerID]
::std::pair<int, int> info[MAXMM]; // [waga_krawedzi, wskaznik na wstecz]
::std::pair<int, int> track[MAXMM]; 
bool core[MAXMM];

void addEdge(int a, int b, int x, int wh = 0, int dir = 0) {
    flow[a].push_back(::std::make_pair(b, edges));
    flow[b].push_back(::std::make_pair(a, edges+1));

    core[edges] = true;
    core[edges+1] = false;

    track[edges] = ::std::make_pair(wh, dir);

    info[edges] = ::std::make_pair(x, edges+1);
    info[edges+1] = ::std::make_pair(0, edges);
    edges+= 2;
}

::std::vector<int> path;
bool visited[MAXN+MAXM];
bool findPath(int s) {
    if (s == T) return true;
    if (visited[s]) return false;
    visited[s] = true;
    for(size_t i=0; i<flow[s].size(); i++)
        if (info[flow[s][i].second].first > 0 && !visited[flow[s][i].first] && findPath(flow[s][i].first)) {
            path.push_back(flow[s][i].second);
            return true;
        }
    return false;
}

bool getFlow(int value, int goFurther=0) {
    edges = 0;
    for(int i=0; i<n+m+1; i++) flow[i].clear();
    for(size_t i=0; i<t.size(); i++) {
        int a = t[i].first.first, b = t[i].first.second;
        int p = t[i].second.first, q = t[i].second.second;
        if (p <= value && q <= value) {
            addEdge(a+1, n+i+1, 1, i, 0); 
            addEdge(b+1, n+i+1, 1, i, 1);
        } else 
            if (p <= value) {
                addEdge(a+1, n+i+1, 1, i, 0);
            } else
                if (q <= value) {
                    addEdge(b+1, n+i+1, 1, i, 1);
                } else return false;
    }
    for(int i=0; i<n; i++) {
        addEdge(0, i+1, deg[i]/2);
    }
    for(int i=0; i<m; i++) {
        addEdge(n+i+1, n+m+1, 1);
    }

    T = n+m+1;
    int fl = 0;
    for(int i=0; i<=T; i++) visited[i] = false;
    while (findPath(0)) {
        fl++;
        for(size_t i=0; i<path.size(); i++) {
            info[path[i]].first--;
            info[info[path[i]].second].first++;
        }
        for(int i=0; i<=T; i++) visited[i] = false;
        path.clear();
    }
    if (!goFurther) 
        return (fl == m);
    for(int i=0; i<edges-2*(m+n); i++) if (!info[i].first && core[i]) {
        if (track[i].second) tab[t[track[i].first].first.second].push_back(::std::make_pair(t[track[i].first].first.first, track[i].first)); else
            tab[t[track[i].first].first.first].push_back(::std::make_pair(t[track[i].first].first.second, track[i].first));
    }
    ::std::stack< ::std::pair<int, int> > s1;
    ::std::vector<int> wynik;
    bool used[MAXM];
    for(int i=0; i<MAXM; i++)
        used[i] = false;
    
    s1.push(::std::make_pair(0, -1));
    while (!s1.empty()) {
        int w = s1.top().first; 
        for(size_t i=0; i<tab[w].size(); i++) if (!used[tab[w][i].second]) {
            used[tab[w][i].second]=true;
            s1.push(tab[w][i]);
            break;
        }
        if (s1.top().first == w) {
            wynik.push_back(s1.top().second);
            s1.pop();
        }
    }
    printf("%d\n",value);
    for(int i=wynik.size()-2; i>=0; i--)
        printf("%d ",wynik[i]+1);
    printf("\n");
    return (fl==m);
}


int main() {
    st = 0, en=0;
    scanf("%d%d",&n, &m);
    int a, b, l, r;
    for(int i=0; i<m; i++) {
        scanf("%d%d%d%d", &a, &b, &l, &r);
        a--; b--;
        deg[a]++; deg[b]++;
        t.push_back(::std::make_pair(::std::make_pair(a, b), ::std::make_pair(l, r)));
        st = ::std::max(st, ::std::min(l, r));
        en = ::std::max(en, ::std::max(l, r));
    }
    for(int i=0; i<n; i++) if (deg[i]%2!=0) {
        printf("NIE\n"); 
        return 0;
    }
    
    while (!getFlow(st)) {
        st++;
    }
    getFlow(st, 1);
    return 0;
}
