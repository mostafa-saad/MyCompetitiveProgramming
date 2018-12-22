#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

const int NN = 1000000;
const double GG = 1000000;

int a[NN], b[NN];

int main () {
  int n;
  scanf("%d", &n);
  int sa = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", a + i, b + i);
    sa += b[i];
  }
  double dg = 0, gg = GG;
  for (int i = 1; i < n; ++i) {
    int rb = b[i - 1] - b[i];
    int ra = a[i] - a[i - 1];
    if (rb == 0 && ra > 0) {
      printf("-1\n");
      return 0;
    }
    if (rb > 0) dg = max(dg, (double)ra / (double)rb);
    if (rb < 0) gg = min(gg, (double)ra / (double)rb);
  }
  if ((dg < gg + 1e-9))
    printf("%.12lf\n", sa * (dg + gg) / 2);
  else
    printf("-1\n");
}
