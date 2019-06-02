/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Podzial naszyjnika                                 *
 *   Autor programu:       Dawid Dabrowski                                    *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/


#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1000005;

int n, k;
int t[MAXN];
int cnt[MAXN];
int curCnt[MAXN];
bool ok[MAXN];

int myabs(const int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}

int main() {
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &t[i]);
    ++cnt[t[i]];
  }

  long long res = 0;
  int bestDiff = MAXN;

  for (int i = 0; i < n; ++i) {
    int cntOk = k;
    for (int j = 1; j <=k; ++j) {
      ok[j] = true;
      curCnt[j] = 0;
    }
    for (int l = 1; l < n; ++l) {
      int pos = (i+l-1) % n;
      ++curCnt[t[pos]];
      if (curCnt[t[pos]] == cnt[t[pos]]) {
        if (!ok[t[pos]]) {
          ++cntOk;
        }
        ok[t[pos]] = true;
      } else {
        if (ok[t[pos]]) {
          --cntOk;
        }
        ok[t[pos]] = false;
      }
      if (cntOk == k) {
        ++res;
        bestDiff = min(bestDiff, myabs(n - 2*l));
      }
    }
  }
  printf("%lld %d\n", res / 2, bestDiff);
  return 0;
}
