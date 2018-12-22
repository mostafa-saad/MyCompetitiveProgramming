#include <cstdio>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long llint;
typedef pair <int, int> pii;

const int MAXN = 505;
const int MAXLOG = 31;
const int MAXK = 2;

int n, m, k;
char str[MAXN][MAXN];
int base_pow2[MAXK][MAXLOG];

const int bases[MAXK] = {3137, 51518};
const int modulo[MAXK] = {(int)((1e9) + 7), 999999937};

struct hashed_string {
  int hashes[MAXK];
  hashed_string() {
    memset(hashes, 0, sizeof hashes);
  }
  void append(const hashed_string &a, int pow2len) {
    for (int i = 0; i < MAXK; ++i) {
      hashes[i] = ((llint)hashes[i] * base_pow2[i][pow2len]) % modulo[i] + a.hashes[i];
      if (hashes[i] >= modulo[i]) hashes[i] -= modulo[i];
    }
  }
};

bool operator < (const hashed_string &a, const hashed_string &b) {
  for (int i = 0; i < 2; ++i)
    if (a.hashes[i] != b.hashes[i]) return a.hashes[i] < b.hashes[i];
  return 0;
}

map <hashed_string, int> M;

hashed_string field[MAXLOG][MAXN][MAXN];

void generate(int dx, int dy) {
  for (int i = 0; i < MAXK; ++i)
    base_pow2[i][0] = bases[i];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      for (int k = 0; k < MAXK; ++k)
	field[0][i][j].hashes[k] = str[i][j] % modulo[k];

  int len = 1;
  for (int log = 1; log < MAXLOG; ++log) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
	field[log][i][j] = field[log-1][i][j];
	field[log][i][j].append(field[log-1][((i + dx * len)%n + n)%n][((j + dy * len)%m + m)%m], log - 1);
      }
    for (int i = 0; i < MAXK; ++i)
      base_pow2[i][log] = (base_pow2[i][log-1] * (llint)base_pow2[i][log-1]) % modulo[i];
    len *= 2;
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      int len = k;
      hashed_string res;
      int cx, cy; cx = i; cy = j;
      for (int k = MAXLOG-1; k >= 0; --k) {
	if ((1 << k) <= len) {
	  len -= (1 << k);
	  res.append(field[k][cx][cy], k);
	  cx = ((cx + dx * (1 << k)) % n + n)%n;
	  cy = ((cy + dy * (1 << k)) % m + m)%m;
	}
      }
      M[res] += 1;
    }
}

int main (void){
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i)
    scanf("%s", str[i]);
  for (int dx = -1; dx <= 1; ++dx)
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) continue;
      generate(dx, dy);
    }

  llint brojnik, nazivnik;
  brojnik = 0; nazivnik = (llint)(n * m * 8) * (n * m * 8);
  for (auto it: M) 
    brojnik += it.second * (llint)it.second;
  llint g = __gcd(brojnik, nazivnik);
  brojnik /= g; nazivnik /= g;
  printf("%lld/%lld\n", brojnik, nazivnik);
  return 0;
}
