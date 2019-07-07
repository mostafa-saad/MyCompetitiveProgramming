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
vector<vl> C(300001, vl());
vl colors;

ll DP1[300001][5] = {0};
ll DP2[300001][5][5] = {0};

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("autput.txt","w",stdout);
    ll a,b,c,e;
    cin >> n >> m >> k;
    for(int c1 = 0; c1 < n; c1++){
        cin >> a;
        a--;
        colors.push_back(a);
    }
    for(int c1 = 0; c1 < m; c1++){
        cin >> a >> b;
        a--;
        b--;
        C[a].push_back(b);
        C[b].push_back(a);
    }

    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < sz(C[c1]); c2++){
            DP1[c1][colors[C[c1][c2]]]++;
        }
    }

    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < sz(C[c1]); c2++){
            for(int c3 = 0; c3 < 5; c3++){
                int c4 = colors[C[c1][c2]];
                DP2[c1][min(c3,c4)][max(c3,c4)] += DP1[C[c1][c2]][c3];
            }
        }
    }

    ll ans1 = 0;
    ll ans2 = 0;
    ll ans3 = 0;
    ll ans4 = 0;

    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < 5; c2++){
            if(c2 == colors[c1])continue;
            ans1 += DP1[c1][c2];
            for(int c3 = c2+1; c3 < 5; c3++){
                if(c3 == colors[c1])continue;
                ans2 += DP1[c1][c2]*DP1[c1][c3];
                ans2 += DP1[c1][c3]*DP1[c1][c2];
                for(int c4 = c3+1; c4 < 5; c4++){
                    if(c4 == colors[c1])continue;
                    ans3 += DP1[c1][c2]*DP2[c1][c3][c4];
                    ans3 += DP1[c1][c3]*DP2[c1][c2][c4];
                    ans3 += DP1[c1][c4]*DP2[c1][c2][c3];
                    for(int c5 = c4+1; c5 < 5; c5++){
                        if(c5 == colors[c1])continue;
                        ans4 += DP2[c1][c2][c3]*DP2[c1][c4][c5];
                        ans4 += DP2[c1][c2][c4]*DP2[c1][c3][c5];
                        ans4 += DP2[c1][c2][c5]*DP2[c1][c3][c4];
                        ans4 += DP2[c1][c3][c4]*DP2[c1][c2][c5];
                        ans4 += DP2[c1][c3][c5]*DP2[c1][c2][c4];
                        ans4 += DP2[c1][c4][c5]*DP2[c1][c2][c3];
                    }
                }
            }
        }
    }

    cout << ans1+ans2+ans3+ans4 << "\n";

    return 0;
}
