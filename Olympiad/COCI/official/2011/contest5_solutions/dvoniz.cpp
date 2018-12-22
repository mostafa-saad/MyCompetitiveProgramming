/*
 * HONI, zadatak DVONIZ
 * Autor: Goran Zuzic
 *
 * Sluzbeno rjesenje, trebalo bi dobiti sve bodove. Ukupna slozenost O(n lg n).
 *
 */

#include <algorithm>
#include <functional>

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 100100;

int n, S;
int A[MAXN];

int L[MAXN], R[MAXN];
vector<int> Ubaci[MAXN];

int main( void )
{
  scanf("%d %d", &n, &S);

  for (int i = 0; i < n; ++i) {
    scanf("%d", A + i);
  }

  int a = 0, b = 0;
  int suma = 0;
  while(a < n) {
    if (b < n && suma+A[b] <= S) {
      suma += A[b++];
    } else {
      R[a] = b-a;
      suma -= A[a++];
    }
  }
  a = b = n-1;
  while (a >= 0) {
    if (b >= 0 && suma+A[b] <= S) {
      suma += A[b--];
    } else {
      L[a] = a-b;
      suma -= A[a--];
    }
  }

  for (int i = 0; i+1 < n; ++i) {
    int val = min(L[i], R[i+1]);
    Ubaci[i-val+1].push_back(i);
  }

  multiset<int> PQ;
  for (int i = 0; i < n; ++i) {
    while (!PQ.empty() && *PQ.begin() < i)
      PQ.erase(PQ.begin());

    for (vector<int>::iterator it = Ubaci[i].begin(); it != Ubaci[i].end(); ++it) {
      PQ.insert(*it);
    }
    Ubaci[i].clear();

    if (!PQ.empty())
      printf("%d\n", (*PQ.rbegin() - i + 1) * 2 );
    else
      printf("0\n");
  }

  return (0-0);
}
