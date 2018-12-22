#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " _ " <<
#define INF 2000000000

#include <iostream>
#include <cassert>
using namespace std;

int tournament[600000];
int offset;

// Vrati prvi i >= oznaka t.d. a[i] <= stanica
int f(int oznaka, int stanica, int x, int lo, int hi) {
    if (x >= offset) {
        assert(lo + 1 == hi);
        return lo;
    }
    int mid = (lo + hi) / 2;
    if (mid > oznaka && tournament[x * 2] <= stanica) {
        int lijevo = f(oznaka, stanica, x * 2, lo, mid);
        if (lijevo != INF)
            return lijevo;
    }
    if (tournament[x * 2 + 1] > stanica)
        return INF;
    return f(oznaka, stanica, x * 2 + 1, mid, hi);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    offset = 1;
    while (offset < n)
        offset *= 2;
    FOR(i, 1, 2 * offset)
        tournament[i] = INF;
    REP(it, q) {
        char type;
        int stanica, oznaka;
        cin >> type >> stanica >> oznaka;
        oznaka -= 1;
        if (type == 'M')
            for (int k = offset + oznaka; k > 0; k /= 2)
                tournament[k] = min(tournament[k], stanica);
        else {
            int sol = f(oznaka, stanica, 1, 0, offset);
            if (sol == INF)
                cout << -1 << endl;
            else
                cout << sol + 1 << endl;
        }
    }
}
