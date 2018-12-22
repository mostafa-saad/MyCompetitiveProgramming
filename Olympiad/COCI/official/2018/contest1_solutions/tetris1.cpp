#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

#define fst first
#define snd second

typedef long long llint;
typedef pair<int, int> pii;

const int B = 27397, MOD = 1e9 + 7;
const int B1 = 33941, MOD1 = 1e9 + 9;

int r, s;

vector<string> shape1{"11",
                      "11"};

vector<string> shape2{"1111"};

vector<string> shape3{"011",
                      "110"};

vector<string> shape4{"110",
                      "011"};

vector<string> shape5{"010",
                      "111"};

const vector<vector<string>> shapes = {shape1, shape2, shape3, shape4, shape5};
const vector<int> rot = {1, 2, 2, 2, 4};

char grid[11][11];

vector<string> rotate(vector<string> mat) {
  int r = mat.size(), s = mat[0].size();
  vector<string> ret;

  ret.resize(s);
  for (int i = 0; i < ret.size(); ++i)
    ret[i].resize(r);

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      ret[j][r - 1 - i] = mat[i][j];

  return ret;
}

int get_count(vector<string> shape) {
  int rr = shape.size(), ss = shape[0].size();
  int ret = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      if (i + rr > r || j + ss > s) continue;
      set <char> S;
      for (int _r = i; _r < i + rr; ++_r)
        for (int _s = j; _s < j + ss; ++_s)
          if (shape[_r - i][_s - j] == '1')
            S.insert(grid[_r][_s]);
      ret += (S.size() == 1 && *S.begin() != '.');
    }
  }
  return ret;
}

int main(void) {
  scanf("%d%d", &r, &s);
  for (int i = 0; i < r; ++i)
    scanf("%s", grid[i]);

  for (int i = 0; i < (int) shapes.size(); ++i) {
    auto shape = shapes[i];
    int sol = 0;
    for (int j = 0; j < rot[i]; ++j) {
      sol += get_count(shape);
      shape = rotate(shape);
    }
    printf("%d\n", sol);
  }

  return 0;
}
