/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Labirynt                                      *
 *   Autor:                Maciej Borsz                                  *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include<cassert>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
#include<cstring>
#define FORE(it, c) for(__typeof((c).begin()) it = (c).begin(); it!=(c).end();++it)
#define FOR(i, a, b) for(int i = (a); i <= b; ++i)
#define FORD(i, a, b) for(int i = (a); i >= b; --i)
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define MP make_pair
#define PB push_back
#define FI first
#define SE second

using namespace std;
typedef pair<int, int> PLL;
const long long MAXN = 100100;
char in0[MAXN], in[MAXN];


PLL pt (int side, int x, int y) {
    if (side == 0) return MP(-x, y);
    if (side == 3) return MP(-y, -x);
    if (side == 2) return MP(x, -y);
    if (side == 1) return MP(y, x);
    assert(false);
}
void num(map<int, int> &m) {
    int n= 0;
    FORE(it, m) {
        it->SE = n;
        ++n;
    }
}
int main() {
    scanf("%s", in0);
    int n = strlen(in0), l = 0, swp = 0;
    REP(i, n) {
        if (in0[i] == 'L') ++l;
        if (in0[i] == 'L' && in0[i+1]=='L') swp = i;
    }
    if (n != 2*l-4) {
        printf("NIE\n");
        return 0;
    }
    REP(i, n) in[i] = in0[(i+swp)%n];
    vector<PLL> points;
    bool fwd = true;
    int side = n, small = 0, x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        if (fwd) {
            if (in[i] == 'L') {
                --side;
                x = -(side+1) * n - small;
                y = side*n + small;
                points.PB(pt(side % 4, x, y));
            } else {
                x = max(0, x+1);
                points.PB(pt(side % 4, x, y));
                ++y;
                ++small;
                if (i != n-1) {
                    points.PB(pt(side % 4, x, y));
                    fwd =  (in[i+1] == 'L');
                }
                ++i;
            }
        } else {
            if (in[i] == 'P') {
                ++side;
                x = (side-1)*n + small;
                y = side*n + small;
                points.PB(pt(side % 4, x, y));
            } else {
                x = min(0, x-1);
                points.PB(pt(side % 4, x, y));
                ++y;
                ++small;
                if (i != n-1) {
                    points.PB(pt(side % 4, x, y));
                    fwd =  (in[i+1] == 'L');
                }
                ++i;
            }
        }
    }
    points[0].SE = points[n-1].SE;
    map<int, int> xs, ys;
    FORE(it, points) {
        xs[it->FI] = ys[it->SE] = 0;
    }
    num(xs);
    num(ys);
    FORE(it, points) {
        printf("%d %d\n", xs[it->FI], ys[it->SE]);
    }
    return 0;
}
