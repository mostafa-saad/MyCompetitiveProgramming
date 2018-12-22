#include <cstdio>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1005;

int n, m, k;
int a[MAXN][MAXN];
int s[MAXN][MAXN];

typedef long long llint;

struct t{
  int cnt;
  int v, h;
  llint ms;
  t (int _cnt = 0, int _v = 0, int _h = 0, llint _ms = 0){
    cnt = _cnt;
    v = _v; h = _h;
    ms = _ms;
  }
};

llint ans;

int main (void){
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);

  for (int i = 0; i < n; ++i){

    stack < t > S;
    S.push(t(0, -1, 0, 0));

    for (int j = 0; j < m; ++j){
      s[i][j] = 1;
      if (i > 0 && a[i-1][j] == a[i][j]) s[i][j] += s[i-1][j];

      int sum = 1;
      while (S.top().v == a[i][j] && S.top().h >= s[i][j]){
	sum += S.top().cnt;
	S.pop();
      }

      llint my_s = sum * (llint)s[i][j];
      if (S.top().v == a[i][j]) my_s += S.top().ms;
      ans += my_s;
      S.push(t(sum, a[i][j], s[i][j], my_s));
    }

  }

  printf("%lld\n", ans);


  return 0;
}
