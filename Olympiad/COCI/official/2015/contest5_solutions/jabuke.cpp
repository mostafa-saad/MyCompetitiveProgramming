#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXR = 501;
const int MAXS = 501;
const int INF = 2e+9;

int R, S, G;
char s[MAXR][MAXS];
int u[MAXR][MAXS];
int d[MAXR][MAXS];

inline int dist(int x1, int y1, int x2, int y2) {
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void update_col(int col) {
  int last = -1;
  for(int row = 0; row < R; ++row) {
    if(s[row][col] == 'x') last = row;
    u[row][col] = last;
  }
  last = -1;
  for(int row = R-1; row >= 0; --row) {
    if(s[row][col] == 'x') last = row;
    d[row][col] = last;
  }
}

int query(int r, int c) {
  int ret = INF;
  for(int t = 0; t < S; ++t) {
    if(u[r][t] != -1) ret = min(ret, dist(r, c, u[r][t], t));
    if(d[r][t] != -1) ret = min(ret, dist(r, c, d[r][t], t));
  }
  return ret;
}

int main(void) {

  scanf("%d%d", &R, &S);
  for(int i = 0; i < R; ++i)
    scanf("%s", s[i]);

  for(int col = 0; col < S; ++col)
    update_col(col);

  scanf("%d", &G);
  for(int i = 0; i < G; ++i) {
    int r, c; scanf("%d%d", &r, &c);
    --r; --c;
    printf("%d\n", query(r, c));
    s[r][c] = 'x';
    update_col(c);
  }

  return 0;

}
