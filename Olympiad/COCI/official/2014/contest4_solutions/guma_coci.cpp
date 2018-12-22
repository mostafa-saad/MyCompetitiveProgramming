#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

const int V = 100001;
bool bio[V];
int euler[V];

int gcd(int a, int b) { return (b == 0? a : gcd(b, a % b)); }

int main () {
  euler[1] = 1;
  for (int i = 2; i < V; ++i) {
    euler[i] = i - 1;
    int korijen = (int)sqrt(i);
    for (int p = 2; p <= korijen; ++p) {
      int m = i;
      while (m % p == 0) m /= p;
      if (m == i) continue;
      euler[i] = (m == 1? i - i/p : euler[m] * euler[i / m]);
      break;
    }
  }
  int n;
  scanf("%d", &n);
  ++n;
  long long sol = 0;
  bio[1] = true;
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    int korijen = (int)sqrt(t);
    vector<int> djelitelji;
    for (int d = 1; d <= korijen; ++d)
      if (t % d == 0) {
        djelitelji.push_back(d);
        if (d * d != t) djelitelji.push_back(t / d);
      }
    for (vector<int>::iterator d = djelitelji.begin(); d != djelitelji.end(); ++d)
      if (!bio[*d]) {
        sol += euler[*d];
        bio[*d] = true;
      }
  }
  printf("%lld\n", sol);
}
