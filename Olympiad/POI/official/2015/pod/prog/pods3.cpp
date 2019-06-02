/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Podzial naszyjnika                                 *
 *   Autor programu:       Tomasz Syposz                                      *
 *   Zlozonosc czasowa:    O(n^2)                                             *
 *   Opis:                 Rozwiazanie wolne, laczenie takich samych korali   *
 *                                            w grupy                         *
 *****************************************************************************/


#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1000005;

int n, k;
int t[MAXN];
int d[MAXN];
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
  int ii = 0;
  scanf("%d",&t[ii]);
  d[ii]++;
  cnt[t[ii]]++;
  for (int i = 1; i < n; ++i) {
	int a;
    scanf("%d", &a);
    if(a != t[ii]){
		ii++;
		t[ii] = a;
	}
    d[ii]++;
    ++cnt[t[ii]];
  }
  ii++;
  //printf("%d\n", ii);
  //for(int i = 0; i < ii; i++) printf("%d ", t[i]); printf("\n");
  //for(int i = 0; i < ii; i++) printf("%d ", d[i]); printf("\n");
  long long res = 0;
  int bestDiff = MAXN;

  for (int i = 0; i < ii; ++i) {
    int cntOk = k;
    for (int j = 1; j <=k; ++j) {
      ok[j] = true;
      curCnt[j] = 0;
    }
    int len = 0;
    for (int l = 1; l < ii; ++l) {
      int pos = (i+l-1) % ii;
      curCnt[t[pos]] += d[pos];
      len += d[pos];
      //printf(">>%d %d %d\n", t[pos],d[pos],cnt[t[pos]]);
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
		//printf("%d %d\n", i,l);
        ++res;
        bestDiff = min(bestDiff, myabs(n - 2*len));
      }
    }
  }
  printf("%lld %d\n", res / 2, bestDiff);
  return 0;
}
