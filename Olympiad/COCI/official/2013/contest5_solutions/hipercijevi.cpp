#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define FORC(it, C) for(__typeof((C).begin()) it = (C).begin(); it != (C).end(); ++it)

const int MAXN = 100000;
const int MAXK = 1000;
const int MAXM = 1000;

int n, m, k;
std::vector< int > E[MAXN+MAXM];
std::queue< int > Q;
int distance[MAXN+MAXM];

int main() {
  scanf("%d%d%d", &n, &k, &m);

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      int a;
      scanf("%d", &a);
      --a;
      E[MAXN+i].push_back(a);
      E[a].push_back(MAXN+i);
    }
  }

  memset(distance, -1, sizeof(distance));
  distance[0] = 0;
  for (Q.push(0); !Q.empty(); Q.pop()) {
    int x = Q.front();
    FORC(it, E[x]) {
      if (distance[*it] == -1) {
        distance[*it] = distance[x] + 1;
        Q.push(*it);
      }
    }
  }

  if (distance[n-1] == -1) {
    printf("%d\n", -1);
  } else {
    printf("%d\n", distance[n-1]/2+1);
  }

  return 0;
}
