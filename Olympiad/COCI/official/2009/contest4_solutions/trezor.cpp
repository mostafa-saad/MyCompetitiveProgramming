#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long llint;

#define MAX 4000

int gcd( int a, int b ) { return b == 0 ? a : gcd( b, a%b ); }

int A, B, L;
vector<int> rastav[MAX+1];

vector<int> umnozak( vector<int> a, vector<int> b ) {
   vector<int> ret;
   for( vector<int>::iterator it = a.begin(); it != a.end(); ++it ) 
      for( vector<int>::iterator jt = b.begin(); jt != b.end(); ++jt ) 
         if( *it == *jt )
            ret.push_back( *it );
         else
            ret.push_back( *it * *jt );
   
   sort( ret.begin(), ret.end() ); 
   ret.erase( unique( ret.begin(), ret.end() ), ret.end() );
   
   return ret;
}

llint ne_vidi( vector<int> a ) {
   llint ret = 0;
   int n = a.size();
   for( int mask = 1; mask < (1<<n); ++mask ) {
      int x = 1;
      int bits = 0;
      for( int i = 0; i < n; ++i ) 
         if( (mask>>i) & 1 ) {
            x = x / gcd( x, a[i] ) * a[i];
            ++bits;
         }

      if( bits & 1 ) ret += L / x;
      else ret -= L / x;
   }
   return ret;
}

int main( void ) {
   scanf( "%d%d%d", &A, &B, &L );
   
   for( int i = 1; i <= MAX; ++i ) {
      int x = i;
      for( int d = 2; d*d <= x; ++d ) {
         if( x%d == 0 ) {
            while( x%d == 0 ) x /= d;
            rastav[i].push_back( d );
         }
      }
      if( x > 1 ) rastav[i].push_back( x );
   }

   llint vidi[3] = { 0LL, 0LL, 0LL };

   for( int dx = 0; dx <= (A+B)/2; ++dx ) {
      llint nevidi1 = dx == 0 ? L-1 : ne_vidi( rastav[dx] );
      llint nevidi2 = ne_vidi( rastav[(A+B)-dx] );
      llint nevidi12 = dx == 0 ? nevidi2 : ne_vidi( umnozak( rastav[dx], rastav[(A+B)-dx] ) );

      int koliko = (2*dx == (A+B)) ? 1 : 2;

      vidi[0] += koliko*nevidi12;
      vidi[1] += koliko*(nevidi1 + nevidi2 - 2*nevidi12);
      vidi[2] += koliko*(L - nevidi1 - nevidi2 + nevidi12);
   }

   for( int i = 0; i < 3; ++i ) printf( "%lld\n", vidi[i] );

   return 0;
}
