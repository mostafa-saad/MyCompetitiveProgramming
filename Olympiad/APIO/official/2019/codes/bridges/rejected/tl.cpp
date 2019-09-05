#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double dbl;
#define pb push_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define all(a) a.begin(),a.end()
bool debug = 0;
const int MAXN = 5e4+100;
const int LOG = 20;
const int mod = 998244353;
const int MX = 2e5 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
int w[2*MAXN];
 
vector<pii> g[MAXN];
 
int ans = 0;
char used[MAXN];
void dfs(int v,int w_mx){
    ans++;
    used[v] =1;
    for(pii x:g[v]){
        int to = x.fi;
        if(!used[to] && w[x.se] >= w_mx){
            dfs(to,w_mx);
        }
    }
}
 
void solve() {
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;++i){
        int a,b;
        cin >> a >> b >> w[i];
        g[a].pb({b,i});
        g[b].pb({a,i});
    }
    int q;
    cin >> q;
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int b,x;
            cin >> b >> x;
            w[b] = x;
        } else{
            int s,w_mx;
            cin >> s >> w_mx;
            memset(used,0,sizeof used);
            ans = 0;
            dfs(s,w_mx);
            cout << ans<<"\n";
        }
    }
 
}
 
signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
#else
 
#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
 
    int t = 1;
 
    while (t--)
        solve();
    dout << endl<<"time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}
