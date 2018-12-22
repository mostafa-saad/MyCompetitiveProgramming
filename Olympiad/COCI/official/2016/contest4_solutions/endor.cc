#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define pos first
#define col second
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

using namespace std;
using kameleon = pair<int, int>;

const int MAXN = 100010;
const int MAXK = 55;

int n, k, l;
vector<double> dp[2][MAXK];
int last_color[2][MAXK];
vector<double> emp, sol;

vector<kameleon> L, R, tL, tR;

inline void add(vector<double>& a, vector<double>& b) {
  for (int i = 0; i < k; ++i)
    a[i] += b[i];
}

inline void add(vector<double>& values, int color, double to_add) {
  values[color] += to_add;
}

kameleon kam[MAXN];
char dir[MAXN];

void calculateDP(void) {
  int i = 0;
  for (; i < n && dir[i] == 'L'; ++i) {
    add(sol, kam[i].col, kam[i].pos);
  }

  int first_right = i++, w = 0;
  for (int col_left = 0; col_left < k; ++col_left) {
    dp[w][col_left] = emp;
    last_color[w][col_left]
      = (col_left + kam[first_right].col) % k;
  }

  int prev_right = first_right;
  for (; i < n; ++i)
    if (dir[i] == 'L') {
      add(sol, dp[w][kam[i].col]);
      add(sol, kam[i].col, (kam[i].pos - kam[prev_right].pos)/2.0);
      add(sol, last_color[w][kam[i].col],
      	  (kam[i].pos + kam[first_right].pos) / 2.0);
    } else {
      w ^= 1;
      for (int col_left = 0; col_left < k; ++col_left) {
	int new_col = (kam[i].col + col_left) % k;
	dp[w][col_left] = dp[w ^ 1][new_col];
	last_color[w][col_left] = last_color[w ^ 1][new_col];
	add(dp[w][col_left], new_col,
	    (kam[i].pos - kam[prev_right].pos) / 2.0);
      }
      prev_right = i;
    }
}

void calculateDirection(void) {
  sort(L.begin(), L.end());
  sort(R.begin(), R.end());
  
  int a = 0, b = 0, j = 0;
  for (; a < (int)L.size() && b < (int)R.size(); ++j) {
    if (L[a].pos < R[b].pos) {
      kam[j] = L[a++];
      dir[j] = 'L';
    } else {
      kam[j] = R[b++];
      dir[j] = 'D';
    }
  }
  for (; a < (int)L.size(); ++a, ++j) {
    kam[j] = L[a];
    dir[j] = 'L';
  }
  for (; b < (int)R.size(); ++b, ++j) {
    kam[j] = R[b];
    dir[j] = 'D';
  }

  calculateDP();

  for (auto k : R)
    sol[k.col] += l - k.pos;
}

void init(void) {
  scanf("%d %d %d",&n,&k,&l);
  for (int i = 0; i < n; ++i) {
    int pos, col;
    char dir[10];
    scanf("%d %d %s",&pos,&col,dir);
    if (dir[0] == 'L')
      L.emplace_back(pos, col);
    else
      R.emplace_back(pos, col);
  }
  emp.resize(k);
  sol = emp;
}

void solve(void) {
  calculateDirection();

  for (int i = 0; i < k; ++i)
    printf("%.1lf\n",sol[i]);
}

int main(void) {
  init();
  solve();
  return 0;
}
