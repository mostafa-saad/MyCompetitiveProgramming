#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 110;

int n, a[MAXN][MAXN];

int main(void) {
  scanf("%d",&n);

  if (n == 2) {
    printf("-1\n");
    return 0;
  }

  for (int j = 0; j < n - 1; ++j) {
    a[0][j] = j + 1;
  }
  a[0][n - 1] = n * (n - 1) / 2;

  int jump = a[0][n - 1];
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      a[i][j] = a[i - 1][j] + jump;
  }

  for (int j = 0; j < n; ++j) {
    a[n - 1][j] = n * a[n - 2][j];
    for (int i = 0; i < n - 1; ++i)
      a[n - 1][j] -= a[i][j];
  }

  
  for (int i = 0; i < n; ++i, printf("\n"))
    for (int j = 0; j < n; ++j)
      printf("%d ",a[i][j]);
  
  return 0;
}
