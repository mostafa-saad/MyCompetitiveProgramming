/* Tug of War
   Autor: Piotr Smulewicz
   Backtracking
 */

#include <iostream>
#include <numeric>
#include <vector>
#include <cstdlib>
using namespace std;
const int SIZE = 30001;
const int MAX_STRENGHT = 20;
int persons[SIZE * 2][2];
int str[SIZE * 2];
bool spots[SIZE * 2][2];
int n, k, a, b, s;
bool backtrack(int pe, int st) {
  if (pe < n * 2) {
    for (int i = 0; i < 2; i++)
      if (!spots[persons[pe][i]][i]) {
        spots[persons[pe][i]][i] = true;
        if (backtrack(pe + 1, st + (1 - 2 * i) * str[pe]))
          return true;
        spots[persons[pe][i]][i] = false;
      }
  } else if (abs(st) <= k) {
    return true;
  }
  return false;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> k;
  for (size_t i = 0; i < n * 2u; i++) {
    cin >> a >> b >> s;
    str[i] = s;
    persons[i][0] = a;
    persons[i][1] = b;
  }
  if (backtrack(0, 0))
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
}
