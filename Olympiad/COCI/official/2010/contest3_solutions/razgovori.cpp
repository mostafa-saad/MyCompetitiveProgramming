/*
  Zadatak: razgovori
  Autor rjesenja: Leo Osvald
*/

#include <cstdio>
#include <algorithm>
#define MAX 100001

int n;
std::pair<int, int> a[MAX];

int main() {
  scanf("%d%*d", &n);
  for( int i = 0; i < n; ++i ) 
    scanf("%d%d", &a[i].first, &a[i].second);

  std::sort(a, a+n);

  a[n] = std::make_pair(0, 0);

  long long ret = 0;
  for( int i = 1; i <= n; ++i ) 
    if( a[i-1].second > a[i].second ) 
      ret += a[i-1].second - a[i].second;

  printf("%lld\n", ret);

  return 0;
}
