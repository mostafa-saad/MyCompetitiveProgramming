/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Karczmarz                                *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <map>
#include "cgdzlib.h"

#define REP(AA,BB) for(int AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(int AA=(BB); AA<(CC); ++AA)
#define FC(AA,BB) for(__typeof((AA).begin()) BB=(AA).begin(); BB!=(AA).end(); ++BB)
#define SZ(AA) ((int)((AA).size()))
#define ALL(AA) (AA).begin(), (AA).end()
#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

inline LL sqr(LL a) {
    return a * a;
}

const int MAXN = 500000;

const LL INF = 100000000000000000LL;

pair<LL, int> strategy(int n) {
    pair<LL, int> best = MP(INF, INF);
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            continue;
        }
        if ((LL)n * i > best.first) {
            break;
        }
        LL can = (LL)n * i + sqr((LL)n * (n % i) / i);
        best = min(best, MP(can, i));
    }
    return best;
}

int cla, ile[MAXN + 10], R[MAXN + 10], mxc;

void go(int n, int d) {
    int lim = n / d + 1;
    for (int i = 1; i <= n; ++i) {
        if (R[i] != -1) {
            continue;
        }
        int cnt = 0;
        for (int j = i; j <= n && cnt <= lim; ++j) {
            if (R[j] == -1) {
                if (f(i, j, d)) {
                    R[j] = cla;
                    ++cnt;
                }
            }
        }
        ile[cla] = cnt;
        mxc = max(mxc, cnt);
        ++cla;
    }
}

void find_one(const VI &a, int d) {
    int m = SZ(a);
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            if (f(a[i], a[j], d)) {
                if (g(a[i], a[j])) {
                    odpowiedz(a[j]);
                } else {
                    odpowiedz(a[i]);
                }
                return;
            }
        }
    }
    assert(0);
}

int main(void) {
    int n = inicjuj();
    if (n == 1) {
        odpowiedz(1);
        return 0;
    }
    if (n == 2) {
        if (g(1, 2)) {
            odpowiedz(2);
        } else {
            odpowiedz(1);
        }
        return 0;
    }
    int s = strategy(n).second;
    memset(R, -1, sizeof R);
    go(n, s);
    VI cans;
    for (int i = 1; i <= n; ++i) {
        if (ile[R[i]] == mxc) {
            cans.PB(i);
        }
    }
    find_one(cans, n - 1);
    return 0;
}

