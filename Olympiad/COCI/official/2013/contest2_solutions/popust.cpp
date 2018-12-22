#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>

#include <set>

using namespace std;

struct Jelo { 
  int a, b;

  friend bool operator < (const Jelo& A, const Jelo& B) {
    return A.b < B.b;
  }
};

typedef long long llint;

const int MAXN = 5e5 + 100;
const llint inf = 2e9;

Jelo jela[MAXN];

struct BestA {
  bool operator () (int a, int b) const {
    if (jela[a].a != jela[b].a)
      return jela[a].a < jela[b].a;
    return a < b;
  }
};

int main(void)
{
  int n; scanf("%d", &n);
  set<int, BestA> pq;

  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &jela[i].a, &jela[i].b);
  }

  llint minAminusB = +inf;
  llint sumaB = 0;

  sort(jela, jela + n);
  for (int i = 0; i < n; ++i) {
    pq.insert(i);
  }

  for (int k = 1; k <= n; ++k) {
    // najbolji A iz preostalih
    llint sol = sumaB + jela[*pq.begin()].a;

    // promijeni nekog iz B u A, dodaj novog B
    llint val = sumaB + jela[k-1].b + minAminusB;
    if (val < sol) sol = val;

    // ispisi
    printf("%lld\n", sol);

    // ubaci jela[k-1] u skup iskoristenih
    sumaB += jela[k-1].b;
    pq.erase(k-1);
    val = jela[k-1].a - jela[k-1].b;
    if (val < minAminusB) minAminusB = val;
  }
  
  return 0;
}
