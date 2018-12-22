#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

int main() {
   int n; scanf("%d", &n);

   map<int, int> depth;
   long long zbr = 0;
   for ( int i=0; i<n; ++i ) {
      int X; scanf("%d", &X);
      int d = 0;
      map<int, int>::iterator it = depth.lower_bound(X);
      if ( it != depth.end()   ) d = max(d, it->second+1);
      if ( it != depth.begin() ) d = max(d, (--it)->second+1);
      depth[X] = d;
      zbr += d;
      printf("%lld\n", zbr);
   }
   
   return 0;
}
