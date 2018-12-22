#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<pair<int, int>> Shape;

const int MAXN = 505;

int n, m;
char a[MAXN][MAXN];
int ans[5];

int main(void) {
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; ++i) {
    scanf("%s", a[i]);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i][j] == '.') {
        continue;
      }

      // kvadrat       
      if (i+1 < n && j+1 < m &&
          a[i+1][j] == a[i][j] &&
          a[i][j+1] == a[i][j] &&
          a[i+1][j+1] == a[i][j]) {
        ++ans[0];
      }

      // slovo I 
      if (j+3 < m &&
          a[i][j+1] == a[i][j] &&
          a[i][j+2] == a[i][j] &&
          a[i][j+3] == a[i][j]) {
        ++ans[1];
      }

      if (i+3 < n &&
          a[i+1][j] == a[i][j] &&
          a[i+2][j] == a[i][j] &&
          a[i+3][j] == a[i][j]) {
        ++ans[1];
      }

      // slovo S
      if (i+1 < n && j > 0 && j+1 < m &&
          a[i+1][j-1] == a[i][j] &&
          a[i+1][j] == a[i][j] &&
          a[i][j+1] == a[i][j]) {
        ++ans[2];
      }

      if (i+2 < n && j+1 < m &&
          a[i+1][j] == a[i][j] &&
          a[i+1][j+1] == a[i][j] &&
          a[i+2][j+1] == a[i][j]) {
        ++ans[2];
      }

      // slovo Z
      if (i+1 < n && j+2 < m &&
          a[i][j+1] == a[i][j] &&
          a[i+1][j+1] == a[i][j] &&
          a[i+1][j+2] == a[i][j]) {
        ++ans[3];
      }

      if (i+2 < n && j > 0 &&
          a[i+1][j-1] == a[i][j] &&
          a[i+1][j] == a[i][j] &&
          a[i+2][j-1] == a[i][j]) {
        ++ans[3];
      }

      // slovo T
      if (i+2 < n && j+1 < m &&
          a[i+1][j] == a[i][j] &&
          a[i+1][j+1] == a[i][j] &&
          a[i+2][j] == a[i][j]) {
        ++ans[4];
      }

      if (i+1 < n && j > 0 && j+1 < m &&
          a[i+1][j-1] == a[i][j] &&
          a[i+1][j] == a[i][j] &&
          a[i+1][j+1] == a[i][j]) {
        ++ans[4];
      }

      if (i+2 < n && j > 0 &&
          a[i+1][j-1] == a[i][j] &&
          a[i+1][j] == a[i][j] &&
          a[i+2][j] == a[i][j]) {
        ++ans[4];
      }

      if (i+1 < n && j+2 < m &&
          a[i][j+1] == a[i][j] &&
          a[i][j+2] == a[i][j] &&
          a[i+1][j+1] == a[i][j]) {
        ++ans[4];
      }
    } 
  }

  for (int i = 0; i < 5; ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
