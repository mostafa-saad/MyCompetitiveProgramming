#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(auto &it : (v))
#define all(v) (v).begin(), (v).end()
#define what_is(x) cerr << #x << " is " << x << endl;
#define sz(x) (int)(x).size()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

int main(){
	ios::sync_with_stdio(0);
    int N, K, R;
    cin >> N >> K >> R;
    vector<int> dna(N);
    rep(i,0,N) {
        cin >> dna[i];
    }
    vector<int> need(K+1);
    rep(i,0,R) {
        int B, Q;
        cin >> B >> Q;
        need[B] = Q;
    }
    int bad = R;
    int r = 0;
    int ans = N+1;
    for (int l = 0; l < N; l++) {
        while (bad > 0 && r < N) {
            need[dna[r]]--;
            if (need[dna[r]] == 0) {
                --bad;
            }
            r++;
        }
        if (bad == 0) {
            ans = min(ans, r-l);
        }
        need[dna[l]]++;
        if (need[dna[l]] == 1) {
            ++bad;
        }
    }
    if (ans == N+1)
        cout << "impossible" << endl;
    else
        cout << ans << endl;
}
