#include <cstdio>
using namespace std;

char a[501][501];
int qx[501 * 501];
int qy[501 * 501];
int bio[501][501];

const int u[] = {0, 0, 1, -1};
const int v[] = {1, -1, 0, 0};

inline int dist(int x, int y, int nx, int ny) {
    return (x - nx) * (x - nx) + (y - ny) * (y - ny);
}

int main () {
    int r, s;
    scanf("%d%d", &r, &s);
    for (int i = 0; i < r; ++i)
        scanf("%s", a[i]);
    int g;
    scanf("%d", &g);
    for (int t = 1; t <= g; ++t) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x;
        --y;
        if (a[x][y] == 'x') {
            printf("0\n");
            continue;
        }
        int best = 2 * 1000 * 1000;
        qx[0] = x;
        qy[0] = y;
        bio[x][y] = t;
        int lo = 0, hi = 1;
        while (lo < hi) {
            int nx = qx[lo];
            int ny = qy[lo++];
            if (dist(x, y, nx, ny) >= best)
                continue;
            for (int i = 0; i < 4; ++i) {
                int sx = nx + u[i];
                if (sx < 0 || sx >= r) continue;
                int sy = ny + v[i];
                if (sy < 0 || sy >= s || bio[sx][sy] == t)
                    continue;
                bio[sx][sy] = t;
                int d = dist(x, y, sx, sy);
                if (d >= best) continue;
                if (a[sx][sy] == 'x')
                    best = d;
                qx[hi] = sx;
                qy[hi++] = sy;
            }
        }
        printf("%d\n", best);
        a[x][y] = 'x';
    }
}
