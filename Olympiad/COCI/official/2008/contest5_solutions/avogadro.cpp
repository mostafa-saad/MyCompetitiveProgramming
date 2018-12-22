#include <cstdio>
#include <stack>
#include <vector>

#define MAX 100000

using namespace std;

int n;
int a[3][MAX];
int erased[MAX];

vector<int> columns[MAX];
int freq[MAX][3];

stack<int> jobs;

int main( void ) {
   scanf( "%d", &n );
   for( int r = 0; r < 3; ++r ) 
      for( int c = 0; c < n; ++c ) {
         scanf( "%d", &a[r][c] ); --a[r][c];

         columns[a[r][c]].push_back( c );
         ++freq[a[r][c]][r];
      }

   for( int i = 0; i < n; ++i ) 
      if( freq[i][1] == 0 || freq[i][2] == 0 ) 
         jobs.push( i );      

   int ret = 0;
   while( !jobs.empty() ) {
      int number = jobs.top();
      jobs.pop();

      for( vector<int>::iterator it = columns[number].begin(); it != columns[number].end(); ++it ) {
         if( erased[*it] ) continue;
         erased[*it] = 1;
         ++ret;

         if( --freq[a[0][*it]][0] == 0 ) jobs.push( a[0][*it] );
         if( --freq[a[1][*it]][1] == 0 ) jobs.push( a[1][*it] );
         if( --freq[a[2][*it]][2] == 0 ) jobs.push( a[2][*it] );
      }
   }

   printf( "%d\n", ret );

   return 0;
}
