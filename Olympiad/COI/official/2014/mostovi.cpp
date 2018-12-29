#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

typedef long long llint;

typedef pair<int, int> most;
#define a first
#define b second

set<most> Sx; // mostovi u obliku {x, y}
set<most> Sy; // mostovi u obliku {y, x}
set<int> dead;
int n;

most getRightMost(int x, int y) {
  auto it = Sx.lower_bound({x, -1});
  if (it != Sx.end() && it->b >= y) return *it;
  it = Sy.lower_bound({y, -1});
  if (it != Sy.end() && it->b >= x) return {it->b, it->a};
  return {-1, -1};
}

most getLeftMost(int x, int y) {
  auto it = Sx.lower_bound({x+1, -1});
  if (it != Sx.begin()) { 
    --it;
    if (it->b <= y) return *it;
  }
  it = Sy.lower_bound({y+1, -1});
  if (it != Sy.begin()) { 
    --it;
    if (it->b <= x) return {it->b, it->a};
  }
  return {-1, -1};
}

bool check(int x, int y) {
  if (x == -1 || y == -1) return false;
  if (x == y) return true;

  // na istoj strani rijeke
  if (x < n && y < n) {
    if (x < y) {
      auto it = dead.lower_bound(x);
      return it == dead.end() || *it >= y;
    } else {
      most m = getRightMost(x, -1);
      return check(x, m.a) && check(m.b, y);
    }
  }

  if (x >= n && y >= n) {
    if (x > y) {
      auto it = dead.lower_bound(y);
      return it == dead.end() || *it >= x;
    } else {
      most m = getLeftMost(n, x);
      return check(x, m.b) && check(m.a, y);
    }
  }

  // na suprotnim stranama rijeke
  if (x < n) {
    most m = getRightMost(x, y);
    return check(x, m.a) && check(m.b, y);
  } else {
    most m = getLeftMost(y, x);
    return check(x, m.b) && check(m.a, y);
  }
  assert(false);
}

int main(void) {
  int m;
  scanf("%d %d", &n, &m);
  
  for (int i = 0; i < m; ++i) {
    char tip[5];
    int x, y;
    scanf("%s %d %d", tip, &x, &y); --x, --y;

    if (tip[0] == 'Q') {
      if (check(x, y)) puts("DA"); else
        puts("NE");
    }
    
    if (x > y) swap(x, y);
    if (tip[0] == 'B') dead.insert(x);
    if (tip[0] == 'A') Sx.insert({x, y}), Sy.insert({y, x});
  }
  return 0;
}
