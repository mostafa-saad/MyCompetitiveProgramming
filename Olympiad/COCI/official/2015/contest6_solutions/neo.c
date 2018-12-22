#include <stdio.h>

#define MAXN 1000

int max(int a, int b) {
  return a < b ? b : a;
}

int max_rect(int *p, int len) {
  int i;
  int h[MAXN], s[MAXN], ptr = 0;
  int ret = 0;

  for(i = 0; i < len; ++i) {
    int l = i;

    while(ptr > 0 && p[i] < h[ptr-1]) {
      ret = max(ret, (i-s[ptr-1]+1) * (h[ptr-1]+1));
      l = s[ptr-1];
      --ptr;
    }

    h[ptr] = p[i];
    s[ptr++] = l;
  }

  while(ptr > 0) {
    ret = max(ret, (len-s[ptr-1]+1) * (h[ptr-1]+1));
    --ptr;
  }

  return ret;
}

int main(void) {

  int r, s;
  int i, j;
  int a[MAXN][MAXN];
  int hist[MAXN];
  int sol;

  scanf("%d%d", &r, &s);
  for(i = 0; i < r; ++i)
    for(j = 0; j < s; ++j)
      scanf("%d", &a[i][j]);

  sol = 0;
  for(i = 0; i < r-1; ++i) {
    for(j = 0; j < s-1; ++j) {
      if(a[i][j]+a[i+1][j+1] <= a[i][j+1]+a[i+1][j])
        ++hist[j];
      else
        hist[j] = 0;
    }
    sol = max(sol, max_rect(hist, s-1));
  }

  printf("%d\n", sol);

  return 0;

}
