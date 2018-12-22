#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main( void ) {
   string s;
   cin >> s;

   string ret = "~";

   for( int i = 1; i < s.size(); ++i ) {
      for( int j = i+1; j < s.size(); ++j ) {
         string a = s.substr( 0, i );
         string b = s.substr( i, j-i );
         string c = s.substr( j );

         reverse( a.begin(), a.end() );
         reverse( b.begin(), b.end() );
         reverse( c.begin(), c.end() );

         string t = a+b+c;

         if( t < ret ) ret = t;
      }
   }

   cout << ret << endl;

   return 0;
}
