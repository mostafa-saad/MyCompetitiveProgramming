#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 20

int N, H;
int nfriends[MAXN], friendmask[MAXN];

int when[1<<MAXN]; long long thrown[1<<MAXN];

int main() {
   cin >> N >> H;
   for ( int i=0; i<N; ++i ) {
      string row;
      cin >> row;
      for ( int j=0; j<N; ++j ) {
         if ( row[j] == '1' ) {
            ++nfriends[i];
            friendmask[i] |= 1<<j;
         }
      }
   }

   fill(when, when+(1<<N), -1);

   int state = friendmask[0];
   when[state] = 1;
   thrown[state] = nfriends[0];

   long long total = thrown[state];

   for ( int t=2; t<=H; ++t ) {
      int next = 0, lastthrown = 0;
      for ( int i=0; i<N; ++i ) {
         if ( state&(1<<i) ) {
            next ^= friendmask[i];
            lastthrown += nfriends[i];
         } else {
            lastthrown += 2*nfriends[i];
         }
      }
      
      state = next;
      total += lastthrown;

      if ( when[state] == -1 ) {
         when[state] = t;
         thrown[state] = total;
      } else {
         int rep = (H-t) / (t-when[state]);
         t += rep * (t-when[state]);
         total += rep * (total-thrown[state]);
         fill(when, when+(1<<N), -1);
      }
   }
   cout << total << endl;
   return 0;
}
