/*
  Sluzbeno rjesenje zadatka SORT
  Autor: Goran Zuzic
*/

#include <algorithm>
#include <functional>

#include <cassert>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <string>

using namespace std;

const int MAXN = 1024;

int n;
int A[MAXN];
int bio[MAXN];

vector< vector<int> > Out;

void odradi(const vector<int> &V)
{
  int n = V.size();
  int next = A[ V[0] ];

  for (int i = 0; i < n; ++i) {
    int j = (i+1)%n;
    int nov_next = A[ V[j] ];
    A[ V[j] ] = next;
    next = nov_next;
  }
}

void solve()
{
  vector<int> Jedan;
  vector<int> Svaki;
  int kol = 0;

  memset(bio, 0, sizeof bio);
  for (int i = 0; i < n; ++i) {
    if (bio[i]) continue;
    vector<int> V;

    int x = i;
    for( ; bio[x] == false; x = A[x] ) {
      V.push_back(x);
      bio[x] = true;
    }
    
    if (V.size() > 1) {
      ++kol;
      Svaki.push_back(i);
      Jedan.swap(V);
    }
  }

  if (kol == 0) return ;

  if (kol == 1) {
    Out.push_back(Jedan);
    odradi( Out.back() );
    for (int i = 0; i < n; ++i)
      assert(A[i] == i);
  } else {
    Out.push_back(Svaki);
    odradi( Out.back() );
    solve();
  }
}

int main( void )
{
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", A+i);
    --A[i];
  }

  solve();

  printf("%d\n", (int)Out.size());
  for (int i = 0; i < (int)Out.size(); ++i) {
    printf("%d:", (int)Out[i].size()); 
    for (int j = 0; j < (int)Out[i].size(); ++j)
      printf(" %d", Out[i][j]+1);
    putchar('\n');
  }

  return (0-0);
}
