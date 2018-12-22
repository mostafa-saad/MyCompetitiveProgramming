#include <algorithm>
#include <iostream>
using namespace std;

int r, s;
char a[50][51];
int u[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int v[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int broj_susjeda(int i, int j) {
  int ret = 0;
  for (int k = 0; k < 8; ++k) {
    int x = i + u[k];
    int y = j + v[k];
    ret += (x >= 0 && y >= 0 && x < r && y < s && a[x][y] == 'o');
  }
  return ret;
}

int main () {
  cin >> r >> s;
  for (int i = 0; i < r; ++i)
    cin >> a[i];

  int rjesenje = 0, maks = 0;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < s; ++j)
      if (a[i][j] == 'o')
        rjesenje += broj_susjeda(i, j);
      else
        maks = max(maks, broj_susjeda(i, j));
  cout << rjesenje / 2 + maks << endl;
}
