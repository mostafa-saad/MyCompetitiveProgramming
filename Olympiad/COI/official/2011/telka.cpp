#include <algorithm>
#include <cstdio>

using namespace std;

#define DAY 86400

int start[2 * DAY + 1];
int end[2 * DAY + 1];
long long popularity_sum[2 * DAY + 1];

int get_seconds(int hh, int mm, int ss) {
  return (hh * 60 + mm) * 60 + ss;
}

int main(void) {
  int n, hh1, hh2, mm1, mm2, ss1, ss2;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d:%d:%d - %d:%d:%d", &hh1, &mm1, &ss1, &hh2, &mm2, &ss2);
    int t1 = 1 + get_seconds(hh1, mm1, ss1);
    int t2 = 1 + get_seconds(hh2, mm2, ss2);
    if (t2 < t1) {
      t2 += DAY;
    }
    ++start[t1];
    ++end[t2];
  }

  int popularity = 0;
  for (int i = 1; i <= 2*DAY; ++i) {
    popularity += start[i];
    popularity_sum[i] = popularity_sum[i-1] + popularity;
    popularity -= end[i];
  }
  
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d:%d:%d - %d:%d:%d", &hh1, &mm1, &ss1, &hh2, &mm2, &ss2);
    int t1 = 1 + get_seconds(hh1, mm1, ss1);
    int t2 = 1 + get_seconds(hh2, mm2, ss2);
    if (t2 < t1) {
      t2 += DAY;
    }

    long long ret = 0;
    for (int offset = -1; offset <= 1; ++offset) {
      int tt1 = max(0, min(2 * DAY, offset * DAY + t1 - 1));
      int tt2 = max(0, min(2 * DAY, offset * DAY + t2));
      ret += popularity_sum[tt2] - popularity_sum[tt1];
    }
    printf("%.10lf\n", ret / (double)(t2-t1+1));
  }

  return 0;
}
