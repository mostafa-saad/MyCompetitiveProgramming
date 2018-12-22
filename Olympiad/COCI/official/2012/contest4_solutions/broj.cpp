#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
                           
typedef long long llint;
const int C = 50;
const int MAX = 1000000000;

llint f(int mid, int p) {
  vector<int> prime, v(p, 0);
  for (int i = 2; i < p; ++i)
    if (!v[i]) {
      prime.push_back(i);
      for (int j = i + i; j < p; j += i)
        v[j] = 1;
    }

  llint ret = mid;
  for (int mask = 1; mask < (1 << (int) prime.size()); ++mask) {
    llint d = 1, sgn = -1;

    for (int i = 0; i < prime.size(); ++i)
      if (mask & (1 << i)) {
        d *= prime[i];
        if (d > mid) break;
        sgn *= -1;
      }
    
    ret -= sgn * mid / d;
  }
  
  return ret;
}

void solve_small(int n, int p) {
  int ans = 0;

  int lo = 1;
  int hi = MAX / p;

  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;    
    long long k = f(mid, p);
    if (k < n)
      lo = mid + 1;
    else
      hi = mid;
  }
  
  if (f(lo, p) == n)
    ans = lo * p;
  
  printf("%d\n", ans);
}

void solve_large(int n, int p) {
  int ans = 0;
  if (n == 1) 
    ans = p;
  
  int len = MAX / p + 1;
  char* v = new char[len];
  memset(v, 0, len);
  
  for (int i = 2, k = 1; i < len; ++i)
    if (!v[i]) {
      if (i < p)
        for (llint j = (llint) i * i; j < len; j += i)
          v[j] = 1;
      else {
        ++k;
        if (k == n)
          ans = i * p;
      }
    }
  
  delete[] v;
  printf("%d\n", ans);
}

int main(void) {
  int n, p;
  scanf("%d %d", &n, &p);

  if (p < C)
    solve_small(n, p);
  else 
    solve_large(n, p);

  return 0;
}
