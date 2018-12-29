/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Podzial naszyjnika                                 *
 *   Autor programu:       Dawid Dabrowski                                    *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1000005;
const int M = 1 << 20;

#define myabs(x) ((x) < 0 ? (-(x)) : (x))

int n, k;
int t[MAXN];
int first[MAXN], last[MAXN];
vector<int> v[MAXN]; // te, ktore w danym momencie staja sie niedostepne

// {{{ Drzewo d1
int d1[2*M]; // kiedy dany punkt bedzie niedostepny przez to, ze rozbilby jakas grupe, ktora juz zamietlismy
void d1_init() {
  for (int i = 0; i < 2*M; ++i) {
    d1[i] = -1;
  }
}
void d1_add(int a, int b, int val) {
  if (a > b) return;
  a += M;
  b += M;
  d1[a] = max(d1[a], val);
  d1[b] = max(d1[b], val);
  while (a/2 != b/2) {
    if (a % 2 == 0) {
      d1[a+1] = max(d1[a+1], val);
    }
    if (b % 2 == 1) {
      d1[b-1] = max(d1[b-1], val);
    }
    a /= 2;
    b /= 2;
  }
}
int d1_get(int a) {
  a += M;
  int res = -1;
  while (a) {
    res = max(res, d1[a]);
    a /= 2;
  }
  return res;
}
// }}}

// {{{ Drzewo d2
int d2[2*M]; // drzewo dostepnych punktow, uwzgledniajac te, ktore odpadly przez v[]
void d2_add(int x, int val) {
  x += M;
  while (x) {
    d2[x] += val;
    x /= 2;
  }
}
int d2_get(int a, int b) {
  if (a > b) return 0;
  int res = 0;
  a += M;
  b += M;
  res += d2[a];
  if (a != b) {
    res += d2[b];
  }
  while (a/2 != b/2) {
    if (a % 2 == 0) {
      res += d2[a+1];
    }
    if (b % 2 == 1) {
      res += d2[b-1];
    }
    a /= 2;
    b /= 2;
  }
  return res;
}
void d2_init() {
  for (int i = 0; i < n; ++i) {
    d2_add(i, 1);
  }
}
// }}}

// {{{ Drzewo d3
int d3[2*M]; // jak daleko mozemy skonczyc przedzial, zaczynajac w danym punkcie, nie rozbijajac jakiejs niezamiecionej jeszcze do konca grupy
void d3_init() {
  for (int i = 0; i < 2*M; ++i) {
    d3[i] = n;
  }
}
void d3_add(int a, int b, int val) {
  if (a > b) return;
  a += M;
  b += M;
  d3[a] = min(d3[a], val);
  d3[b] = min(d3[b], val);
  while (a/2 != b/2) {
    if (a % 2 == 0) {
      d3[a+1] = min(d3[a+1], val);
    }
    if (b % 2 == 1) {
      d3[b-1] = min(d3[b-1], val);
    }
    a /= 2;
    b /= 2;
  }
}
int d3_get(int a) {
  a += M;
  int res = n;
  while (a) {
    res = min(res, d3[a]);
    a /= 2;
  }
  return res;
}
// }}}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &t[i]);
  }
  for (int i = 1; i <= k; ++i) {
    first[i] = last[i] = -1;
  }
  d3_init();
  for (int i = 0; i < n; ++i) {
    if (first[t[i]] == -1) {
      first[t[i]] = i;
    } else {
      // printf("d3_add %d %d %d\n", last[t[i]]+1, i, i-1);
      d3_add(last[t[i]]+1, i, i-1);
    }
    last[t[i]] = i;
  }
  d1_init();
  for (int i = 1; i <= k; ++i) {
    if (first[i] != last[i]) {
      // printf("%d first %d last %d\n", i, first[i], last[i]);
      d1_add(first[i], last[i]-1, first[i]);
    }
  }
  for (int i = 0; i < n; ++i) {
    int tim = d1_get(i);
    // printf("tim %d  = %d\n", i, tim);
    if (tim != -1) {
      v[tim].push_back(i);
    }
  }
  long long res = 0;
  int best = MAXN;
  d2_init();
  for (int i = n; i >= 1; --i) {
    for (int j = 0; j < (int) v[i].size(); ++j) {
      d2_add(v[i][j], -1);
    }
    int max_last = d3_get(i);
    // printf("i = %d max_last = %d\n", i, max_last);
    if (i > max_last) continue;
    int cur = d2_get(i, max_last);
    res += cur;
    if (cur <= 0) {
      continue;
    }
    
    // probujemy uzyskac najlepsza roznice
    int best_last = i + n/2 - 1;
    if (best_last > max_last) best_last = max_last;
    int best_left = best_last; // najwiekszy mniejszy rowny od best_last
    best_left += M;
    if (d2[best_left] == 0) {
      while (best_left) {
        if (best_left % 2 == 1) {
          if (d2[best_left-1] > 0) {
            --best_left;
            while (best_left < M) {
              if (d2[2*best_left + 1] > 0) {
                best_left = 2*best_left + 1;
              } else {
                best_left = 2*best_left;
              }
            }
            break;
          }
        }
        best_left /= 2;
      }
    }
    if (best_left != -1) {
      best_left -= M;
      if (best_left >= i) {
        int len = best_left - i + 1;
        best = min(best, myabs(n - 2*len));
      }
    }

    int best_right = best_last+1; // najmniejszy wiekszy rowny od best_last+1
    if (best_right <= n) {
      best_right += M;
      if (d2[best_right] == 0) {
        while (best_right) {
          if (best_right % 2 == 0) {
            if (d2[best_right+1] > 0) {
              ++best_right;
              while (best_right < M) {
                if (d2[2*best_right]) {
                  best_right = 2*best_right;
                } else {
                  best_right = 2*best_right + 1;
                }
              }
              break;
            }
          }
          best_right /= 2;
        }
      }
    } else {
      best_right = -1;
    }
    if (best_right != -1) {
      best_right -= M;
      if (best_right <= max_last) {
        int len = best_right - i + 1;
        best = min(best, myabs(n - 2*len));
      }
    }
  }
  printf("%lld %d\n", res, best);
  return 0;
}
