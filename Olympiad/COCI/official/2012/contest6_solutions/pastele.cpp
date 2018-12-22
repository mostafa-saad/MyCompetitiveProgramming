#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int n, k;
const int c = 256;
int a[c][c][c];
int s[c][c][c];
 
inline int f(int x, int y, int z) {
  return x < 0 || y < 0 || z < 0 ? 0 : s[x][y][z];
}
int f(int x1, int y1, int z1, int m) {
  int x2 = x1 + m;
  int y2 = y1 + m;
  int z2 = z1 + m;
  --x1; --y1; --z1;
  return
    + f(x2, y2, z2)
    - f(x1, y2, z2)
    - f(x2, y1, z2)
    - f(x2, y2, z1)
    + f(x1, y1, z2)
    + f(x1, y2, z1)
    + f(x2, y1, z1)
    - f(x1, y1, z1);
}
 
int main(void) {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    ++a[x][y][z];
  }
  for (int x = 0; x < c; ++x)
    for (int y = 0; y < c; ++y)
      for (int z = 0; z < c; ++z)
        s[x][y][z] = 
          + a[x][y][z]
          + f(x - 1, y, z)
          + f(x, y - 1, z)
          + f(x, y, z - 1)
          - f(x - 1, y - 1, z)
          - f(x - 1, y, z - 1)
          - f(x, y - 1, z - 1)
          + f(x - 1, y - 1, z - 1); 
          
  int rx, ry, rz, rm = c;  
  for (int x = 0; x < c; ++x)
    for (int y = 0; y < c; ++y)
      for (int z = 0; z < c; ++z) {
        int l = 0;
        int h = min(c - x, min(c - y, c - z)) - 1;
        while (l < h) {
          int m = l + (h - l) / 2;
          if (f(x, y, z, m) < k)
            l = m + 1;
          else
            h = m;
        }
        if (f(x, y, z, l) >= k && l < rm) {
          rx = x;
          ry = y;
          rz = z;
          rm = l;
        }
      }
  printf("%d\n", rm);
  for (int x = rx; x <= rx + rm; ++x)
    for (int y = ry; y <= ry + rm; ++y)
      for (int z = rz; z <= rz + rm; ++z)
        while (k > 0 && a[x][y][z]--) {
          printf("%d %d %d\n", x, y, z);
          --k;
        }
  return 0;
}
