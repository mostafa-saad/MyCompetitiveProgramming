/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pieczec                                            *
 *   Autor programu:       Dawid Dabrowski                                    *
 *   Zlozonosc czasowa:    O(n^2*m^2)                                         *
 *   Zlozonosc pamieciowa: O(n*m)                                             *
 *   Opis:                 rozwiazanie powolne                                *
 *****************************************************************************/

#include <cstdio>
#include <set>
#include <vector>

using namespace std;

const int MX = 1005;

int a, b, x, y;
char goal[MX][MX], stamp[MX][MX];
vector<pair<int, int> > stampxs;
set<pair<int, int> > goalxs;

int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
  stampxs.clear();
  goalxs.clear();
  bool ok = true;
  scanf("%d%d%d%d", &a, &b, &x, &y);

  for (int i = 0; i < a; ++i) {
    scanf("%s", goal[i]);
  }
  for (int i = 0; i < x; ++i) {
    scanf("%s", stamp[i]);
  }

  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) {
      if (goal[i][j] == 'x') {
        goalxs.insert(make_pair(i, j));
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
  if (goalxs.size() == 0) {
    printf("TAK\n");
    continue;
  }
  if (stampxs.size() == 0) {
    printf("NIE\n");
    continue;
  }
  if (goalxs.size() % stampxs.size() != 0) {
    printf("NIE\n");
    continue;
  }

  for (int i = 1; i < (int) stampxs.size(); ++i) {
    stampxs[i].first -= stampxs[0].first;
    stampxs[i].second -= stampxs[0].second;
  }
  stampxs[0].first = stampxs[0].second = 0;

  int res = 0;
  while (!goalxs.empty() && ok) {
    pair<int, int> cur = *goalxs.begin();
//    printf("cur = %d %d\n", cur.first, cur.second);
    ++res;
    for (int i = 0; i < (int) stampxs.size(); ++i) {
      pair<int, int> painted = make_pair(
        cur.first + stampxs[i].first,
        cur.second + stampxs[i].second);
//      printf("painted = %d %d\n", painted.first, painted.second);
      if (goalxs.find(painted) == goalxs.end()) {
        printf("NIE\n");
        ok = false;
        break;
      }
      goalxs.erase(painted);
    }
  }

  if (!goalxs.empty() && ok) {
    printf("NIE\n");
    continue;
  }
  
  if (ok)
      printf("TAK\n");
  }
  return 0;
}
