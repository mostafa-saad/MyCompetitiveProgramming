#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

const int MAXN = 1091;

int R, S;
int n, len;

char grid[MAXN][MAXN];
char *ptr[MAXN];

struct char_cmpf {
  inline bool operator () (const char *A, const char *B) const {
    return strcmp(A, B) < 0;
  }
};

int main( void )
{
  scanf("%d %d", &R, &S);
  n = S; len = R;
  
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < S; ++j) {
      scanf(" %c", &grid[j][R-i-1] );
    }
  for (int i = 0; i < n; ++i) {
    grid[i][len] = 0;
    ptr[i] = grid[i];
  }

  int maks = 0;
  sort(ptr, ptr+n, char_cmpf());

  for (int i = 1; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < len && ptr[i-1][j] == ptr[i][j]; ++j)
      ++cnt;
    if (cnt > maks) maks = cnt;
  }

  printf("%d\n", len - maks - 1 ); 
  return (0-0);
}
