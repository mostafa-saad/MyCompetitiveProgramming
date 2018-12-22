#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// max_mod * max_mod * log(k)

const int max_mod = 1500;
char baza[max_mod];
char ans[2][max_mod], org = 0;

int mod;
long long k;

void load() {
  int n, t;
  scanf("%lld%d%d", &k, &mod, &n);
  for (int j = 0; j < n; ++j)
    scanf("%d", &t) && (baza[t] = 1);
}

void solve() {
  ans[org][1] = 1;
  for (unsigned long long mask = (1ll<<63); mask; mask >>=1) {
    memset(ans[!org], 0, mod);
    for (int i = 0; i < mod; ++i)
      for (int j = 0; j < mod; ++j)
        if (ans[org][i] && ans[org][j])
          ans[!org][ (i*j) % mod ] = 1;
    org = !org;
    if (mask & k) {
      memset(ans[!org], 0, mod);
      for (int i = 0; i < mod; ++i)
        for (int j = 0; j < mod; ++j)
          if (ans[org][i] && baza[j])
            ans[!org][ (i*j) % mod ] = 1;
      org = !org;
    }
  }
  for (int j = 0; j < mod; ++j) {
    if (ans[org][j])
      printf("%d ", j);
  }
  printf("\n");
}

int main() {
  load();
  solve();
  return 0;
}
