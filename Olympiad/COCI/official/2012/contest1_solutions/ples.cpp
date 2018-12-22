#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector< int > L[2];
vector< int > H[2];
int M;

void match(vector< int > &l, vector< int > &h) {
  if (l.empty() || h.empty()) return;
  for (int i = l.size() - 1, j = h.size() - 1; i >= 0; --i, --j, ++M) {
    while (j >= 0 && h[j] >= l[i]) 
      --j;
    if (j < 0) 
      return;
  }   
}

int main(void) {
  scanf("%d", &N);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < N; ++j) {
      int h; scanf("%d", &h);
      if (h < 0)
        L[i].push_back(-h);
      else
        H[i].push_back(h);
    }
    sort(L[i].begin(), L[i].end());
    sort(H[i].begin(), H[i].end());
  }

  match(L[0], H[1]);
  match(L[1], H[0]);

  printf("%d\n", M);
  return 0;
}
