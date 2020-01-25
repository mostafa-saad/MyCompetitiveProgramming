#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

int n;
char input[MAXN];
vector<int> adj[MAXN];

int stk_sz = 1;
char stk[2 * MAXN];
int pivot = 0;
int ans = 1;

int manacher() {
  static int rad[2 * MAXN];

  int x = 0;
  for (int i = 1; i < stk_sz; ++i) {
    int &r = rad[i] = 0;
    if (i <= x + rad[x])
      r = min(rad[2 * x - i], x + rad[x] - i);
    while (i - r - 1 >= 0 && i + r + 1 < stk_sz &&
        stk[i - r - 1] == stk[i + r + 1]) ++r;
    if (i + r >= x + rad[x]) x = i;
  }

  int ret = 0;
  for (int i = 0; i < stk_sz; ++i)
    if (rad[i] > ret)
      ret = rad[i];
  return ret;
}

void dfs(int x, int prev = -1) {
  stk[stk_sz++] = input[x];
  stk[stk_sz++] = '*';
  if (adj[x].size() == 1 && x < pivot)
    ans = max(ans, manacher());
  for (int y : adj[x]) {
    if (y == prev) continue;
    dfs(y, x);
  }
  stk_sz -= 2;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin >> n;
  cin >> input;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  stk[0] = '*';
  for (int i = 0; i < n; ++i) {
    if (adj[i].size() != 1)
      continue;
    pivot = i;
    dfs(i);
  }
  cout << ans << endl;
  return 0;
}
