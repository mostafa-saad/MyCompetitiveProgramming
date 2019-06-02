/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Korale                                             *
 *   Autor programu:       Tomek Idziaszak                                    *
 *   Zlozonosc czasowa:    O(nk)                                              *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/

#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define REPDN(i,n) for(int i=(n)-1;i>=0;--i)

template<class T> int size(const T& c) { return c.size(); }
typedef long long ll;
typedef vector<int> VI;

const int NK = 10000000+100;
int n,k;
ll a[NK];
int index[NK], previous[NK];
int last_index;

int main() {
  scanf("%d%d",&n,&k);

  REP(i,n) scanf("%lld",&a[i]);
  vector<pair<ll, int> > v;
  v.push_back(make_pair(0, last_index));
  previous[last_index] = -1;
  last_index++;

  REPDN(i,n) {
    vector<pair<ll, int> > va = v, vb = v;
    REP(j,size(vb)) {
      vb[j].first += a[i];
      vb[j].second = last_index;
      previous[last_index] = v[j].second;
      index[last_index++] = i+1;
    }
    int ia=0, ib=0;
    v.clear();
    while (ia < size(va) && ib < size(vb)) {
      if (va[ia].first < vb[ib].first) v.push_back(va[ia++]);
      else v.push_back(vb[ib++]);
    }
    while (ia < size(va)) v.push_back(va[ia++]);
    while (ib < size(vb)) v.push_back(vb[ib++]);
    if (size(v) > k) v.resize(k);
  }

  printf("%lld\n", v[k-1].first);
  int j = v[k-1].second;
  bool first = true;
  while (previous[j] != -1) {
    if (!first) printf(" ");
    first = false;
    printf("%d", index[j]);
    j = previous[j];
  }
  printf("\n");
}
