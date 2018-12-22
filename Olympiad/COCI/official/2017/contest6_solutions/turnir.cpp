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

const int MAXN = 20;
int n;
int a[1 << MAXN];

int calc (int x) {
  if (x == 0) return 0;
  for (int i = n-1; i >= 0; --i) {
    if ((1 << i) < x) x -= (1 << i);
    else return n - i;
  }
  return n;
}

int main (void){
  scanf("%d", &n);
  vector <int> V;
  for (int i = 0; i < (1 << n); ++i) {
    scanf("%d", &a[i]);
    V.push_back(a[i]);
  }
  sort(V.begin(), V.end());
  for (int i = 0; i < (1 << n); ++i) {
    printf("%d ", calc(V.end() - upper_bound(V.begin(), V.end(), a[i])));
  }

  return 0;
}
