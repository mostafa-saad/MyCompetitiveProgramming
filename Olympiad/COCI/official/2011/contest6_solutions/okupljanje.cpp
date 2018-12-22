#include <cstdio>

int main() {
  int lj, p, x;

  scanf("%d %d", &lj, &p);

  for(int i = 0; i < 5; ++i) {
    scanf("%d", &x);
    printf("%d%s", x-lj*p, (i == 4 ? "\n" : " "));
  }

  return 0;
}
