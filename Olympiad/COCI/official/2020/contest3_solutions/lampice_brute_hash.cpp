#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef pair<long long, long long> hash_t;

hash_t operator+(hash_t a, hash_t b) { return {a.x + b.x, a.y + b.y}; }
hash_t operator*(hash_t a, hash_t b) { return {a.x * b.x, a.y * b.y}; }
hash_t operator+(hash_t a, char b) { return {a.x + b, a.y + b}; }
hash_t operator*(hash_t a, char b) { return {a.x * b, a.y * b}; }

const int MAXN = 100100;
const hash_t BASE = {31337, 10007};

int n;
char input[MAXN];
vector<int> adj[MAXN];
hash_t P[MAXN];

int ans = 1;

void rec(int x, int prev = -1, hash_t down = {0, 0}, hash_t up = {0, 0}, int len = 1) {
  down = down * BASE + input[x];
  up = up + P[len - 1] * input[x];
  if (up == down && len > ans)
    ans = len;
  for (int y : adj[x]) {
    if (y == prev) continue;
    rec(y, x, down, up, len + 1);
  }
}

int main(void) {
  cin >> n;
  cin >> input;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  P[0] = {1, 1};
  for (int i = 1; i < n; ++i)
    P[i] = P[i - 1] * BASE;
  for (int i = 0; i < n; ++i)
    rec(i);
  cout << ans << endl;
  return 0;
}
