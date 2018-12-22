#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

typedef long long llint;

#define MAXT 1000001

int n, m;
bool upit[MAXT];
llint dodaj[MAXT];
int koliko2[MAXT], koliko4[MAXT];
int x1, y1, x2, y2;

inline llint presjek_kvadrata_s_pravokutnikom( int t ) {
   llint x = min( t, x2 ) - max( -t, x1 ) + 1;
   llint y = min( t, y2 ) - max( -t, y1 ) + 1;
   return (x<=0 || y<=0) ? 0 : x * y;
}

inline void obradi( int t1, int t2 ) {
   llint p0 = presjek_kvadrata_s_pravokutnikom( t1-1 );
   llint p1 = presjek_kvadrata_s_pravokutnikom( t1 );
   llint p2 = presjek_kvadrata_s_pravokutnikom( t1+1 );
   dodaj[t1] += p1-p0;
   dodaj[t2] -= p1-p0;
   if( t2-t1 > 1 ) {
      dodaj[t2] -= (p2-2*p1+p0)*(t2-t1);
      if( p2-2*p1+p0 == 2 ) ++koliko2[t1], --koliko2[t2];
      if( p2-2*p1+p0 == 4 ) ++koliko4[t1], --koliko4[t2];
   }
}

int main( void ) {
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ) {
      scanf( "%d%d%d%d", &x1, &y1, &x2, &y2 );
      vector<int> t;
      for( int d = -1; d <= 1; ++d ) {
         t.push_back( abs(x1+d) );
         t.push_back( abs(y1+d) );
         t.push_back( abs(x2+d) );
         t.push_back( abs(y2+d) );
      }
      sort( t.begin(), t.end() ); 
      
      for( int i = 1; i < t.size(); ++i ) obradi( t[i-1], t[i] );
   }
   scanf( "%d", &m );
   for( int i = 0; i < m; ++i ) {
      int t; scanf( "%d", &t );
      upit[t] = 1;
   }
   
   llint ret = 0, add = 0;
   llint k2 = 0, k4 = 0;
   for( int t = 1; t <= MAXT; ++t ) {
      ret += add += dodaj[t];
      add += 2*(k2+=koliko2[t]) + 4*(k4+=koliko4[t]);
      if( upit[t] ) cout << ret << endl;
   }

   return 0;
}
