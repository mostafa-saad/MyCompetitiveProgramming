#include <bits/stdc++.h>
using namespace std;

int n,m,k;
vector<vector<int>> C(300001, vector<int>());
vector<int> colors;
int ans = 0;
bool mark[5] = {0};

void brute(int i){
    mark[colors[i]] = 1;
    for(int c1 = 0; c1 < C[i].size(); c1++){
        int j = C[i][c1];
        if(!mark[colors[j]]){
            ans++;
            brute(j);
        }
    }
    mark[colors[i]] = 0;
}

int main() {
    cin >> n >> m >> k;
    assert(n <= 100 && m <= 100 && k <= 4);
    for(int c1 = 0; c1 < n; c1++){
        int a;
        cin >> a;
        colors.push_back(a);
    }
    for(int c1 = 0; c1 < m; c1++){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        C[a].push_back(b);
        C[b].push_back(a);
    }
    for(int c1 = 0; c1 < n; c1++)brute(c1);
    cout << ans << "\n";
    return 0;
}
