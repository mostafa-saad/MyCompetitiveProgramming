/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 mos7.cpp                                      *
 *   Autor:                Miroslaw Michalski                            *
 *   Opis:                 Rozwiazanie alternatywne.                     *
 *                         Pomysl podobny do Kosci z XII OI.             *
 *                         Brak losowego kierowania.                     *
 *   Zlozonosc czasowa:    O((n + m) * m * log MAX_WIATR)                *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <stack>

const int MAXN = 1007;
const int MAXM = 2007;
const int MAXMM = 8*MAXM;
const int INF = 1000000000;

struct kraw{
    int a, b, l, r;
    kraw(){}
    kraw(int _a, int _b, int _l, int _r): a(_a), b(_b), l(_l), r(_r){}
};

::std::map< ::std::pair<int, int>, int> edges;
::std::vector< ::std::pair<int, int> > t[MAXN];
::std::vector< ::std::pair<int, int> > tmp[MAXN];
::std::vector<kraw> v;
::std::pair<int, int> info[MAXMM];
int n, m;

bool check(int x) {
    int deg[MAXN], dist[MAXN];
     ::std::pair<int, int> prev[MAXMM];
    for(int i=0; i<n; i++) {
        t[i].clear();
        tmp[i].clear();
        deg[i] = 0;
    }
    int kr = 0;
    for(int i=0; i<m; i++) {
        if (v[i].l <= x && v[i].r <=x) {
            t[v[i].a].push_back(::std::make_pair(v[i].b, kr));
            t[v[i].b].push_back(::std::make_pair(v[i].a, kr+1));
            
            info[kr] = ::std::make_pair(kr+1, 1);
            info[kr+1] = ::std::make_pair(kr, 0);
            kr+=2;
            deg[v[i].a]++;
            deg[v[i].b]--;
        } else
            if (v[i].l <= x) {
                deg[v[i].a]++;
                deg[v[i].b]--;
                tmp[v[i].a].push_back(::std::make_pair(v[i].b, i));
            } else
                if (v[i].r <= x) {
                    deg[v[i].a]--;
                    deg[v[i].b]++;
                    tmp[v[i].b].push_back(::std::make_pair(v[i].a, i));
                } else
                    return false;
    }
    ::std::vector<int> check;
    for(int i=0; i<n; i++) if (deg[i] > 0) check.push_back(i);

    for(::std::vector<int>::iterator it=check.begin(); it!=check.end(); it++) {
        while (deg[*it] >= 2) {
            ::std::queue<int> q;
            for(int i=0; i<n; i++) {
                dist[i] = INF;
                prev[i] = ::std::make_pair(-1, -1);
            }
            q.push(*it);
            dist[*it] = 0;
            int finish = -1;

            while (!q.empty()) {
                int w = q.front(); q.pop();
                for(::std::vector< ::std::pair<int, int> >::iterator neigh=t[w].begin(); neigh!=t[w].end();
                        neigh++) 
                    if (dist[neigh->first] == INF && info[neigh->second].second) { 
                        dist[neigh->first] = dist[w]+1;
                        prev[neigh->first] = ::std::make_pair(w, neigh->second);
                        q.push(neigh->first);
                        if (deg[neigh->first] <= -2) {
                            finish = neigh->first;
                            break;
                        }
                    }
            }
            if (finish == -1) return false;
            int f = finish;
            while (prev[f].first!=-1) {
                int n_kraw = prev[f].second;
                info[n_kraw].second = 0;
                info[info[n_kraw].first].second = 1;
                f = prev[f].first;
            }
            deg[*it]-=2;
            deg[finish]+=2;
            if (deg[*it] == 1) return false;
        }
    }
    for(int i=0; i<n; i++)
        if (deg[i]!=0) return false;
    return true;
}

void getCycle() {
    for(int i=0; i<n; i++) {
        for(size_t j=0; j<t[i].size(); j++) {
            if (info[t[i][j].second].second)
            tmp[i].push_back(::std::make_pair(t[i][j].first, edges[::std::make_pair(i, t[i][j].first)]));
        }
    }
    ::std::stack< ::std::pair<int, int> > s1;
    ::std::vector<int> wynik;
    bool used[MAXM];
    for(int i=0; i<MAXM; i++)
        used[i] = false;
    
    s1.push(::std::make_pair(0, -1));
    while (!s1.empty()) {
        int w = s1.top().first; 
        for(size_t i=0; i<tmp[w].size(); i++) if (!used[tmp[w][i].second]) {
            used[tmp[w][i].second]=true;
            s1.push(tmp[w][i]);
            break;
        }
        if (s1.top().first == w) {
            wynik.push_back(s1.top().second);
            s1.pop();
        }
    }
    for(int i=wynik.size()-2; i>=0; i--)
        printf("%d ",wynik[i]+1);
    printf("\n");
}

int main() {
    int a, b, l, r, be = 0, en = 0,mid, d[MAXN];
    for(int i=0; i < MAXN; i++) d[i] = 0;
    srand(0);
    scanf("%d%d",&n, &m);
    for(int i=0; i<m; i++) {
        scanf("%d%d%d%d",&a, &b, &l, &r);
        a--; b--;
        v.push_back(kraw(a, b, l, r));

        edges[::std::make_pair(a, b)] = i;
        edges[::std::make_pair(b, a)] = i;
        
        be = ::std::max(be, ::std::min(l, r));
        en = ::std::max(en, ::std::max(l, r));
        d[a]++;
        d[b]++;
    }
    for(int i=0; i<n; i++) if (d[i]%2!=0) {
        printf("NIE\n");
        return 0;
    }

    while (be < en) {
        mid = be + (en-be)/2;
        if (check(mid)) en = mid; else be = mid+1;
    }
    check(be);
    printf("%d\n",be);
    getCycle();
    return 0;
}


