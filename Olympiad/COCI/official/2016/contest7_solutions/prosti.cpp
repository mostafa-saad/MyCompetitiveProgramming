#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 5000000;
const int MAXK = 150;

bool np[MAXN];
int psum[MAXN], k, l, m;

void eratosten(void) {
  np[1] = false;
  for (int p = 2; p * p < MAXN; ++p)
    if (!np[p])
      for (int q = 2; p * q < MAXN; ++q)
	np[p * q] = true;
}

int count_happy(int a, int b) {
  if (a > b) return 0;
  if (b <= m) return (b - a + 1);
  if (a <= m) return (m - a + 1) + count_happy(m + 1, b);
  return psum[b] - psum[a - 1];
}

bool between(int a, int b, int c) {
  if (a > b) swap(a, b);
  return c >= a && c <= b;
}

int main(void) {
  eratosten();
  int zero_start = 0;
  for (int i = 2; i < MAXN; ++i) {
    psum[i] = psum[i - 1] + (!np[i] ? 1 : 0);
    if (i >= MAXK && psum[i] - psum[i - MAXK] == 0)
      zero_start = i - MAXK;
  }

  int q;
  scanf("%d",&q);
  while (q-- > 0) {
    scanf("%d %d %d",&k,&l,&m);

    int lo = 1, hi = zero_start, res = -1;
    int count_lo = count_happy(1, k);;

    while (lo <= hi) {
      int mid = (lo + hi) / 2;

      if (count_happy(mid, mid + k - 1) == l) {
	res = mid;
	break;
      } else if (between(count_lo, count_happy(mid - 1, mid + k - 2), l)) {
	hi = mid - 1;
      } else {
	lo = mid + 1;
	count_lo = count_happy(lo, lo + k - 1);
      }
    }


    printf("%d\n",res);
  }

  return 0;
}
