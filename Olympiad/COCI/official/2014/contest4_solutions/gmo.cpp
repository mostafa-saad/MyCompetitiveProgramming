#include <iostream>
#include <string>
using namespace std;

int main () {
  string a, b;
  cin >> a >> b;
  int c[500];
  cin >> c['A'];
  cin >> c['C'];
  cin >> c['G'];
  cin >> c['T'];
  int sol = 2000000000;
  a += "X";
  for (int i = 0; i < a.size(); ++i) {
    int tmp = 0;
    int j = i, k = 0;
    while (k < b.size()) {
      if (a[j] == b[k]) ++j;
      else tmp += c[b[k]];
      k++;
    }
    if (sol > tmp) sol = tmp;
  }
  cout << sol << endl;
}
