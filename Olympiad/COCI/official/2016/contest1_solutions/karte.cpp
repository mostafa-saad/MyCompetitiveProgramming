#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXB = 5;
const int MAXN = 20;

bool bio[MAXB][MAXN];

int getColor(char chr) {
  if (chr == 'P') return 0;
  if (chr == 'K') return 1;
  if (chr == 'H') return 2;
  if (chr == 'T') return 3;
}

int main(void) {
  string s;
  cin >> s;
  for (int i = 0; i < s.size(); i += 3) {
    int b = getColor(s[i]);
    int x = (s[i + 1] - '0') * 10 + s[i + 2] - '0';
    if (bio[b][x]) {
      printf("GRESKA\n");
      return 0;
    }
    bio[b][x] = true;
  }

  for (int i = 0; i < 4; ++i) {
    int cnt = 0;
    for (int j = 1; j <= 13; ++j)
      if (bio[i][j])
	++cnt;
    printf("%d ",13 - cnt);
  }
  printf("\n");
    
  return 0;
}
