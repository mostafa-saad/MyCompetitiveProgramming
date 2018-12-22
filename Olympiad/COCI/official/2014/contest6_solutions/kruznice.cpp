#include <cstdio>
#include <cassert>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct event {
  bool otvaram;
  int left, right, radius;

  event (bool otvaram, int left, int right, int radius) :
    otvaram(otvaram), left(left), right(right), radius(radius) { }

  inline int x() const { return otvaram ? left : right; }

  void debug() const {
    // printf("%s r:%d  %3d : %3d\n", otvaram ? "otv" :"zat", radius, left, right);
  }

  bool operator< (const event &rhs) const {
    if (x() != rhs.x()) return x() < rhs.x();
    if (otvaram != rhs.otvaram) return otvaram < rhs.otvaram;
    if (radius != rhs.radius) return radius > rhs.radius;
    return false;
  }
};

int N;
vector<event> evts;

void load() {
  scanf("%d", &N);
  for (int j = 0; j < N; ++j) {
    int c, r;
    scanf("%d%d", &c, &r);
    evts.push_back(event(true, c - r, c + r, r));
    evts.push_back(event(false, c - r, c + r, r));
  }
}

#define INIT 0
#define KONT 1
#define DISKONT 2

int solve() {
  sort(evts.begin(), evts.end());
  int sol = 0;
  stack<int> S;

  for (size_t j = 0; j < evts.size(); ++j) {
    event &e = evts[j];
    e.debug();
    if (S.size()) {
      int &parent_state = S.top();
      if (parent_state == INIT || parent_state == KONT) {
        parent_state = (e.x() == evts[j-1].x()) ? KONT : DISKONT;
      }
    }
    if (e.otvaram) {
      S.push(INIT);
    } else {
      assert(S.size());
      sol += (S.top() == KONT);
      S.pop();
    }
  }
  return sol + N + 1;
}

int main() {
  load();
  printf("%d\n", solve());
  return 0;
}
