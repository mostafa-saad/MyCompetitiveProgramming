#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100;
const int MAXLEN = 10;

int N, M;
char word[MAXN][MAXLEN + 1];
bool seen[26];
bool greater[26][26];
vector< pair< int, char > > ret;

int main(void)
{
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%s", word[i]);

  for (int i = 0; i < N; ++i)
    for (char *p = word[i]; *p; ++p) {
      M += !seen[*p - 'a'];
      seen[*p - 'a'] = true;
    }

  for (int i = 0; i < N - 1; ++i) {
    char *a = word[i];
    char *b = word[i + 1];
    while (*a && *b && *a == *b) {
      ++a;
      ++b;
    }
    if (*a && *b) 
      greater[*b - 'a'][*a - 'a'] = true;

    if (*a && !*b) {
      puts("!");
      return 0;
    }
  }

  for (int k = 0; k < 26; ++k)
    for (int i = 0; i < 26; ++i)
      for (int j = 0; j < 26; ++j)
        greater[i][j] |= greater[i][k] && greater[k][j];

  for (int i = 0; i < 26; ++i)
    if (greater[i][i]) {
      puts("!");
      return 0;
    }

  for (int i = 0; i < 26; ++i) {
    if (!seen[i]) continue;
    int out = 0;
    int in = 0;
    for (int j = 0; j < 26; ++j) {
      out += greater[i][j];
      in += greater[j][i];
    }
    if (out + in != M - 1) {
      puts("?");
      return 0;
    }
    ret.push_back(make_pair(out, 'a' + i));
  }

  sort(ret.begin(), ret.end());

  for (int i = 0; i < ret.size(); ++i)
    printf("%c", ret[i].second);
  printf("\n");

  return 0;
}
