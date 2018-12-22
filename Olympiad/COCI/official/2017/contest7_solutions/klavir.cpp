#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1 << 20;
const int mod = 1e9 + 7;

typedef long long llint;

int str[MAXN];
int fail[MAXN];

int pot[MAXN];
int A;

int ans;

void add(int &x, int delta) {
  x += delta;
  if (x >= mod)
    x -= mod;
}

void sub(int &x, int delta) {
  x -= delta;
  if (x < 0)
    x += mod;
}

void set(int previous, int curr) {
  while (previous != curr) {
    if (previous > curr)
      sub(ans, pot[previous]), previous = fail[previous];
    if (curr > previous)
      add(ans, pot[curr]), curr = fail[curr];
  }
}

int n;

int main(void) {
  scanf("%d", &A);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &str[i]);
  pot[0] = 1;
  for (int i = 1; i < MAXN; ++i)
    pot[i] = ((llint)pot[i - 1] * A) % mod;
  fail[1] = 0;
  for (int i = 2; i <= n; ++i) {
    int back = fail[i - 1];
    while (back != 0 && str[back] != str[i - 1])
      back = fail[back];
    if (str[back] == str[i - 1])
      ++back;
    fail[i] = back;
  }
  int curr = 0;
  for (int i = 1; i <= n; ++i) {
    set(curr, i);
    curr = i;
    printf("%d\n", ans);
  }
  return 0;
}
