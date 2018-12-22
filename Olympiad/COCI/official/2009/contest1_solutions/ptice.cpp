#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
   int len;
   string s;
   cin >> len >> s;

   int skor[3] = {0};
   for ( int i=0; i<len; ++i ) {
      skor[0] += s[i] == "ABC"[i%3];
      skor[1] += s[i] == "BABC"[i%4];
      skor[2] += s[i] == "CCAABB"[i%6];
   }
   
   int naj = max(skor[0], max(skor[1], skor[2]));
   cout << naj << endl;
   if ( skor[0] == naj ) cout << "Adrian" << endl;
   if ( skor[1] == naj ) cout << "Bruno" << endl;
   if ( skor[2] == naj ) cout << "Goran" << endl;
   
   return 0;
}
