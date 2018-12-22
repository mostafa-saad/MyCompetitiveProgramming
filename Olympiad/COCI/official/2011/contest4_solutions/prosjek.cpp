#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long llint;

inline int cnt(llint n, int k) {
  int ans = 0;
  while (n % k == 0) {
    n /= k;
    ++ans;
  }
  return ans;
}

int main(void) {

  char buff[50];
  scanf("%s", buff);
  llint a = atoi(buff);
  llint b = atoi(buff + 2);

  int l = strlen(buff + 2);
  for (int i = 1; i <= l; ++i) 
    a *= 10;
  b += a;

  int n2 = cnt(b, 2);
  int n5 = cnt(b, 5);

  llint n = 1;
  while (n2 < l) {
    n *= 2;
    n2++;
  }
  while (n5 < l) {
    n *= 5;
    n5++;
  }

  llint sum = n * b;
  for (int i = 1; i <= l; ++i) 
    sum /= 10;

  llint ret[6] = {0};
  for (int i = 5; i >= 2; --i) {
    llint k = (sum - n) / (i - 1);
    n -= k;
    ret[i] = k;
    sum -= k * i;
  }
  ret[1] = n;

  for (int i = 1; i <= 5; ++i)
    printf("%lld%c", ret[i], (i < 5) ? ' ' : '\n');

  return 0;

}
