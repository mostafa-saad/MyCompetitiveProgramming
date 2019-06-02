/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Adam Karczmarz                                *
 *   Zlozonosc czasowa:    O(n * m^(2/3))                                *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;

bool has(int a, int b, int d) {
    return a % d == 0 || b % d == 0 || b - a + 1 >= d || a % d > b % d;
}

int small(int a, int b, int x, int y, int Z) {
    for (int d = min(Z, min(b, y)); ; --d) {
        if (has(a, b, d) && has(x, y, d)) {
            return d;
        }
    }
    return 1;
}

int inter(int A, int B, int X, int Y) {
    if (max(A, X) <= min(B, Y)) {
        return min(B, Y);
    }
    return -1;
}

int big(int a, int b, int x, int y, int Z) {
    int res = 1;
    for (int d1 = 1; d1 <= min(Z, y); ++d1) {
        int x1 = (x + d1 - 1) / d1, y1 = y / d1;
        for (int d2 = 1; d2 <= min(Z, b); ++d2) {
            res = max(res, inter((a + d2 - 1) / d2, b / d2, x1, y1));
        }
    }
    return res;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        int Z = (int)pow(max(b, y), 1.0 / 3.0) + 2;
        int res = small(a, b, x, y, Z * Z);
        res = max(res, big(a, b, x, y, Z));
        printf("%d\n", res);
    }
    return 0;
}
