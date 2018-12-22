#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int INF = 1 << 30;
const int MAXN = 300000;

int N, C;
pair< int, int > nxt[MAXN];
#define who first
#define amount second
vector< int > prev[MAXN];

int seen[MAXN];
bool ignore[MAXN];
vector< int > cycle[MAXN];

void find_cycles()
{
  for (int i = 1; i <= N; ++i) {
    int node = i;

    if (!seen[node]) {
      for (; !seen[node]; node = nxt[node].who)
        seen[node] = i;
      if (seen[node] != i) continue;

      for (; !ignore[node]; node = nxt[node].who) {
        ignore[node] = 1;
        cycle[C].push_back(node);
      }
      C++;
    }
  }
}

int ret;
int money[MAXN];

void solve(int node)
{
  if (ignore[node]) return;
  ignore[node] = 1;

  for (int i = 0; i < prev[node].size(); ++i)
    solve(prev[node][i]);

  money[nxt[node].who] += nxt[node].amount;
  ret -= min(money[node] - nxt[node].amount, 0);
}

void solve_outside_cycles()
{
  for (int i = 1; i <= N; ++i)
    solve(i);
}

void solve_cycles() 
{
  for (int c = 0; c < C; ++c) {
    int min_cost = INF, start = -1;
    
    for (int i = 0; i < cycle[c].size(); ++i) {
      int cost = -min(money[cycle[c][i]] - nxt[cycle[c][i]].amount, 0);
      if (cost < min_cost) {
        min_cost = cost;
        start = cycle[c][i];
      }
    }

    ret += min_cost;
    money[nxt[start].who] += nxt[start].amount;

    for (int node = nxt[start].who; node != start; node = nxt[node].who) {
      money[nxt[node].who] += nxt[node].amount;
      ret -= min(money[node] - nxt[node].amount, 0);
    }
  }
}

int main(void)
{
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d %d", &nxt[i].who, &nxt[i].amount);
    prev[nxt[i].who].push_back(i);
  }
  
  find_cycles();
  solve_outside_cycles();
  solve_cycles();

  printf("%d\n", ret);
  return 0;           
}
