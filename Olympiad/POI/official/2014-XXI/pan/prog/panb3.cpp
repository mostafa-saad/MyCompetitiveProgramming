/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Adam Karczmarz                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;

int Z;

bool has(int a, int b, int d) {
    return a % d == 0 || b % d == 0 || b - a + 1 >= d || a % d > b % d;
}

int small(int a, int b, int x, int y) {
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

int check(int a, int b, int X, int Y) {
    int d = max(b / (Y + 1), 1);
    int res = 1;
    for (int i = 0; i <= 2 && d + i <= b; ++i) {
        int d1 = d + i;
        res = max(res, inter((a + d1 - 1) / d1, b / d1, X, Y));
    }
    //printf("check %d %d %d %d (%d) -> %d\n", a, b, X, Y, d, res);
    return res;
}

int big(int a, int b, int x, int y) {
    int res = 1;
    for (int d = 1; d <= min(Z, y); ++d) {
        res = max(res, check(a, b, (x + d - 1) / d, y / d));
    }
    return res;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int a, b, x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        Z = (int)sqrt(max(b, y)) + 5;
        int res = small(a, b, x, y);
        res = max(res, big(a, b, x, y));
        //res = max(res, big(x, y, a, b));
        printf("%d\n", res);
    }
    return 0;
}
