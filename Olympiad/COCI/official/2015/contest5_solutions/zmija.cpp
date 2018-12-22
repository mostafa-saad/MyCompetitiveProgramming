#include <algorithm>
#include <cstdio>

using namespace std;

int R, S, vis;
int l[1005], r[1005];

char grid[1005][1005];

int main(void) {

    scanf("%d%d", &R, &S);
    for (int i = 0; i < R; ++i) 
        scanf("%s", grid[i]);

    for (int i = R - 1; i >= 0; --i) {
        l[R - 1 - i] = 10001, r[R - 1 - i] = -1;
        for (int j = 0; j < S; ++j) {
            if (grid[i][j] == 'J') {
                l[R - 1 - i] = min(l[R - 1 - i], j);
                r[R - 1 - i] = max(r[R - 1 - i], j);
                vis = R - 1 - i;
            }
        }
    }

    l[R] = 10001; r[R] = -1;
    int x = 0, sol = vis;
    for (int i = 1; i <= R; ++i) {
        if (i % 2) { 
            int _x = max(r[i - 1], r[i]); _x = max(_x, x);
            sol += _x - x;
            x = _x;
        } else {
            int _x = min(l[i - 1], l[i]); _x = min(_x, x);
            sol += x - _x;
            x = _x;
        }
    }

    printf("%d\n", sol);

    return 0;

}
