/**
 * A solution for task PORTALS.
 * Saves position of one portal.
 * Complexity - O((RC)^2).
 *
 * Author: Daumilas Ardickas
 */

#include <queue>
#include <cstdio>

using namespace std;

#define MAX_N 50

int R, C, i, j, c, cx, cy;
char lab[MAX_N][MAX_N+1]; //labyrinth

struct pos {
    int x, y, px, py;
    bool fired;
    pos(int x_, int y_, int px_, int py_, bool fired_) {
        x = x_; y = y_; px = px_, py = py_, fired = fired_;
    }
};

int t[MAX_N][MAX_N][MAX_N][MAX_N][2]; //y, x, py, px, fired
queue<pos> q;

void bfs(const pos& p) {
    if (t[p.y][p.x][p.py][p.px][p.fired] == -1) {
        pos& pp = q.front();
        t[p.y][p.x][p.py][p.px][p.fired] = t[pp.y][pp.x][pp.py][pp.px][pp.fired] + !p.fired;
        if (p.x == cx && p.y == cy) c = t[p.y][p.x][p.py][p.px][p.fired];
        q.push(p);
    }
}

int w[MAX_N][MAX_N][4]; //up, left, down, right

void fire(pos& p, int dir) {
    if (dir % 2) {
        p.py = p.y;
        p.px = w[p.y][p.x][dir];
    } else {
        p.px = p.x;
        p.py = w[p.y][p.x][dir];
    }
    bfs(p);
}

void go(pos p, int dx, int dy) {
    p.x += dx; p.y += dy;
    if (p.x < 0 || p.x >= C || p.y < 0 || p.y >= R || lab[p.y][p.x] == '#') {
        p.x = p.px;
        p.y = p.py;
    }
    bfs(p);
}

int main() {
    scanf("%d%d", &R, &C);
    for (j = 0; j < R; j++)
        for (i = 0; i < C; i++)
            for (int py = 0; py < R; py++)
                for (int px = 0; px < C; px++)
                    t[j][i][py][px][0] = t[j][i][py][px][1] = -1;
    for (j = 0; j < R; j++) {
        scanf(" %s", lab[j]);
        for (i = 0; i < C; i++) {
            switch (lab[j][i]) {
                case 'S': {
                    pos p = pos(i, j, i, j, false);
                    t[j][i][j][i][0] = 0;
                    q.push(p);
                    break;
                }
                case 'C': {cx = i; cy = j; break;}
            }
        }
    }
    
    for (j = 0; j < R; j++)
        for (i = 0; i < C; i++) {
            w[j][i][0] = (j == 0 || lab[j-1][i] == '#') ? j : w[j-1][i][0];
            w[j][i][1] = (i == 0 || lab[j][i-1] == '#') ? i : w[j][i-1][1];
        }
        
    for (j = R-1; j >= 0; j--)
        for (i = C-1; i >= 0; i--) {
            w[j][i][2] = (j == R-1 || lab[j+1][i] == '#') ? j : w[j+1][i][2];
            w[j][i][3] = (i == C-1 || lab[j][i+1] == '#') ? i : w[j][i+1][3];
        }
    
    c = -1;
    while (c == -1 && q.size()) {
        pos p = q.front();
        p.fired = !p.fired;
        if (p.fired) {
            bfs(p);
            fire(p, 0);
            fire(p, 1);
            fire(p, 2);
            fire(p, 3);
        } else {
            go(p, 0, 1);
            go(p, 0, -1);
            go(p, 1, 0);
            go(p, -1, 0);
        }
        q.pop();
    }
    printf ("%d\n", c);
}
