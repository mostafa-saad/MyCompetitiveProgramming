
#include <iostream>
using namespace std;

int main () {
  int n; cin >> n;
  int m; cin >> m;
  int broj_poklapanja = 0;
  for (int i = 1; i < m; ++i)
    broj_poklapanja += (i * n % m == 0);
  cout << m - 1 - broj_poklapanja << endl;
  return 0;
}
