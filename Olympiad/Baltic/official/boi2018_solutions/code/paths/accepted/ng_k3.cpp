#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m,k,a,b;
    cin >> n >> m >> k;
    assert(k <= 3);
    vector<int> colors(n);
    vector<vector<int>> graph(n,vector<int>());
    for(int c1 = 0; c1 < n; c1++){
        cin >> colors[c1];
        colors[c1]--;
    }
    for(int c1 = 0; c1 < m; c1++){
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    long long ans = 0;
    for(int c1 = 0; c1 < n; c1++){
        long long F[3] = {0};
        for(int c2 = 0; c2 < graph[c1].size(); c2++){
            F[colors[graph[c1][c2]]]++;
        }
        F[colors[c1]] = 0;
        ans += 2*(F[0]*F[1]+F[0]*F[2]+F[1]*F[2])+F[0]+F[1]+F[2];
    }
    cout << ans << "\n";
    return 0;
}
