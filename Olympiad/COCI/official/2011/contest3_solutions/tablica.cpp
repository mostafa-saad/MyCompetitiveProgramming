#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

bool equals( double a, double b ){
  if( fabs(a-b) < 0.0001 ) return 1;
  return 0;
}

int main(){
  double a, b, c, d;
  scanf( "%lf %lf %lf %lf", &a, &b, &c, &d );

  double v1 = a/c + b/d;
  double v2 = c/d + a/b;
  double v3 = d/b + c/a;
  double v4 = b/a + d/c;

  double mx = max(max(v1,v2),max(v3,v4));
  if( equals(mx, v1) ) printf( "0\n" );
  else if( equals(mx,v2) ) printf( "1\n" );
  else if( equals(mx,v3) ) printf( "2\n" );
  else printf( "3\n" );

  return 0;
}
