#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1005;

int n;
int ans[MAXN];

int main (void){
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      int x;
      scanf("%d", &x);
      ans[i] |= x;
    }

  for (int i = 0; i < n; ++i)
    printf("%d ", ans[i]);
  return 0;
}

