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
    int N, M, K;
    cin >> N >> M >> K;
    vector<string> dna = vector<string>(N);
    set<int> candidates;
    rep(i,0,N) {
        candidates.insert(i);
        cin >> dna[i];
    }
    while (candidates.size() > 1) {
        vector<int> check;
        vector<bool> isChecked(N);
        rep(i,0,N) {
            if (rand()%2) {
                check.push_back(i);
                isChecked[i] = true;
            }
        }
        vector<int> tot[128];
        tot['A'].resize(M);
        tot['C'].resize(M);
        tot['G'].resize(M);
        tot['T'].resize(M);
        for (int i : check) {
            rep(j,0,M) {
                tot[(int)dna[i][j]][j]++;
            }
        }
        set<int> newCandidates;
        for (int i : candidates) {
            int correct = 0;
            rep(j,0,M) {
                correct += tot[(int)dna[i][j]][j];
            }
            if (correct - M*isChecked[i] == (M-K) * ((int)check.size() - isChecked[i])) {
                newCandidates.insert(i);
            }
        }

        candidates = newCandidates;
    }
    cout << (*candidates.begin()) + 1 << endl;
}
