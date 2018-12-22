#include <iostream>
using namespace std;

int main () {
  int n, o;
  cin >> n >> o;
  int uzela_max = o / (n - 1);
  int uzela_min = uzela_max;
  if (uzela_max * (n - 1) == o)
    --uzela_min;
  cout << o + uzela_min << " " << o + uzela_max << endl;
  return 0;
}
