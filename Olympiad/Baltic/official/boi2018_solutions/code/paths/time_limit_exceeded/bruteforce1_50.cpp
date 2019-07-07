// Bruteforces first k-1 nodes, uses memoization on the last.
// Also never visits leaves, in order to deal with star graphs.
// Should only get the first 2 subtasks.

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;

const ll big = 1000000007;
const ll mod = 998244353;

ll n,m,k;
vi colors;
vector<vi> graph(300001, vi());
vector<vi> nonleaves(300001, vi());

ll ncolors[300001][5] = {0};
ll ans = 0;
bool mark[5] = {0};

void brute(int i, int visited){
    mark[colors[i]] = 1;
    for(int c1 = 0; c1 < k; c1++){
        if(!mark[c1])ans += ncolors[i][c1];
    }
    if(visited < k-1){
        for(int c1 = 0; c1 < sz(nonleaves[i]); c1++){
            int a = nonleaves[i][c1];
            if(!mark[colors[a]]){
                brute(a,visited+1);
            }
        }
    }
    mark[colors[i]] = 0;
    return;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("autput.txt","w",stdout);
    ll a,b,c,e;

    cin >> n >> m >> k;

    for(int c1 = 0; c1 < n; c1++){
        cin >> a;
        colors.push_back(a-1);
    }
    for(int c1 = 0; c1 < m; c1++){
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        ncolors[a][colors[b]]++;
        ncolors[b][colors[a]]++;
    }
    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < sz(graph[c1]); c2++){
            a = graph[c1][c2];
            if(sz(graph[a]) != 1){
                nonleaves[c1].push_back(a);
            }
        }
    }
    for(int c1 = 0; c1 < n; c1++){
        brute(c1,1);
    }
    cout << ans << "\n";
    return 0;
}
