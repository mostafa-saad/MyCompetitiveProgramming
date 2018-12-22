#include <iostream>

using namespace std;

int main(void) {
  long long s = 0;
  int n;
  cin >> n;
  for (int k = 0; k < n; ++k) {
    long long b;
    cin >> b;
    int a = (k + 1) * b - s;
    cout << (k > 0 ? " " : "") << a;
    s += a;
  }
  cout << "\n";
  return 0;
}
