#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

struct bigint {
   vector<int> digits;
   
   bigint( int x ) {
      digits.push_back( x );
   }
   
   void output() {
      int n = digits.size();
      printf( "%d", digits[--n] );
      while( n > 0 ) printf( "%09d", digits[--n] );
      printf( "\n" );
   }

   void operator += (const bigint &b ) {
      int carry = 0;
      for( int i = 0; i < digits.size() || i < b.digits.size() || carry; ++i ) {
         int x = carry;
         if( i < digits.size() ) x += digits[i];
         if( i < b.digits.size() ) x += b.digits[i];
         carry = x >= 1000000000;
         if( carry ) x -= 1000000000;
         
         if( i < digits.size() ) digits[i] = x;
         else digits.push_back( x );
      }
   }
};

#define MAX 10000
char S[MAX];

int main( void ) {
   gets( S );

   bigint currA( 1 ), currB( 0 );
   for( int i = strlen( S )-1; i >= 0; --i ) {
      bigint nextA( 0 ), nextB( 0 );
      
      if( S[i] == '*' || S[i] == 'P' ) { 
         nextA += currA;
         nextB += currB;
      }

      if( S[i] == '*' || S[i] == 'L' ) { 
         nextA += currA;
         nextA += currA;
         nextB += currB;
      }

      if( S[i] == '*' || S[i] == 'R' ) { 
         nextA += currA;
         nextA += currA;
         nextB += currA;
         nextB += currB;
      }

      currA = nextA; currB = nextB;
   }

   currA += currB;
   currA.output();

   return 0;
}
