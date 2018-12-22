#include <iostream>
#include <vector>
using namespace std;

char ploca[9][10];

bool cross(int z) {
   bool bar_jednom = false;

   int red[9] = {0}, stupac[9] = {0}, blok[3][3] = {{0}};
   for ( int r=0; r<9; ++r ) {
      for ( int s=0; s<9; ++s ) {
         if ( ploca[r][s] == '0'+z ) {
            if ( red[r]++ > 0 ) throw 1;
            if ( stupac[s]++ > 0 ) throw 1;
            if ( blok[r/3][s/3]++ > 0 ) throw 1;
         }
      }
   }

   for ( int i=0; i<3; ++i ) {
      for ( int j=0; j<3; ++j ) {
         if ( blok[i][j] ) continue;

         vector<pair<int, int> > mog;
         for ( int r=0; r<3; ++r ) {
            for ( int s=0; s<3; ++s ) {
               if ( ploca[3*i+r][3*j+s] == '.' &&
                    !red[3*i+r] && !stupac[3*j+s] )
                  mog.push_back( make_pair(3*i+r, 3*j+s) );
            }
         }

         if ( mog.empty() ) throw 1;
         if ( mog.size() == 1 ) {
            int r = mog[0].first, s = mog[0].second;
            ploca[r][s] = '0'+z;
            red[r] = stupac[s] = blok[i][j] = 1;
            bar_jednom = true;
         }
      }
   }

   return bar_jednom;
}

int main() {
   for ( int i=0; i<9; ++i ) cin >> ploca[i];

   try {
      for ( ;; ) {
         bool gotovo = true;
         for ( int i=1; i<=9; ++i )
            gotovo &= !cross(i);
         if ( gotovo ) break;
      }
   } catch(...) {
      puts("ERROR");
      return 0;
   }

   for ( int i=0; i<9; ++i ) cout << ploca[i] << endl;

   return 0;
}
