/**
 * A solution for task PORTALS.
 * Saves position of both portals.
 * Complexity - O((RC)^3).
 *
 * Author: Daumilas Ardickas
 */

#include <queue>
#include <cstdio>

using namespace std;

#define MAX_N 15

int R, C, i, j, c, cx, cy;
char lab[MAX_N][MAX_N]; //labyrinth

struct pos {
    int x, y, px[2], py[2], fired; //blue and orange portals
};

int t[MAX_N][MAX_N][MAX_N+1][MAX_N][MAX_N+1][MAX_N][3]; //y, x, py[0], px[0], py[1], px[1], fired
queue<pos> q;

void bfs(pos& p) {
    int* tt = &t[p.y][p.x][p.py[0]][p.px[0]][p.py[1]][p.px[1]][p.fired];
    if (*tt == -1) {
        pos& pp = q.front();
        *tt = t[pp.y][pp.x][pp.py[0]][pp.px[0]][pp.py[1]][pp.px[1]][pp.fired] + (p.fired == 0);
        
        if (p.x == cx && p.y == cy) c = *tt;
        q.push(p);
    }
}

int w[MAX_N][MAX_N][4]; //up, left, down, right

void fire(pos& p, int dir) {
    if (dir % 2) {
        p.py[p.fired - 1] = p.y;
        p.px[p.fired - 1] = w[p.y][p.x][dir];
    } else {
        p.px[p.fired - 1] = p.x;
        p.py[p.fired - 1] = w[p.y][p.x][dir];        
    }
    bfs(p);
}

void go(pos p, int dx, int dy) {
    p.x += dx; p.y += dy;
    if (p.x < 0 || p.x >= C || p.y < 0 || p.y >= R || lab[p.y][p.x] == '#') return;
    bfs(p);
}

void teleport(pos p, int portal) {
    if (p.x != p.px[portal] || p.y != p.py[portal]) return;
    p.x = p.px[1 - portal]; p.y = p.py[1 - portal];
    bfs(p);
}

int main() {
    scanf("%d%d", &R, &C);
    for (j = 0; j < R; j++)
        for (i = 0; i < C; i++)
            for (int by = 0; by <= R; by++)
                for (int bx = 0; bx < C; bx++)
                    for (int oy = 0; oy <= R; oy++)
                        for (int ox = 0; ox < C; ox++)
                            t[j][i][by][bx][oy][ox][0] = t[j][i][by][bx][oy][ox][1] = t[j][i][by][bx][oy][ox][2] = -1;
    for (j = 0; j < R; j++) {
        scanf(" %s", lab[j]);
        for (i = 0; i < C; i++) {
            switch (lab[j][i]) {
                case 'S': {
                    pos p; 
                    p.x = p.px[0] = p.px[1] = i;
                    p.y = j; 
                    p.py[0] = p.py[1] = R;
                    p.fired = false;
                    t[j][i][R][i][R][i][0] = 0;
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
        p.fired = (p.fired + 1) % 3;
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
            teleport(p, 0);
            teleport(p, 1);
        }
        q.pop();
    }
    printf ("%d\n", c);
}
