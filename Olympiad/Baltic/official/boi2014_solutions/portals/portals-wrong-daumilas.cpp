/**
 * An invalid solution for task PORTALS.
 * Assumes that it is worth to shoot portals only if you are near a wall
 *
 * Author: Daumilas Ardickas
 */

#include <queue>
#include <cstdio>

using namespace std;

#define MAX_N 1000

int R, C, i, j;
char lab[MAX_N][MAX_N]; //labyrinth
int wx[MAX_N][MAX_N][2], wy[MAX_N][MAX_N][2]; //wall coordinates
int t[MAX_N][MAX_N]; //time
int cx, cy;
queue< pair<int, int> > q;

void bfs(int x, int y) {
    if (x >= 0 && y >= 0 && x < C && y < R && t[y][x] == -1 && lab[y][x] != '#') {
        t[y][x] = t[j][i] + 1;
        q.push(make_pair(x, y));
    }
}

int main() {
    scanf("%d%d", &R, &C);
    for (j = 0; j < R; j++) {
        scanf(" %s", lab[j]);
        for (i = 0; i < C; i++) {
            t[j][i] = -1;
            switch (lab[j][i]) {
                case 'S': {t[j][i] = 0; q.push(make_pair(i, j)); break;}
                case 'C': {cx = i; cy = j; break;}
            }
        }
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
    
    while (q.size() && t[cy][cx] == -1) {
        i = q.front().first;
        j = q.front().second;
        q.pop();
        bfs(i, j-1);
        bfs(i, j+1);
        bfs(i-1, j);
        bfs(i+1, j);
        if (wx[j][i][0] == i || wx[j][i][1] == i || wy[j][i][0] == j || wy[j][i][1] == j)
        {
            bfs(wx[j][i][0], j);
            bfs(wx[j][i][1], j);
            bfs(i, wy[j][i][0]);
            bfs(i, wy[j][i][1]);
        }
    }
    
    printf ("%d\n", t[cy][cx]);
}
