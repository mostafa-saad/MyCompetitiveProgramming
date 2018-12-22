
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task PRASE
  Programming language C++
*/

#include <iostream>
#include <string>
using namespace std;

#define MAXN 100

int main()
{
   int n;
   static string red[MAXN];

   cin >> n;
   int ret = 0;
   for ( int i=0; i<n; ++i ) {
      cin >> red[i];

      int dosad = 0;
      for ( int j=0; j<i; ++j )
         dosad += red[i] == red[j];
      if ( dosad > i-dosad )
         ++ret;                 // prase!
   }

   printf( "%d\n", ret );

   return 0;
}
