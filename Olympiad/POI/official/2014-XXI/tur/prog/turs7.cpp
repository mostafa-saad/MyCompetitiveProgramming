/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Turystyka                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(8^t * (n+m))                                *
 *                         (t - dlugosc najdluzszej sciezki w grafie)    *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
typedef long long LL;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin(); i != (x).end(); ++i)

const int MAXT = 10;
const int MAXN = 20000;
const int INF = 1000000000;
const int MASKS = 1<<(MAXT);

int n,m,c[MAXN+7]; // wartosci z wejscia
vector<int> G[MAXN+7]; // graf
int res; // wynik
int h[MAXN+7];
bool vis[MAXN+7];

inline void mini(int& a,int b) {
    a = min(a,b);
}

vector<vector<int> > join(vector<vector<int> > a, vector<vector<int> > b, int t) {
    vector<vector<int> > c(1<<(t-1), vector<int>(1<<(t-1), INF));
    int one = 1<<(t-1);
    REP(X,1<<t) REP(Y,1<<t)
    if(Y&one)
        REP(Z,1<<(t-1))
        mini(c[X&(~one)][(Y|Z)&(~one)], a[X][Y] + b[X&(~one)][Z]);
    return c;
}

int value(vector<vector<int> > v) {
    return min(v[0][1], v[1][1]);
}

vector<vector<int> > dfs(int x,int hh) {
    vis[x] = true;
    h[x] = hh;
    int nei = 0, one = 1<<hh;
    vector<vector<int> > dp(1<<(hh+1), vector<int>(1<<(hh+1), INF));
    FORE(i,G[x])
    if(vis[*i])
        nei |= 1<<h[*i];
    REP(m,1<<hh) {
        dp[m][m|(m<<1)|(m>>1)|((bool)(m & nei) ? one : 0)] = 0;
        dp[m|one][m|(m<<1)|(m>>1)|one|nei] = c[x];
    }
    FORE(i,G[x])
    if(!vis[*i])
        dp = join(dfs(*i, hh+1), dp, hh+2);
    return dp;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    // wczytanie wejscia
    cin >> n >> m;
    for(int i=1; i<=n; i++)
        cin >> c[i];
    while(m--) {
        int a,b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    // rozwiazanie
    for(int i=1; i<=n; i++)
        if(!vis[i])
            res += value(dfs(i,0));
    // wypisanie wyniku
    cout << res << endl;
}
