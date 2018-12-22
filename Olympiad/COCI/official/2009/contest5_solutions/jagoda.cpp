#include <cmath>
#include <iostream>
using namespace std;

#define MAXN 100000

int box[MAXN], cup[MAXN];

int main() {
   cin.sync_with_stdio(0);

   int N, M;
   cin >> N >> M;

   int K = (int)sqrt(N);
   while ( M-- > 0 ) {
      int B, A;
      cin >> B >> A;
      --A; B += A;

      int ans = 0;
      while ( A < B && A%K != 0 ) ans += ++box[A++];
      if ( B != N ) {
         while ( A < B && B%K != 0 ) ans += ++box[--B];
      }
      while ( A < B ) ans += ++cup[A/K], A += K;
      cout << ans << endl;
   }

   return 0;
}
