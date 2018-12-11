#include <bits/stdc++.h>
   
#define forn(i, n) for (ll i = 0; i < n; i++)
#define re return
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define x first
#define y second
#define point pair <int, int>
#define re return
#define se second
#define fi first
#define mp(a, b) make_pair(a, b)
#define mp1(a, b, c, d) make_pair(mp(a, b), mp(c, d))
using namespace std;
typedef long long ll;
const int mod = int(1e9) + 7;
const int ma = 8 * 128 * 1024;
 
int n, m, upper[ma], use[ma], h[ma], fup[ma], cnt = 0;
ll szk[ma];
vector<ll> a, comp;
vector<vector<int> > e;
vector<int> edge[ma];
vector<int> base, nms;
ll ans = 0;
 
void dfs(int nu, int hh) {
    fup[nu] = h[nu] = hh;
    use[nu] = 1;
    nms.push_back(nu);
    int ps = sz(nms);
    for (int v : edge[nu]) {
        if (use[v]) {
            fup[nu] = min(fup[nu], h[v]);
            continue;
        } 
        dfs(v, hh + 1);
        fup[nu] = min(fup[nu], fup[v]);
        if (h[nu] <= fup[v]) {
            base.push_back(nu);
            comp.push_back(0);
            e.push_back({});
            while (sz(nms) > ps) {
                upper[nms.back()] = cnt;
                comp[sz(comp) - 1]++;
                nms.pop_back();
            }
            cnt++;
        }
        ps = sz(nms);
    }
}
 
void dfs2(int nu) {
    szk[nu] = comp[nu];
    for (int v : e[nu]) {
        dfs2(v);
        szk[nu] += szk[v];
    }
}
bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.se < b.se;
}
void dfs3(int nu, ll n) {
    vector<pair<int, int> > c;
    for (int v : e[nu]) {
        dfs3(v, n);
        c.push_back(mp(szk[v], base[v]));
        ans += szk[v] * (n - szk[nu]) * comp[nu];
        //cout << nu << " " << szk[nu] << " " << n << " " << comp[nu] << " " << szk[v] << "\n";
        //cout << ans << "\n";
        ans += szk[v] * (szk[nu] - szk[v] - comp[nu]);
        //cout << ans << "\n";
    }
    sort(c.begin(), c.end(), cmp);
    //if (szk[nu] != n) {
    ll sm = 0;
    forn (i, sz(c)) {
        //cout << c[i].fi << " " << c[i].se << "\n";
        if (i && c[i].se != c[i - 1].se) {
            if (szk[nu] != n)
            ans += (szk[nu] - comp[nu] - sm) * sm * (comp[nu]);
          //  cout << nu << " " << szk[nu] << " " << n << " " << comp[nu] << "\n";
           // cout << ans << "\n";
            sm = 0;
        }
        sm += c[i].fi;
    }
    if (szk[nu] != n)
    ans += (szk[nu] - comp[nu] - sm) * sm * comp[nu];
    //}
    //cout << nu << " " << szk[nu] << " " << n << " " << comp[nu] << "\n";
    //cout << ans << "\n";
    //  cout << (n - szk[nu]) * (comp[nu]) * (szk[nu] - comp[nu]) << " " << 
    //      comp[nu] * (comp[nu] - 1) * (comp[nu] + 1) << " khe\n"; 
    ans += (n - szk[nu]) * (comp[nu]) * (szk[nu] - comp[nu]);
    //cout << ans << "\n";
    ans += comp[nu] * (comp[nu] - 1) * (comp[nu] + 1);
    if (szk[nu] != n) {
        ans += 2LL * comp[nu] * (comp[nu] - 1) * (n - comp[nu] - 1);
        //ans += 2LL * comp[nu] * (n - szk[nu] - 1);
        //ans += 2LL * (szk[nu] - comp[nu]) * comp[nu];
    }
    //cout << ans << "\n";
}
 
int main() {
    iostream::sync_with_stdio(0);
    cin >> n >> m;
    forn (i, m) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    forn (i, n) {
        if (use[i] == 0) {
            dfs(i, 0);
            comp.push_back(1);
            e.push_back({});
            upper[i] = cnt;
            base.push_back(-1);
            a.push_back(cnt);
            cnt++;
        }
    }
    forn (i, cnt) {
        if (base[i] != -1) {
            e[upper[base[i]]].push_back(i);
        }
    }
    for (int v : a) {
        dfs2(v);
        dfs3(v, szk[v]);
    }
    cout << ans << "\n";
    return 0;
}