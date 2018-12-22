#include <algorithm>
#include <iostream>

using namespace std;

int a[4];

int main(void) {
   for( int i = 0; i < 4; ++i ) cin >> a[i];
   sort( a, a+4 );
   cout << a[0] * a[2] << endl;
   return 0;
}
