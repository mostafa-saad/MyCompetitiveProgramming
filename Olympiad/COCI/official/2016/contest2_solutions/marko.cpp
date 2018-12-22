#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int n;
vector <string> V;

int dig[] = {0, 3, 3, 3, 3, 3, 4, 3, 4};

char set_digit (char x) {
  int digpos = 0;
  int pos = x - 'a' + 1;
  while (pos > 0) 
    pos -= dig[digpos++];

  return '0' + digpos;
}

int main (void){
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string str;
    cin >> str;
    for (auto &x: str) 
      x = set_digit(x);
    V.push_back(str);
  }

  string s;
  cin >> s;
  int ans = 0;
  for (auto x: V)
    ans += s == x;
  printf("%d\n", ans);
  return 0;
}
