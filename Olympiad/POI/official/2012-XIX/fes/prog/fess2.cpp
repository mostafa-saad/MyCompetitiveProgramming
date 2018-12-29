/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Festyn                                           *
 *   Autor:             Michal Bejda                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      n razy wykonujemy algorytm Bellmana-Forda        *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;

#define REP(i, n) for(int i=0; i<n; ++i)
#define ST first
#define ND second
#define PB push_back
#define VAR(v,n) __typeof__(n) v=(n)
#define FE(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ALL(c) (c).begin(),(c).end()

#define MAXN 1000+2
#define INF 1000000000

int n;
int M[MAXN][MAXN]; // macierz odleglosci

// Wyznaczanie silnie spojnych skladowych

VI G[MAXN];  // graf wejsciowy
VI Gr[MAXN]; // graf transponowany


int ss[MAXN]; // numer ss wierzcholka
int ord[MAXN]; // wierzcholki w kolejnosci czasow wyjscia
int ssCnt, ordCnt;
bool v[MAXN]; // visited?

int stat[MAXN];

void dfs1(int a){ // pierwszy dfs (do przodu)
    v[a] = true;
    FE(i, G[a]) if ( ! v[*i] ) dfs1(*i);
    ord[ordCnt++] = a;
}

void dfs2(int a, int p){ // drugi dfs (do tylu)
    ss[a] = p;
    v[a] = true;
    FE(i, Gr[a]) if ( ! v[*i] ) dfs2(*i, p);
}

void compute_ssc(){ // funkcja obliczajaca numer ss wierzcholka (ss[])
    fill_n(ss, n, -1);
    fill_n(v, n, false);
    ssCnt = ordCnt = 0;
    
    for(int i=0; i<n; ++i) if ( ! v[i] ) dfs1(i);
    
    fill_n(v, n, false);
    while(ordCnt>0){
        ordCnt--;
        if (! v[ ord[ordCnt] ]) dfs2( ord[ordCnt], ssCnt++ );
    }
}

// obliczanie najdluzszych sciezek w kazdej ss (Floyd-Warshall)

int LP[MAXN][MAXN]; // macierz najdluzszych sciezek
int sslp[MAXN]; // nadluzsze sciezki w kazdej ss

void compute_lp(){
    // dodajemy sztuczny wierzcholek
    int fake = n;
    REP(i, n) {
        M[i][fake] = -INF;
        M[fake][i] = 0;
        G[fake].PB( i );
    }

    // Bellman-Ford ze sztucznego wierzcholka
    REP(i, n) LP[fake][i] = -INF;
    LP[fake][fake] = 0;
    REP(cnt, n){
        REP(u, n+1){
            FE(v, G[u]) if ( M[u][*v] > -INF ) {
                // relaksujemy u -> *v
                LP[fake][*v] = max( LP[fake][*v], LP[fake][u] + M[u][*v] );
            }
        }
    }
    // testujemy obecnosc dodatniego cyklu
    {
        REP(u, n){
            FE(v, G[u]){
                if ( LP[fake][*v] < LP[fake][u] + M[u][*v] ) {
                    printf("NIE\n");
                    exit(0);
                }
            }
        }
    }
/*
    // modyfikujemy wagi krawedzi
    REP(i, n) REP(j, n) if ( M[i][j] > -INF ) {
        M[i][j] = M[i][j] + LP[fake][i] - LP[fake][j];
    }
*/

    REP(i, n) {
        fill_n(stat, MAXN, 0);
    //cout << "od " <<i << endl;
        // algorytm Dijkstry
        // REP(j, n) LP[i][j] = -INF;
        bool change = true;
        while(change){
            change = false;
            REP(u, n){
                FE(v, G[u]) if ( M[u][*v] > -INF ) {
                    if ( LP[i][*v] < LP[i][u] + M[u][*v] ){
                        change = true;
                        LP[i][*v] = LP[i][u] + M[u][*v];
                    }
                }
            }
        }
    
    }
    
    
    
    
    
    REP(i, n) REP(j, n){
    //    LP[i][j] = LP[i][j] - LP[fake][i] + LP[fake][j];
    }
}


int main(){
    ios_base::sync_with_stdio(0);
    int m1, m2;
    cin >> n >> m1 >> m2;
    
    REP(i, n) REP(j, n) LP[i][j] = M[i][j] = (i==j ? 0 : -INF);
    
    while(m1--){
        int a, b;
        cin >> a >> b;
        a--; b--; // przenumerujemy wszystkie wierzcholki na [0...n-1]
        G[a].PB(b);
        G[b].PB(a);
        Gr[b].PB(a);
        Gr[a].PB(b);
        M[a][b] = max(M[a][b], 1);
        M[b][a] = max(M[b][a], -1);
    }
    
    while(m2--){
        int c, d;
        cin >> c >> d;
        c--; d--;
        //if ( M[c][d] != 1 ){ // TODO: zwrocic ERROR!
            G[c].PB(d);
            Gr[d].PB(c);
            M[c][d] = max(M[c][d], 0);
        //}
    }
    
    compute_ssc();
    
    REP(i, n) REP(j, n) if ( ss[i] != ss[j] ) M[i][j] = -INF; // usuwamy krawedzie pomiedzy ss
    
    compute_lp();
    
    REP(i, ssCnt) sslp[i] = 0;
    REP(i, n) REP(j, n) if ( ss[i] == ss[j] ) {
        sslp[ ss[i] ] = max( sslp[ ss[i] ], max(LP[i][j], -LP[j][i]) + 1 );
    }
    
    int result = 0;
    REP(i, ssCnt) result += sslp[i];
    printf("%d\n", result);
return 0;
}

