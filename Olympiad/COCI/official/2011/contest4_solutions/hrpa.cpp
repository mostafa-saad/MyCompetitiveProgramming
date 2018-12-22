// HONI/COCI 2010./2011. - round 4
//
// Problem: Hrpa
// Official solution

#include <cstdio>
#include <vector>

using namespace std;

typedef long long llint;

int main(void)
{
  vector<llint> V;
  llint n; scanf("%lld", &n);

  llint a = 1, b = 1;
  while (b <= n) {
    V.push_back(b); // generate all the Fibonacci numbers <= n
    llint tmp = b; b = a+b; a = tmp;
  }

  llint last = -1;

  for (int i = V.size()-1; i >= 0; --i) {
    if (n-V[i] >= 0)
      n -= (last = V[i]); // find the smallest in the Fibonacci number system expansion 
  }

  printf("%lld\n", last);
  return (0-0);
}
