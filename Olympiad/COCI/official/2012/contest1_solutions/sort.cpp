#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct fenwick {
  static const int MAXA = 100100;
  int A[MAXA];

  fenwick() { 
    memset(A, 0, sizeof A); 
  }
  void add(int at, int val) {
    for (int i = at; i < MAXA; i += i & -i) 
      A[i] += val;
  }
  int query(int at) {
    int ret = 0;
    for (int i = at; i > 0; i -= i & -i) 
      ret += A[i];
    return ret;
  }
} L;

int N;
vector< int > V;
long long R;

void part_one() {
  vector< int >::iterator l, r;
  l = r = V.begin();
  while (l != V.end()) {
    ++r;
    if (r == V.end() || *(r - 1) < *r) {
      if (r - 1 - l) {
        reverse(l, r);
        ++R;
      }
      l = r;
    }
  }
}

void part_two() {
  for (int i = N - 1; i >= 0; --i) {
    R += L.query(V[i]);
    L.add(V[i], 1);
  }
}

int main(void) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    int x; scanf("%d", &x);
    V.push_back(x);
  }

  part_one();
  part_two();

  printf("%lld\n", R);
  return 0;
}
