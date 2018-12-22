#include <stdio.h>
#include <string.h>

int main(void) {

  int k, t;
  int i;
  int x;
  int m1, m2, m3, m4;
  int p[21], br[21];
  int rj;

  memset(br, 0, sizeof br);

  scanf("%d", &k);
  for(i = 1; i <= k; ++i)
    scanf("%d", &p[i]);
  scanf("%d", &x);
  scanf("%d%d%d%d", &m1, &m2, &m3, &m4);
  scanf("%d", &t);
  for(i = 0; i < t; ++i) {
    int o; 
    scanf("%d", &o);
    ++br[o];
  }

  rj = 0;

  while(br[m1] + br[m2] + br[m3] + br[m4] > 0) {
    int c = 0;
    if(br[m1] > 0) c = c + p[m1];
    if(br[m2] > 0) c = c + p[m2];
    if(br[m3] > 0) c = c + p[m3];
    if(br[m4] > 0) c = c + p[m4];
    if(c > x) rj += x; else rj += c;
    if(br[m1] > 0) --br[m1];
    if(br[m2] > 0) --br[m2];
    if(br[m3] > 0) --br[m3];
    if(br[m4] > 0) --br[m4];
  }

  for(i = 1; i <= 20; ++i)
    rj += br[i] * p[i];

  printf("%d\n", rj);

  return 0;

}
