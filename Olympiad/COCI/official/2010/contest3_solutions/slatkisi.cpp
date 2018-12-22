#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#define MAX 9

using namespace std;

string round(const string &s, int p) {
  string ret = s; bool flag = false;
  if( p == MAX ) 
    return ret;
  if( s[p] >= '5' ) {
    for( int i = p-1; i >= 0; --i ) {
      if( s[i] != '9' ) {
        ++ret[i];
        break;
      }
      else {
        ret[i] = '0';
        if( i == 0 ) 
          flag = true;
      }
    }
    flag |= (p == 0);
  }
  for( int i = p; i < MAX; ++i ) 
    ret[i] = '0';
  if( flag ) 
    ret = "1" + ret;
  return ret;
}

int main() {
  string s; int k;
  cin >> s >> k;
  s = string(9-s.size(), '0') + s;
  cout << atoi(round(s, 9-k).c_str()) << endl;
  return 0;
}
