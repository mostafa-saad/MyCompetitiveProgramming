/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Autor programu:       Michal Glapa                                       *
 *   Zlozonosc czasowa:    O(n^2qd)                                           *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
using namespace std;
int MOD, n;
typedef vector<vector<int > > matrix;

vector<array<int,3> > queries;
matrix graph;

matrix empty_matrix() {
    vector<vector<int> > res (n, vector<int>(n,0));
    return res;
}
void read() {
	ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m >> MOD;
    graph = empty_matrix();
    while(m--) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        graph[a][b] = 1;
    }
    int q;
    cin >> q;
    queries.resize(q);
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        queries[i][0] = a;
        queries[i][1] = b;
        cin >> queries[i][2];
    }
}

int solve_query(array<int,3> & q) {
    if (q[2] < 2)
        return graph[q[0]][q[1]];
    auto dp = graph[q[0]];
    q[2]-=2;
    while(q[2]--)
    {
        vector<int> tmp(n);
        for(int from = 0; from < n; from++)
            for(int to = 0; to < n; to++) {
                if(to == q[0] || to == q[1] || from == q[0] || from == q[1])
                    continue;
                tmp[to] += graph[from][to] * dp[from];
                tmp[to] %= MOD;
            }
        dp = tmp;
    }
    int res = 0;
    for ( int i = 0; i < n; i++)
        if ( graph[i][q[1]] )
            res = ( res + dp[i] ) % MOD;
    return res;

}

int main()
{
    read();
    for(auto &i : queries)
        cout << solve_query(i) << endl;
}

