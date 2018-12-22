#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;

const int MAXN = 1 << 20;

int n;

set <int> S[MAXN];
int find (int pos, int v) {
  set<int>::iterator it = S[v].lower_bound(pos);
  if (it == S[v].end()) return -1;
  return *it;
}

int v[MAXN];

int main (void){
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    S[v[i]].insert(i);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
   if (S[v[i]].count(i) == 0) continue;
   int pos = i;
   ++ans;
   while (pos >= 0) {
      S[v[pos]].erase(pos);
      pos = find(pos, v[pos] - 1);
   }
  }

  printf("%d\n", ans);

  return 0;
}
