#include <cstdio>

using namespace std;

const int MAXN = 5001;
const int M    = 200000;

int n, a[MAXN], e[2*M+1];

inline int q(int b) { return e[b+M]; } // query
inline void u(int b) { e[b+M] = 1; } // update

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", a+i);

  int sol = 0;
  for (int i = 0, ok = 0; i < n; ++i, ok = 0) {
    for (int j = 0; j <  i && !ok; ++j) ok = q(a[i]-a[j]);
    for (int j = 0; j <= i; ++j) u(a[i]+a[j]);
    sol += ok;
  }

  printf("%d\n", sol);
  return 0;
}
