#include <iostream>
#include <string>
using namespace std;

int main()
{
  string A, B;
  cin >> A >> B;
  int n = A.size();
  int m = B.size();

  int prvo_A = 0, prvo_B = 0;
  bool pronasao = false;
  for (int i = 0; i < n && !pronasao; ++i) {
    for (int j = 0; j < m && !pronasao; ++j)  {
      if (A[i] == B[j]) {
        prvo_A = i;
        prvo_B = j;
        pronasao = true;
      }
    }
  }

  string pocetak = string(prvo_A, '.');
  string kraj = string(n - prvo_A - 1, '.');

  for (int i = 0; i < prvo_B; ++i) {
    cout << pocetak << B[i] << kraj << endl;
  }
  cout << A << endl;
  for (int i = prvo_B+1; i < m; ++i) {
    cout << pocetak << B[i] << kraj << endl;
  }

  return 0;
}

