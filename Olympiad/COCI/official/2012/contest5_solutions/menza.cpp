#include <iostream>
using namespace std;

int main() {
  long long P, K, L;
  cin >> P >> K >> L;

  long long placeno = K*10000 + L*100;
  long long cijena = 100 * placeno / P + 50;

  cout << cijena/10000 << ' ' << (cijena/100)%100 << endl;
  return 0;
}

