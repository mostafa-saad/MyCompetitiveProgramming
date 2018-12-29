/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pieczec                                            *
 *   Autor programu:       Dawid Dabrowski                                    *
 *   Zlozonosc czasowa:    O(n^2*m^2)                                         *
 *   Zlozonosc pamieciowa: O(n*m)                                             *
 *   Opis:                 rozwiazanie nieoptymalne                           *
 *****************************************************************************/


#include <cstdio>
#include <vector>

using namespace std;

const int MX = 1005;

int a, b, x, y;
char goal[MX][MX], stamp[MX][MX];
vector<pair<int, int> > stampxs;

int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
  stampxs.clear();
  bool ok = true;
  scanf("%d%d%d%d", &a, &b, &x, &y);

  for (int i = 0; i < a; ++i) {
    scanf("%s", goal[i]);
  }
  for (int i = 0; i < x; ++i) {
    scanf("%s", stamp[i]);
  }

  int toPaint = 0;

  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) {
      if (goal[i][j] == 'x') {
        toPaint++;
      }
    }
  }
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      if (stamp[i][j] == 'x') {
        stampxs.push_back(make_pair(i, j));
      }
    }
  }
  if (toPaint == 0) {
    printf("TAK\n");
    continue;
  }
  if (stampxs.size() == 0) {
    printf("NIE\n");
    continue;
  }
  if (toPaint % stampxs.size() != 0) {
    printf("NIE\n");
    continue;
  }

  for (int i = 1; i < (int) stampxs.size(); ++i) {
    stampxs[i].first -= stampxs[0].first;
    stampxs[i].second -= stampxs[0].second;
  }
  stampxs[0].first = stampxs[0].second = 0;

  int res = 0;
  while (toPaint) {
    pair<int, int> cur;
    for (int i = 0; i < a; ++i) {
      bool found = false;
      for (int j = 0; j < b; ++j) {
        if (goal[i][j] == 'x') {
          cur = make_pair(i, j);
          found = true;
          break;
        }
      }
      if (found) {
        break;
      }
    }
//    printf("cur = %d %d\n", cur.first, cur.second);
    ++res;
    for (int i = 0; i < (int) stampxs.size(); ++i) {
      pair<int, int> painted = make_pair(
        cur.first + stampxs[i].first,
        cur.second + stampxs[i].second);
//      printf("painted = %d %d\n", painted.first, painted.second);
      if (painted.first >= 0 && painted.first < a &&
          painted.second >= 0 && painted.second < b &&
          goal[painted.first][painted.second] == 'x') {
        --toPaint;
        goal[painted.first][painted.second] = '.';
      } else {
        ok = false;
        toPaint = false;
        break;
      }
    }
  }

  if (toPaint || (!ok)) {
    printf("NIE\n");
    continue;
  }
  
  if (ok)
      printf("TAK\n");
  }
  return 0;
}
