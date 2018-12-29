/*
  Croatian Olympiad in Informatics 2007
  Task PATRIK
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

typedef long long llint;
typedef pair<int,int> par;

stack<par> S;

int main( void ) {
   int n;
   scanf( "%d", &n );

   llint ret = 0;
   for( int i = 0; i < n; ++i ) {
      int h;
      scanf( "%d", &h );
      
      par p( h, 1 );
      for( ; !S.empty() && S.top().first <= h; S.pop() ) {
         ret += S.top().second;
         if( S.top().first == h ) p.second += S.top().second;
      }

      if( !S.empty() ) ++ret;
      S.push( p );
   }
   
   cout << ret << endl;

   return 0;
}
