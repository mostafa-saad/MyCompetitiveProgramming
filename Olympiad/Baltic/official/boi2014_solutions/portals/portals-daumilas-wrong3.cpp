/**
 * A solution for task PORTALS.
 * Bug in bfs
 *
 * Author: Daumilas Ardickas
 */

#include <queue>
#include <cstdio>

using namespace std;

#define MAX_N 1000

int R, C, i, j;
char lab[MAX_N][MAX_N]; //labyrinth
int dw[MAX_N][MAX_N]; //distances to walls
int wx[MAX_N][MAX_N][2], wy[MAX_N][MAX_N][2]; //wall coordinates
int t[MAX_N][MAX_N]; //time
int cx, cy;
queue< pair<int, int> > q;
priority_queue< pair<int, pair<int, int> > > q2;

void bfs(int x, int y) {
    if (x >= 0 && y >= 0 && x < C && y < R && dw[y][x] == -1) {
        dw[y][x] = dw[j][i] + 1;
        q.push(make_pair(x, y));
    }
}

void dijkstra(int x, int y, int d) {
    if (x >= 0 && y >= 0 && x < C && y < R && (t[y][x] == -1 || t[y][x] > t[j][i] + d) && lab[y][x] != '#') {
        t[y][x] = t[j][i] + d;
        q2.push(make_pair(-t[y][x], make_pair(x, y)));
    }
}

int main() {
    scanf("%d%d", &R, &C);
    for (j = 0; j < R; j++) {
        scanf(" %s", lab[j]);
        for (i = 0; i < C; i++) {
            dw[j][i] = -1;
            t[j][i] = -1;
            switch (lab[j][i]) {
                case 'S': {t[j][i] = 0; q2.push(make_pair(0, make_pair(i, j))); break;}
                case 'C': {cx = i; cy = j; break;}
                case '#': {dw[j][i] = 0; q.push(make_pair(i, j)); break;}
            }
        }
        q.push(make_pair(-1, j));
        q.push(make_pair(C, j));
    }
    for (i = 0; i < C; i++) {
        q.push(make_pair(i, -1));
        q.push(make_pair(i, R));
    }
    
    while (q.size()) {
        i = q.front().first;
        j = q.front().second;
        q.pop();
        bfs(i, j-1);
        bfs(i, j+1);
        bfs(i-1, j);
        bfs(i+1, j);
    }
    
    for (j = 0; j < R; j++)
        for (i = 0; i < C; i++) {
            wy[j][i][0] = (j == 0 || lab[j-1][i] == '#') ? j : wy[j-1][i][0];
            wx[j][i][0] = (i == 0 || lab[j][i-1] == '#') ? i : wx[j][i-1][0];
        }
        
    for (j = R-1; j >= 0; j--)
        for (i = C-1; i >= 0; i--) {
            wy[j][i][1] = (j == R-1 || lab[j+1][i] == '#') ? j : wy[j+1][i][1];
            wx[j][i][1] = (i == C-1 || lab[j][i+1] == '#') ? i : wx[j][i+1][1];
        }
    
    while (q2.size() && t[cy][cx] == -1) {
        i = q2.top().second.first;
        j = q2.top().second.second;
        q2.pop();
        if (!lab[j][i]) continue;
        dijkstra(i, j-1, 1);
        dijkstra(i, j+1, 1);
        dijkstra(i-1, j, 1);
        dijkstra(i+1, j, 1);
        dijkstra(wx[j][i][0], j, dw[j][i]);
        dijkstra(wx[j][i][1], j, dw[j][i]);
        dijkstra(i, wy[j][i][0], dw[j][i]);
        dijkstra(i, wy[j][i][1], dw[j][i]);
        lab[j][i] = 0;
    }
    
    printf ("%d\n", t[cy][cx]);
}
