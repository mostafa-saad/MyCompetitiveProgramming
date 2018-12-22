#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 510;
const int MAXV = 510;

struct point {
  int x, y;
  point() {}
  point (int _x, int _y) { 
    x = _x, y = _y; 
  }
} pts[MAXV];

int R, C, V;
char mat[MAXN][MAXN];
int sum[MAXN][MAXN][26];

int area() {
  int ret = 0;

  point cur = pts[0];
  for (int i = V - 1; i >= 0; --i) {
    point nxt = pts[i];
    if (cur.y != nxt.y)
      ret += (nxt.y - cur.y) * cur.x;
    cur = nxt;
  }

  return ret;
}

int cnt(int row, int col, int letter) {
  int ret = 0;

  point cur = pts[0];
  for (int i = V - 1; i >= 0; --i) {
    point nxt = pts[i];
    if (cur.y != nxt.y) 
      ret += sum[nxt.x + row][nxt.y + col][letter] - sum[cur.x + row][cur.y + col][letter];
    cur = nxt;
  }

  return ret;
}

int main(void) {

  scanf("%d %d", &R, &C);
  for (int row = 0; row < R; ++row)
    scanf("%s", mat[row]);

  for (char letter = 0; letter < 26; ++letter) 
    for (int row = 1; row <= R; ++row)
      for (int col = 1; col <= C; ++col)
        sum[row][col][letter] = (mat[row - 1][col - 1] == 'a' + letter) +
          sum[row - 1][col][letter] + 
          sum[row][col - 1][letter] - 
          sum[row - 1][col - 1][letter];

  int min_row = R;
  int max_row = 0;
  int min_col = C;
  int max_col = 0;

  scanf("%d", &V);

  for (int i = 0; i < V; ++i) {
    scanf("%d %d", &pts[i].y, &pts[i].x);
    min_row = min(min_row, pts[i].x);
    max_row = max(max_row, pts[i].x);
    min_col = min(min_col, pts[i].y);
    max_col = max(max_col, pts[i].y);
  }

  max_row -= min_row;
  max_col -= min_col;

  for (int i = 0; i < V; ++i) {
    pts[i].x -= min_row;
    pts[i].y -= min_col;
  }

  int A = area();
  point p(min_row, C);
  for (int i = 0; i < V; ++i) 
    if (pts[i].x == min_row) p.y = min(p.y, pts[i].y);

  int ret = 0;

  for (int row = 0; row + max_row <= R; ++row)
    for (int col = 0; col + max_col <= C; ++col) {
      int letter = mat[p.x + row][p.y + col] - 'a';
      int n = cnt(row, col, letter);
      ret += n == A;
    }

  printf("%d\n", ret);
}
