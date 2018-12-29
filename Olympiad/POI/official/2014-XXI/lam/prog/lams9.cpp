/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Karczmarz                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         std::set                                      *
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

struct str {
    multiset<int> S;
    void insert(int k) {
        S.insert(k);
    }
    int count_le(int k) {
        return distance(S.begin(), S.upper_bound(k));
    }
};

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
int BASE;
str drz[1 << 19];
VI used;

void add(int t, int y) {
    t += BASE;
    while (t > 0) {
        used.PB(t);
        drz[t].insert(y);
        t /= 2;
    }
}

int find_time(int y, int K) {
    if (drz[1].count_le(y) < K) {
        return -1;
    }
    int p = 1;
    while (p < BASE) {
        int z = drz[2 * p].count_le(y);
        if (z >= K) {
            p = 2 * p;
        } else {
            K -= z;
            p = 2 * p + 1;
        }
    }
    return p - BASE;
}

point P[MAXN + 10];
int res[MAXN + 10];

void comp(point *p, int n) {
    FC (used, it) {
        drz[*it] = str();
    }
    used.clear();
    REP (i, n) {
        int z = find_time(p[i].y, p[i].k);
        if (z == -1 || z > p[i].id) {
            z = p[i].id;
        }
        res[p[i].id] = z;
        add(z, p[i].y);
    }
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
    for (BASE = 1; BASE < n; BASE <<= 1);
    sort(P, P + n);
    if (!zero) {
        comp(P, n);
    } else {
        for (int i = 0; i < n; ) {
            int j;
            for (j = i; j < n && P[j].x == P[i].x; ++j);
            comp(P + i, j - i);
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
