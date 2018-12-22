#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long llint;
typedef pair <int, int> pii;

int n, d;

int main (void){
  scanf("%d%d", &n, &d);
  int last = 0;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int x; scanf("%d", &x);
    if (x == 1) last = i;
    if (i - last == d) {
      ++ans;
      last = i;
    }
  }
  printf("%d\n", ans);
  return 0;
}
