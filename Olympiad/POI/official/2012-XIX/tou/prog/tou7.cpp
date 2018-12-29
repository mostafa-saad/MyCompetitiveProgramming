/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O((n + m) * log^*(n + m))                        *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                      Find-union                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
struct FAU {
  int *p;
  int *s;
  FAU(int sz) {
    p = new int[sz];
    s = new int[sz];
    for(int i = 0; i < sz; i++) {
      p[i] = -1;
      s[i] = 1;
    }
  }
  
  ~FAU() {
    delete p;
    delete s;
  }

  int Find(int x) {
    return (p[x] < 0) ? x : p[x] = Find(p[x]);
  }

  bool Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (s[y] > s[x]) {
      s[y] += s[x]; p[x] = y;
    } else {
      s[x] += s[y]; p[y] = x;
    }
    return true;
  }
};

int main() {
  int n, m, k, a, b;
  std::vector<std::pair<int, int> > c, ret;
  scanf("%d%d%d", &n, &m, &k);
  FAU f(n + 1);
  for(int i = 0; i < m; i++) {
    scanf("%d%d", &a, &b);
    if (a > k) {
      f.Union(a, b);
    } else {
      c.push_back(std::make_pair(a, b));
    }
  }
  for(size_t i = 0; i < c.size(); i++) {
    if (!f.Union(c[i].first, c[i].second)) {
      ret.push_back(c[i]);
    }
  }
  printf("%d\n", static_cast<int>(ret.size()));
  for(size_t i = 0; i < ret.size(); i++) {
    printf("%d %d\n", ret[i].first, ret[i].second);
  }
  return 0;
}
