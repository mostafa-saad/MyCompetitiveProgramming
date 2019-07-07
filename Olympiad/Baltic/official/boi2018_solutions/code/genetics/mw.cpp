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

using bs = bitset<4100>;

int main(){
	ios::sync_with_stdio(0);
    int N, M, K;
    cin >> N >> M >> K;
    vector<bs> dna = vector<bs>(N);
    vector<int> hammingWeight(N);
    set<int> candidates;
    rep(i,0,N) {
        candidates.insert(i);
        string s;
        cin >> s;
        rep(j,0,M) {
            if (s[j] == '1')
                dna[i].set(j);
        }
        hammingWeight[i] = dna[i].count();
    }
    while (candidates.size() > 1) {
        bs check;
        rep(i,0,N) {
            if (rand()%2) {
                check.flip(i);
            }
        }
        int checkCount = check.count();
        vector<int> tot(M);
        rep(i,0,N) {
            if (check.test(i)) {
                rep(j,0,M) {
                    tot[j] += dna[i].test(j);
                }
            }
        }
        int totWeight = accumulate(all(tot), 0);
        set<int> newCandidates;
        for (int i : candidates) {
            int totalDot = 0;
            rep(j,0,M) {
                totalDot += tot[j] * dna[i].test(j);
            }
            int totDist = checkCount * hammingWeight[i] + totWeight - totalDot * 2;
            if (totDist == K * (checkCount - check.test(i))) {
                newCandidates.insert(i);
            }
        }

        candidates = newCandidates;
    }
    cout << (*candidates.begin()) + 1 << endl;
}
