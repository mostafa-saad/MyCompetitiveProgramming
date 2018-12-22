#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1 << 17;

int n;

char polje[10][MAXN];

vector <int> V;
bool dfs (int x, int y) {
  if (polje[x][y] == 'X') return 0;
  if (y == n-1) return 1;
  polje[x][y] = 'X';
  if (dfs(min(9, x+1), y+1)) return 1;
  if (dfs(max(0, x-1), y+1)) {
    V.push_back(y);
    return 1;
  }
  return 0;
}

int main (void){
  scanf("%d", &n);
  for (int i = 0; i < 10; ++i)
    scanf("%s", &polje[i]);
  assert(dfs(9, 0) == 1);
  reverse(V.begin(), V.end());
  printf("%d\n", V.size());
  for (auto x: V)
    printf("%d %d\n", x, 1);
  return 0;
}

