/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Festyn                                           *
 *   Autor:             Michal Bejda                                     *
 *   Opis:              Rozwiazanie powolne, wykladnicze                 *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <bitset>

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

#define MAXN 1000
#define INF 1000000000

int M[MAXN][MAXN]; // [i] + M[i][j] <= [j]
int T[MAXN];
bool U[MAXN];
int n;

bool validTime(int a){
    REP(i, a) if ( !  ( T[i] + M[i][a] <= T[a] && T[a] + M[a][i] <= T[i] )  ) return false;
    return true;
}

int ddSize(){
    fill_n(U, n, false);
    REP(i, n) {
        U[ T[i] ] = true;
    }
    int result = 0;
    REP(i, n) result += U[i];
    return result;
}

int assign(int a){
    if ( a == n ) return ddSize();
    int result = -1;
    REP(i, n) {
        T[a] = i;
        if ( validTime( a ) ) {
            result = max( result, assign( a + 1 ) );
        }
    }
    return result;
}

int main(){
    ios_base::sync_with_stdio(0);
    int m1, m2;
    cin >> n >> m1 >> m2;
    
    REP(i, n) REP(j, n) M[i][j] = -INF;
    
    while(m1--){
        int a, b;
        cin >> a >> b;
        a--; b--; // przenumerujemy wszystkie wierzcholki na [0...n-1]
        M[a][b] = max(M[a][b], 1);
        M[b][a] = max(M[b][a], -1);
    }
    
    while(m2--){
        int c, d;
        cin >> c >> d;
        c--; d--;
        M[c][d] = max(0, M[c][d]);
    }
    
    int result = assign(0);
    if ( result < 0 ) cout << "NIE" << endl;
    else cout << result << endl;
return 0;
}

