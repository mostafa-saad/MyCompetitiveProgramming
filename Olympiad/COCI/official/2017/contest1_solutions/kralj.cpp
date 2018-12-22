#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> P;
#define X first
#define Y second

const int MAX = 500100;

int n;
int on[MAX];
int moji[MAX], poc[MAX];
int pref[MAX];
vector <int> V[MAX];

int rijesi(int prvi)
{
  int ret = 0;
  set <int> S;

  for (int i=prvi, j=0; j<n; j++, i=(i+1) % n) {
    for (auto it : V[i])
      S.insert(it);

    auto it = S.upper_bound(on[i]);
    if (it == S.end())
      S.erase(S.begin());
    else {
      ret++;
      S.erase(it);
    }
  }

  return ret;
}

int main()
{
  scanf("%d", &n);

  memset(pref, -1, sizeof pref);

  for (int i=0; i<n; i++) {
    scanf("%d", &poc[i]);
    poc[i]--;
  }

  for (int i=0; i<n; i++)
    scanf("%d", &on[i]);

  for (int i=0; i<n; i++) {
    scanf("%d", &moji[i]);
    pref[poc[i]]++;
    V[poc[i]].push_back(moji[i]);
  }

  P minn = P(MAX, MAX);
  for (int i=0; i<n; i++) {
    if (i)
      pref[i] += pref[i-1];

    minn = min(minn, P(pref[i], i));
  }

  int prvi = (minn.Y + 1) % n;
  printf("%d\n", rijesi(prvi));

  return 0;
}

