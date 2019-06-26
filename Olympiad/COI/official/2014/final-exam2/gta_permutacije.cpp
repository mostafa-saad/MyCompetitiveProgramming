#include <iostream>
#include <string>
using namespace std;

int A[] = {1, 0, 3, 4, 5, 6, 7, 2}; 
int C[] = {2, 5, 6, 0, 7, 3, 1, 4}; 
int G[] = {7, 4, 5, 1, 6, 2, 0, 3}; 
int T[] = {4, 7, 1, 6, 2, 0, 3, 5}; 

class permutacija {
 public:
  permutacija() {
    for (int i = 0; i < 8; ++i)
      a[i] = i;
  }
  void primijeni(char z) {
    int* q;
    if (z == 'A') q = A;
    if (z == 'C') q = C;
    if (z == 'G') q = G;
    if (z == 'T') q = T;
    int b[8];
    for (int i = 0; i < 8; ++i)
      b[i] = q[a[i]];
    for (int i = 0; i < 8; ++i)
      a[i] = b[i];
  }
  int a[8];
};

int main () {
  int n;
  cin >> n;
  permutacija p[n];
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = s.size() - 1; j >= 0; --j)
      p[i].primijeni(s[j]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      bool iste = true;
      for (int k = 0; k < 8; ++k)
        if (p[i].a[k] != p[j].a[k])
          iste = false;
      cout << iste;
    }
    cout << endl;
  }
}
