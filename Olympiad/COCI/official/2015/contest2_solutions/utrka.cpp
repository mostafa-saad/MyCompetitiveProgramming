#include <cstdio>
#include <cstring>

int main(void) {

  char tmp[21];
  int cnt[26][20];

  memset(cnt, 0, sizeof cnt);

  int n;
  scanf("%d", &n);

  for(int i = 0; i < 2*n-1; ++i) {
    scanf("%s", tmp);
    for(int j = 0; tmp[j] != '\0'; ++j)
      cnt[tmp[j]-'a'][j]++;
  }

  for(int i = 0; i < 20; ++i) {
    for(int c = 'a'; c <= 'z'; ++c)
      if(cnt[c-'a'][i] % 2 == 1) printf("%c", c);
  }

  printf("\n");

}
