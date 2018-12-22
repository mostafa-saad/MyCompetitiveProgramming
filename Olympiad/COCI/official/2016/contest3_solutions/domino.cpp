#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 2005;
const int MAXK = 9;
typedef pair <int, int> pii;
typedef long long llint;

int n, k;
int mat[MAXN][MAXN];

struct Field {
  pii pos;
  bool dir;
  int sum;

  Field (pii pos = pii(0, 0), bool dir = 0) : pos(pos), dir(dir) {
    int x, y;
    tie(x, y) = pos;
    sum = mat[x][y] + mat[x + dir][y + (1 - dir)];
  }

  vector <pii> get_fields () const {
    int x, y;
    tie(x, y) = pos;
    vector <pii> ret;
    ret.push_back(pii(x, y));
    ret.push_back(pii(x + dir, y + (1 - dir)));
    return ret;
  }


  bool intersect (const Field &B) const {
    auto Af = get_fields();
    auto Bf = B.get_fields();
    for (auto a: Af)
      for (auto b: Bf)
	if (a == b) return true;
    return false;
  }
};

bool cmp (const Field &A, const Field &B) {
  return A.sum > B.sum;
}

short val[MAXN];
llint mask[MAXN];

short best_left[1 << 20][MAXK];

void solve_left (int pos, int sz, int cmask, llint blocked, short sum, int cnt) {
  if (cnt > k) return;
  if (pos == sz) {
    best_left[cmask][cnt] = sum;
    return;
  }
  solve_left(pos+1, sz, cmask, blocked, sum, cnt);
  if (!(blocked & (1LL << pos)))
    solve_left(pos+1, sz, cmask | (1LL << pos), blocked | mask[pos], sum + val[pos], cnt + 1);
}


int solve_right (int pos, int sz, int szl, llint blocked, short sum, int cnt) {
  if (cnt > k) return 0;
  if (pos == sz){
    return sum + best_left[(~blocked) & ((1 << szl) - 1)][k - cnt];
  }

  int ret = solve_right(pos+1, sz, szl, blocked, sum, cnt);
  if (!(blocked & (1LL << pos)))
    ret = max(ret, solve_right(pos+1, sz, szl, blocked | mask[pos], sum + val[pos], cnt + 1));
  return ret;
}

int solve (int sz) {
 int lsz = sz / 2;
  while (lsz > 20) --lsz;

  solve_left(0, lsz, 0, 0, 0, 0);
  for (int i = 0; i < (1 << lsz); ++i) {
    int pos = i;
    while (pos > 0) {
      int bit = pos&-pos;
      for (int j = 0; j <= k; ++j)
	best_left[i][j] = max(best_left[i][j], best_left[i - bit][j]);
      pos -= bit;
    }
  }
  return solve_right(lsz, sz, lsz, 0, 0, 0);
}

int main (void){
  scanf("%d%d", &n, &k);
  vector <Field> V;
  V.reserve(n*n*2);
  long long sum = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", &mat[i][j]);
      sum += mat[i][j];
    }

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      V.push_back(Field(pii(i, j), 0));
      V.push_back(Field(pii(i, j), 1));
    }

  int sz = min((int)V.size(), (k - 1)*7 + 1);
  nth_element(V.begin(), V.begin() + sz, V.end(), cmp);

  for (int i = 0; i < sz; ++i)
    val[i] = V[i].sum;

  for (int i = 0; i < sz; ++i)
    for (int j = 0; j < sz; ++j)
      if (V[i].intersect(V[j])) mask[i] |= (1LL << j);

  printf("%lld\n", sum - solve(sz));
  return 0;
}

