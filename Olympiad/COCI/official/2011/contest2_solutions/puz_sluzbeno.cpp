#include <cstdio>
#include <algorithm>

using namespace std;

int main( void ) {
  int a, b, v;
  scanf( "%d %d %d", &a, &b, &v );
  printf( "%d\n", (v-b-1)/(a-b)+1 );
  return 0;
}

