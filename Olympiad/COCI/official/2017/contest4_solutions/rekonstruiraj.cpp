#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long llint;
typedef pair <int, int> pii;

const int MAXN = 55;

int n;
llint a, b;

vector<llint> getDivisors (llint x) {
  vector <llint> ret;
  for (llint i = 1; i*i <= x; ++i)
    if (x % i == 0) ret.push_back(i), ret.push_back(x / i);
  sort(ret.begin(), ret.end());
  ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
  return ret;
}

bool test(llint x, vector <llint> &V) {
  llint first;
  if (a % x != 0) first = a - a%x + x;
  else first = a;
  while (first <= b) {
    if (!binary_search(V.begin(), V.end(), first))
      return 0;
    first += x;
  }
  return 1;
}

bool uzeo[MAXN];
int interpret (char *s) {
  while (strlen(s) != 5)
    s[strlen(s)] = '0';
  int ret = 0;
  for (int i = 0; i < 5; ++i)
    ret = ret * 10 + s[i] - '0';
  return ret;
}

int main (void){
  scanf("%d", &n);
  scanf("%lld%lld", &a, &b);
  a *= 100000;
  b *= 100000;
  vector <llint> V;
  for (int i = 0; i < n; ++i) {
    int x;
    char y[10] = {0};
    int cnt = scanf("%d.%s\n", &x, y);
    if (cnt == 1) y[0] = 0;
    llint broj = (llint)x * 100000 + interpret(y);
    V.push_back(broj);
  }
  sort(V.begin(), V.end());
  vector <llint> ans;
  for (int i = 0; i < n; ++i) {
    auto divisors = getDivisors(V[i]);
    if (uzeo[i] == 1) continue;
    for (auto x: divisors)
      if (test(x, V)) {
	for (int j = i; j < n; ++j)
	  if (V[j] % x == 0) uzeo[j] = 1;
	ans.push_back(x);
	break;
      }
  }
  for (auto x: ans)
    printf("%lld.%05lld\n", x / 100000, x % 100000);
  
  return 0;
}
