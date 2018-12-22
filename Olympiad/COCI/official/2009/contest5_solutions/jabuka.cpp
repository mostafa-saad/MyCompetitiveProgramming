#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
   int R, G;
   cin >> R >> G;

   for ( int i=1; i*i<=R; ++i ) {
      if ( R%i == 0 ) {
         if ( G%i == 0 )
            cout << i << ' ' << R/i << ' ' << G/i << endl;

         if ( i*i != R && G%(R/i) == 0 ) {
            cout << R/i << ' ' << i << ' ' << G/(R/i) << endl;
         }
      }
   }
   return 0;
}
