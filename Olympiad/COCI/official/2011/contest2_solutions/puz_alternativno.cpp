#include <cstdio>
#include <algorithm>

using namespace std;

int main( void ) {
  int a, b, v;
  scanf( "%d %d %d", &a, &b, &v );

  int lo = 1, hi = v;
  while( lo < hi ) {
    long long mid = ( lo+hi ) / 2;
    if( mid*a - (mid-1)*b >= v ) hi = mid;
    else lo = mid+1;
  }
  printf( "%d\n", lo );

  return 0;
}

