/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Karczmarz                                *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <set>
#include <map>
#include <cassert>

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

struct point {
    int x, y, k, id;
    bool operator<(const point &p) const {
        if (x == p.x) {
            return y < p.y;
        }
        return x < p.x;
    }
};

const int MAXN = 200000;
point P[MAXN + 10], tmp[MAXN + 10];
int cnt[MAXN + 10], MX, res[MAXN + 10];

VI used;

void clear() {
    FC (used, it) {
        cnt[*it] = 0;
    }
    used.clear();
}

void add(int a, int v) {
    while (a <= MX) {
        used.PB(a);
        cnt[a] += v;
        a += (a & (-a));
    }
}

int get(int a) {
    int r = 0;
    while (a > 0) {
        r += cnt[a];
        a -= (a & (-a));
    }
    return r;
}

void comp(point *p, point *t, int n, int l, int r) {
    if (l == r) {
        REP (i, n) {
            res[p[i].id] = l;
        }
        return;
    }
    int mid = (l + r) / 2;
    int A = 0, B = n - 1;
    REP (i, n) {
        int z = get(p[i].y);
        if (p[i].id <= mid || z >= p[i].k) {
            t[A++] = p[i];
            add(p[i].y, 1);
        } else {
            p[i].k -= z;
            t[B--] = p[i];
        }
    }
    reverse(t + A, t + n);
    REP (i, n) {
        p[i] = t[i];
    }
    clear();
    comp(p, t, A, l, mid);
    comp(p + A, t + A, n - A, mid + 1, r);
}

int main(void) {
    bool zero = false;
    int n, X1, Y1, X2, Y2;
    scanf("%d%d%d%d%d", &n, &X1, &Y1, &X2, &Y2);
    if ((LL)X1 * Y2 - (LL)X2 * Y1 < 0) {
        swap(X1, X2);
        swap(Y1, Y2);
    } else if ((LL)X1 * Y2 == (LL)X2 * Y1) {
        X2 = X1;
        Y2 = Y1;
        zero = true;
    }
    REP (i, n) {
        scanf("%d%d", &P[i].x, &P[i].y);
        P[i].id = i;
    }
    REP (i, n) {
        scanf("%d", &P[i].k);
    }
    vector<LL> sX, sY;
    REP (i, n) {
        LL tx = (LL)P[i].x * Y2 - (LL)X2 * P[i].y;
        LL ty = zero ? (LL)X1 * P[i].x + (LL)Y2 * P[i].y : (LL)X1 * P[i].y - (LL)P[i].x * Y1;
        sX.PB(tx);
        sY.PB(ty);
    }
    sort(ALL(sX));
    sX.erase(unique(ALL(sX)), sX.end());
    sort(ALL(sY));
    sY.erase(unique(ALL(sY)), sY.end());
    REP (i, n) {
        LL tx = (LL)P[i].x * Y2 - (LL)X2 * P[i].y;
        LL ty = zero ? (LL)X1 * P[i].x + (LL)Y2 * P[i].y : (LL)X1 * P[i].y - (LL)P[i].x * Y1;
        P[i].x = lower_bound(ALL(sX), tx) - sX.begin();
        P[i].y = lower_bound(ALL(sY), ty) - sY.begin();
        ++P[i].x;
        ++P[i].y;
    }
    MX = SZ(sY) + 1;
    sort(P, P + n);
    if (!zero) {
        comp(P, tmp, n, 0, n - 1);
    } else {
        for (int i = 0; i < n; ) {
            int j;
            for (j = i; j < n && P[j].x == P[i].x; ++j);
            comp(P + i, tmp + i, j - i, 0, n - 1);
            i = j;
        }
    }
    REP (i, n) {
        if (i > 0) {
            putchar(' ');
        }
        printf("%d", res[i] + 1);
    }
    puts("");
    return 0;
}

