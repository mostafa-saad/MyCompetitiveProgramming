/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Wcale nie Nim                                      *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiązanie wzorcowe                               *
 *****************************************************************************/

#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
const int INF = 99999999;

int n;

int Log(int n) { return (n == 1) ? 0 : 1 + Log(n/2); }

int LeadingOnes(int n) {
  int res = 0;
  for (int i = 29; i >= 0; i--) {
    if (((1<<i) & n) != 0) res++;
    else if (res > 0) break;
  }
  return res;
}

multiset<int> M;

int main() {
  int result = -1;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int size;
    scanf("%d", &size);
    result += 2 * Log(size) + 4;
    int p = LeadingOnes(size);
    M.insert(-p);
  }

  M.erase(M.begin());
  while (!M.empty()) {
    int best = *(M.begin());
    if (best == -1) {
      M.erase(M.begin());
      result -= 2;
    }
    else {
      M.erase(M.begin());
      M.insert(best+1);
      M.erase(M.begin());
    }
  }

  printf("%d\n", result);

  return 0;
}
