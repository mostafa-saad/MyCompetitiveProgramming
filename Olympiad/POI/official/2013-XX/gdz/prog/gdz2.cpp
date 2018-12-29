/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Karczmarz                                *
 *   Opis:                 Rozwiazanie wzorcowe                          *
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
int c[MAXN + 10], cost[MAXN + 10];

// cost[i] = suma liczb pierwszych w rozkladzie i
void comp_cost(int n) {
    for (int i = 2; i * i <= n; ) {
        for (int j = i; j <= n; j += i) {
            c[j] = i;
        }
        while (c[++i]);
    }
    cost[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (!c[i]) {
            cost[i] = i;
        } else {
            cost[i] = cost[i / c[i]] + c[i];
        }
    }
}

const LL INF = 100000000000000000LL;

// oblicz strategię
int strategy(int n) {
    pair<LL, int> best = MP(INF, INF);
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            continue;
        }
        LL can = (LL)n * cost[i] + sqr((LL)n * (n % i) / i);
        best = min(best, MP(can, i));
    }
    return best.second;
}

// wszystkie potegi liczb pierwszych w rozkladzie n
void split_pp(int n, VI &s) {
    map<int, int> cnt;
    while (n > 1) {
        if (c[n] == 0) {
            ++cnt[n];
            n = 1;
        } else {
            ++cnt[c[n]];
            n /= c[n];
        }
    }
    s.clear();
    FC (cnt, it) {
        int pp = 1;
        REP (i, it->second) {
            pp *= it->first;
            s.PB(pp);
        }
    }
}

int cla, ile[MAXN + 10], R[MAXN + 10], mxc;
VI P;

// znajdz klasy abstrakcji
void go(const VI &a, int phase) {
    if (phase == SZ(P)) {
        FC (a, it) {
            R[*it] = cla;
        }
        ile[cla] = SZ(a);
        mxc = max(ile[cla], mxc);
        ++cla;
        return;
    }
    vector<bool> vis(SZ(a));
    VI tmp; int d = P[phase];
    for (int i = 0; i < SZ(a); ++i) {
        if (vis[i]) {
            continue;
        }
        tmp.clear();
        for (int j = i; j < SZ(a); ++j) {
            if (!vis[j]) {
                if (f(a[i], a[j], d)) {
                    vis[j] = true;
                    tmp.PB(a[j]);
                }
            }
        }
        go(tmp, phase + 1);
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
    comp_cost(n);
    int s = strategy(n);
    split_pp(s, P);
    VI a;
    for (int i = 1; i <= n; ++i) {
        a.PB(i);
    }
    go(a, 0);
    VI cans;
    for (int i = 1; i <= n; ++i) {
        if (ile[R[i]] == mxc) {
            cans.PB(i);
        }
    }
    find_one(cans, n - 1);
    return 0;
}

