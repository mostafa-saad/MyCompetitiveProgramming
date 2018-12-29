/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Karczmarz                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Drzewo przedzialowe po wspolrzednych.         *
 *                         W wezlach wektory.                            *
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
    vector<int> S;
    void insert(int k) {
        S.insert(upper_bound(ALL(S), k), k);
    }
    int count_le(int k) {
        return distance(S.begin(), upper_bound(ALL(S), k));
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
    y += BASE;
    while (y > 0) {
        used.PB(y);
        drz[y].insert(t);
        y /= 2;
    }
}

int count_earlier(int y, int t) {
    int p = y + BASE;
    int res = drz[p].count_le(t);
    while (p > 1) {
        if (p & 1) {
            res += drz[p - 1].count_le(t);
        }
        p >>= 1;
    }
    return res;
}

int find_time(int y, int K) {
    int l = 0, r = BASE - 1, res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (count_earlier(y, mid) >= K) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res;
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
