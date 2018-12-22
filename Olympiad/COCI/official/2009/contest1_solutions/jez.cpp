#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

const int LOG_MAXN = 20;

int R, S; long long K;
int nd, visak;

int prebroji(int x, int ymax) {
   int rez = 0;
   for ( int k=LOG_MAXN; k>=0; --k ) {
      if ( (ymax&(1<<k)) != 0 ) {
         // jed = broj jedinica koje x ima na pozicijama 0..k-1
         int jed = __builtin_popcount(x&((1<<k)-1));
         rez += 1<<(k-jed);

         // ako x ima jedinicu na poziciji k, svi brojevi izmedu 2^k i
         // ymax imaju neki zajednicki bit, pa smo gotovi
         if ( (x&(1<<k)) != 0 ) break;
      }
   }
   return rez;
}

int jedanred(int r) {
   int smax = nd-r;
   if ( nd%2 == 0 ) {
      int sr = nd - max(0, nd-R+1);
      smax += sr-r >= 0 && sr-r < visak;
   } else {
      int sr = max(0, nd-S+1);
      smax += r-sr >= 0 && r-sr < visak;
   }
   smax = max(smax, 0);
   smax = min(smax, S);
   return prebroji(r, smax);
}

void dodaj(long long &ukupno, int x) {
   ukupno += x;
   if ( ukupno > K ) throw 1;
   ++nd;
   visak = K - ukupno;
}

int main() {
   cin >> R >> S >> K;

   try {
      int najdulja = min(R, S);
      long long ukupno = 0;
      nd = 0;
      for ( int i=1; i<=najdulja; ++i ) dodaj(ukupno, i);
      for ( int i=0; i<R+S-2*najdulja; ++i ) dodaj(ukupno, najdulja);
      for ( int i=najdulja-1; i>0; --i ) dodaj(ukupno, i);
   } catch(...) { }

   long long rez = 0;
   for ( int r=0; r<R; ++r )
      rez += jedanred(r);
   cout << rez << endl;

   return 0;
}
