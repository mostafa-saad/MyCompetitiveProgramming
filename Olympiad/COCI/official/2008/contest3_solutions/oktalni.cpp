#include <iostream>
#include <string>

using namespace std;

int main() {
   string s;
   cin >> s;

   while( s.length() % 3 != 0 ) s = "0" + s;

   while( s != "" ) {
      int x = 0;
      if( s[0] == '1' ) x += 4;
      if( s[1] == '1' ) x += 2;
      if( s[2] == '1' ) x += 1;
      printf( "%d", x );

      s = s.substr( 3 );
   }
   printf( "\n" );

   return 0;
}
