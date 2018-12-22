#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 510;
const int MAXV = 510;

typedef unsigned int uint;

uint pow2[32];
void precompute() {
  for (int i = 0; i < 32; ++i) {
    pow2[i] = 1 << i;
  }
}

struct Code {
  uint mask[16];
  Code() { 
    memset(mask, 0, sizeof mask); 
  }
  
  inline void set(int idx) {
    int pos = idx / 32;
    int bit = idx - pos * 32;
    mask[pos] |= pow2[bit];
  }

  inline int get(int idx) {
    int pos = idx / 32;
    int bit = idx - pos * 32;
    return (mask[pos] & pow2[bit]) > 0;
  }

  inline void shift_right() {
    int c = 0, nc = 0;
    for (int i = 0; i < 16; ++i) {
      nc = (mask[i] & pow2[31]) > 0;
      mask[i] <<= 1;
      mask[i] |= c;
      c = nc;
    }
  }

  inline Code operator & (Code &right) {
    Code tmp;
    for (int i = 0; i < 16; ++i)
      tmp.mask[i] = mask[i] & right.mask[i];
    return tmp;
  }

  inline bool operator == (Code &right) {
    for (int i = 0; i < 16; ++i)
      if (mask[i] != right.mask[i]) return 0;
    return 1;
  }

};

int R, C;
char mat[MAXN][MAXN];

Code encoded_row[MAXN][26];
Code valid_rows[MAXN][MAXN];

struct Polygon {
  int V;
  int x[MAXV];
  int y[MAXV];

  Polygon() {
    memset(mat, 0, sizeof mat);
    memset(edge, 0, sizeof edge);
    memset(first_col, -1, sizeof first_col);
  }

  int edge[MAXN][MAXN];

  void init_edge() {
    x[V] = x[0];
    y[V] = y[0];
    for (int i = 0; i < V; ++i) {
      if (y[i] == y[i + 1]) continue;
      int dy = 1, dj = 0;
      if (y[i + 1] < y[i])
        dy = dj = -1;
      for (int j = y[i]; j != y[i + 1]; j += dy)
        edge[x[i]][j + dj] = 1;
    }
  }

  int mat[MAXN][MAXN];

  void init_mat() {
    int sweep[MAXN];
    memset(sweep, 0, sizeof sweep);
    for (int col = 0; col < C; ++col) {
      for (int row = 0; row < R; ++row)
        sweep[row] ^= edge[col][row];
      for (int row = 0; row < R; ++row)
        mat[col][row] = sweep[row];
    }
  }

  int rows;
  int cols;
  int first_col[MAXN];
  Code encoded_row[MAXN];

  void encode_mat() {
    int min_row = R;
    int min_col = C;
    int max_row = 0;
    int max_col = 0;
    for (int col = 0; col < C; ++col)
      for (int row = 0; row < R; ++row)
        if (mat[col][row]) {
          min_row = min(min_row, row);
          min_col = min(min_col, col);
          max_row = max(max_row, row);
          max_col = max(max_col, col);
        }
    rows = max_row - min_row + 1;
    cols = max_col - min_col + 1;
    for (int col = 0; col < C; ++col)
      for (int row = 0; row < R; ++row)
        if (mat[col][row]) {
          encoded_row[row - min_row].set(col - min_col);
          if (first_col[row - min_row] == -1) first_col[row - min_row] = col - min_col;
        }
  }

} polygon;

int n;
int prow[MAXN * MAXN];
int pcol[MAXN * MAXN];

int main(void) {

  precompute();

  scanf("%d %d", &R, &C);
  for (int row = 0; row < R; ++row)
    for (int col = 0; col < C; ++col)
      scanf(" %c", &mat[col][row]);

  scanf("%d", &polygon.V);
  for (int i = 0; i < polygon.V; ++i)
    scanf("%d %d", &polygon.x[i], &polygon.y[i]);

  polygon.init_edge();
  polygon.init_mat();
  polygon.encode_mat();

  for (char c = 'a'; c <= 'z'; ++c)
    for (int row = 0; row < R; ++row)
      for (int col = 0; col < C; ++col)
        if (mat[col][row] == c)
          encoded_row[row][c - 'a'].set(col);

  for (int row = 0; row < R; ++row) {

    int lb = 0, ub = polygon.rows;
    lb = max(lb, polygon.rows - (R - row));
    ub = min(ub, row + 1);

    for (int p_row = lb; p_row < ub; ++p_row) {

      Code code = polygon.encoded_row[p_row];
      int first_col = polygon.first_col[p_row];
      
      for (int col = 0; col + polygon.cols <= C; ++col) {

        char c = mat[first_col][row];
        if ((encoded_row[row][c - 'a'] & code) == code)
            valid_rows[col][row].set(p_row);

        code.shift_right();
        ++first_col;
      }
    }
  }

  for (int col = 0; col < C; ++col)
    for (int row = 0; row < R; ++row) {
      if ((row != 0 || polygon.rows == 1) && valid_rows[col][row].get(polygon.rows - 1)) {
        pcol[n] = col;
        prow[n++] = row;
      }
      if (row + 1 < R) {
        valid_rows[col][row].shift_right();
        valid_rows[col][row].set(0);
        valid_rows[col][row + 1] = valid_rows[col][row] & valid_rows[col][row + 1];
      }
    }

  int ret = n;

  for (int i = 0; i < n; ++i) {
    int col = pcol[i];
    int row = prow[i];

    int f_col = polygon.first_col[polygon.rows - 1] + col;
    char c = mat[f_col][row];

    for (int j = 1, p_col; j < polygon.rows; ++j) {
      char ch = mat[polygon.first_col[polygon.rows - 1 - j] + col][row - j];
      if (ch != c) {
        ret--;
        break;
      }
    }
  }

  printf("%d\n", ret);
  return 0;
}
