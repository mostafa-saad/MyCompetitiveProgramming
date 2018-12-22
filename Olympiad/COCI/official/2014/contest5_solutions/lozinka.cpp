#include <cstdio>
#include <cstring>

const int maxn = 100;
const int maxk = 16;

int N;
char lista[maxn][maxk];
char tmp[maxk];

void load() {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%s", (char*) lista[i]);
}

bool ispravna(char *str) {
  int k = strlen(str);
  for (int j = 0; j < k; ++j)
    tmp[k - j - 1] = str[j];
  tmp[k] = 0;
  for (int i = 0; i < N; ++i)
    if (!strcmp(lista[i], tmp))
      return 1;
  return 0;
}

int main() {
  load();
  for (int i = 0; i < N; ++i) {
    if (ispravna(lista[i])) {
      int k = strlen(lista[i]);
      printf("%d %c\n", k, lista[i][k/2]);
      return 0;
    }
  }
  return 1;
}
