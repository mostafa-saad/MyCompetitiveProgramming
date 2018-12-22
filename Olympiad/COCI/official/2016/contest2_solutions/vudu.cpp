#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1 << 20;
typedef pair <double, int> pdi;

int n;
double a[MAXN];

bool cmp (const pdi &A, const pdi &B) {
  if (A.first != B.first) return A.first < B.first;
  return A.second < B.second;
}

int loga[MAXN];
void update (int pos) {
  pos += 10;
  while (pos < MAXN) {
    ++loga[pos];
    pos += pos&-pos;
  }
}

int query (int pos) {
  pos += 10;
  int ret = 0;
  while (pos > 0) {
    ret += loga[pos];
    pos -= pos&-pos;
  }
  return ret;
}

int main (void){
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%lf", &a[i]);
  int p;
  scanf("%d", &p);

  for (int i = 0; i < n; ++i) {
    a[i] -= p;
    if (i > 0) a[i] += a[i-1];
  }

  vector <pdi> V;
  for (int i = 0; i < n; ++i)
    V.push_back(pdi(a[i], i));
  V.push_back(pdi(0, -1));

  sort(V.begin(), V.end(), cmp);
  int pos = 0;
  long long ans = 0;
  for (int i = 0; i < V.size(); ++i) {
    while (pos < i && (V[i].first - V[pos].first) >= 0) update(V[pos++].second);
    ans += query(V[i].second);
  }

  printf("%lld\n", ans);


  return 0;
}
