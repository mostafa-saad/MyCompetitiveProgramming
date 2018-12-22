#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

int n, k, q;
long long sol;
map <int, int> rcnt, ccnt;
map <int, int> rxor, cxor;
map <pair<int, int>, int> rook;

void moveRook(int r, int c, int val) {
  sol -= n - ccnt[rxor[r]];
  sol -= n - rcnt[cxor[c]];
  if (rxor[r] != cxor[c])
    sol += 1;

  --rcnt[rxor[r]];
  rxor[r] ^= val;
  ++rcnt[rxor[r]];

  --ccnt[cxor[c]];
  cxor[c] ^= val;
  ++ccnt[cxor[c]];

  sol += n - ccnt[rxor[r]];
  sol += n - rcnt[cxor[c]];
  if (rxor[r] != cxor[c])
    sol -= 1;

  rook[make_pair(r, c)] ^= val;
}

void init(void) {
  scanf("%d %d %d",&n,&k,&q);
  rcnt[0] = ccnt[0] = n;
  for (int i = 0; i < k; ++i) {
    int r, c, val;
    scanf("%d %d %d",&r,&c,&val);
    --r;
    --c;
    moveRook(r, c, val);
  }
}

void solve(void) {
  while (q-- > 0) {
    int r1, c1, r2, c2;
    scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
    --r1; --c1;
    --r2; --c2;
    int rookValue = rook[make_pair(r1, c1)];
    moveRook(r1, c1, rookValue);
    moveRook(r2, c2, rookValue);
    printf("%lld\n",sol);
  }
}

int main(void) {
  init();
  solve();
  return 0;
}
