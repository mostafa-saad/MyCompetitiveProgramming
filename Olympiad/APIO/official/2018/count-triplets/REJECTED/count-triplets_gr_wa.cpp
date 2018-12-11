#include <bits/stdc++.h>
 
using namespace std;
 
const int MX = 200 * 1000 + 7;
 
using ll = long long;
 
vector<pair<int, int> > g[MX];
vector<pair<int, int> > gg[MX];
 
int was[MX];
ll ans = 0;
ll sz[MX];
ll dp[MX];
int p[MX];
int cid[MX];
ll csz[MX];
int ccnt = 0;
 
ll solve(const vector<ll>& a) {
    ll ans = 0;
    ll sm = 0;
    for (ll x : a) {
        ans -= x * x;
        sm += x;
    }
    ans += sm * sm;
    return ans / 2;
}
 
void dfs(int v) {
    was[v] = true;
    sz[v] = csz[v];
    dp[v] = 0;
    ll pans = 0;
    ll sdp = 0;
    ll ssz = 0;
    map<int, vector<ll> > cnt;
    for (const auto& toe : g[v]) {
        int to = toe.first;
        if (!was[to]) {
            dfs(to);
            sz[v] += sz[to];
            cnt[toe.second].push_back(sz[to]);
            dp[v] += dp[to];
            dp[v] += 1ll * csz[v] * sz[to];
            ans += 1ll * csz[v] * dp[to];
            sdp += dp[to];
            ssz += sz[to];
            pans -= 1ll * dp[to] * sz[to];
        }
    }
 
    pans += 1ll * ssz * sdp;
    ans += pans;
    vector<ll> go;
    for (const auto& v : cnt) {
        ans += solve(v.second);
        ll sm = 0;
        for (ll x : v.second) {
            sm += x;
        }
        go.push_back(sm);
    }
    ans += csz[v] * solve(go);
}
 
void dfs1(int v, int pp = -1) {
    was[v] = 1;
    for (auto& toe : gg[v]) {
        int to = toe.first, toid = toe.second;
        if (was[to] == 1 && toid != pp) {
            int vv = v;
            ccnt++;
            while (vv != to) {
                csz[ccnt]++;
                cid[vv] = ccnt;
                vv = p[vv];
            }
            csz[ccnt]++;
            cid[vv] = ccnt;
        } else if (was[to] == 0) {
            p[to] = v;
            dfs1(to, toid);
        }
    }
    was[v] = 2;
}
 
 
ll c3(ll x) {
    return x * (x - 1) * (x - 2) / 6;
}
 
ll c2(ll x) {
    return x * (x - 1) / 2;
}
 
void dfs3(int v, ll tot) {
    was[v] = true;
    ans += c2(csz[v] - 1) * (tot - csz[v]) * 4;
    ans += (csz[v] - 1) * (tot - csz[v]) * 2;
    for (const auto& to : g[v]) {
        if (!was[to.first]) {
            dfs3(to.first, tot);
        }
    }
}
 
int cv = 0, ce = 0;
 
void dfs4(int v) {
    was[v] = true;
    cv++;
    ce += gg[v].size();
    for (auto& to : gg[v]) {
        if (!was[to.first]) {
            dfs4(to.first);
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<pair<int, int> > edges;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        gg[u].emplace_back(v, i);
        gg[v].emplace_back(u, i);
        edges.emplace_back(u, v);
    }
 
    for (int i = 1; i <= n; i++) {
        if (!was[i]) {
            dfs1(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cid[i] == 0) {
            ccnt++;
            cid[i] = ccnt;
            csz[ccnt] = 1;
        }
    }
 
    for (const auto& e : edges) {
        if (cid[e.first] != cid[e.second]) {
            g[cid[e.first]].emplace_back(cid[e.second], e.first);
            g[cid[e.second]].emplace_back(cid[e.first], e.second);
        }
    }
 
    memset(was, 0, sizeof(was));
 
    for (int i = 1; i <= ccnt; i++) {
        if (!was[i]) {
            dfs(i);
        }
    }
 
    ans *= 2;
 
    ll a2 = 0;
    for (int i = 1; i <= ccnt; i++) {
        ans += c3(csz[i]) * 6;
        a2 += c3(csz[i]) * 6;
    }
     
    memset(was, 0, sizeof(was));
    for (int i = 1; i <= ccnt; i++) {
        if (!was[i]) {
            dfs3(i, sz[i]);
        }
    }
 
    cout << ans << "\n";
}