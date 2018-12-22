#include <algorithm>
#include <cstdio>
using namespace std;

const int NN = 100005;
pair<int, int> t[NN];

void divcon(int lo, int hi) {
  if (lo + 2 == hi) {
    printf("%d %d\n", t[lo].first, t[lo + 1].second); 
    return;
  }
  if (lo + 2 > hi) return;
  int mid = (lo + hi) / 2;
  int x = t[mid].first;
  for (int i = lo; i < hi; ++i)
    if (i != mid)
      printf("%d %d\n", x, t[i].second);
  divcon(lo, mid);
  divcon(mid + 1, hi);
}

int main () {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &t[i].first, &t[i].second);
  }
  sort(t, t + n);
  divcon(0, n);
}
