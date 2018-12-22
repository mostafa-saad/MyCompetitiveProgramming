#include <cstdio>
using namespace std;

int main() {
   int max_score = 0, winner = 0;
   for ( int i=1; i<=5; ++i ) {
      int sum = 0;
      for ( int j=0; j<4; ++j ) {
         int x;
         scanf("%d", &x);
         sum += x;
      }
      if ( sum > max_score ) {
         max_score = sum;
         winner = i;
      }
   }
   printf("%d %d\n", winner, max_score);

   return 0;
}
