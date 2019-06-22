/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                mags0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwi±zanie nieoptymalne.                      *
 *                        Liczy odleg³osc dla kazdego punktu             *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define VAR(a,b) typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
#define ALL(f,w) ({ bool _ok=true; f _ok=_ok && (w); _ok; })
#define EXISTS(f,w) (!ALL(f,!(w)))
typedef long long LL;
const int INF = 1000000000;
typedef vector<int> VI;
template<class T> inline int size(const T&c) { return c.size(); }
template<class T> inline vector<T> makeV(const T&x) { return vector<T>(1,x); }
template<class T> inline vector<T> makeV(const T&x,const T&y) {
    vector<T> v(2); v[0] = x; v[1] = y; return v;
}
template<class T> inline vector<T> makeV(const T&x,const T&y,const T&z) {
    vector<T> v(3); v[0] = x; v[1] = y; v[2]=z; return v;
}
template<class A,class B> inline bool contains(const A&a, const B&b) {
    return find(a.begin(),a.end(),b)!=a.end();
}



LL count_sum(vector<pair<int,int> > &tab, VI & count, int pozx, int pozy) {
  LL sum = 0;
  REP(i,tab.size()) {
    LL temp = max(abs(tab[i].first-pozx),abs(tab[i].second-pozy));
    temp *= count[i];
    sum+=temp;
  }
  return sum;
}

int main() {
  int n;
  scanf("%d",&n);
  int px,py,c;

  vector<pair<int,int> > tab;
  vector<int> count;

  // in counts we keep how many shops are there
  REP(i,n) {
    scanf("%d%d%d",&px,&py,&c);
    tab.push_back(make_pair(px,py));
    count.push_back(c);
  }

  LL min_result = count_sum(tab,count,0,0);
  int res_x = 0;
  int res_y = 0;


  int minx = tab[0].first;
  int maxx = tab[0].first;
  REP(i,tab.size()) minx = min(minx,tab[i].first);
  REP(i,tab.size()) maxx = max(maxx,tab[i].first);

  int miny = tab[0].second;
  int maxy = tab[0].second;
  REP(i,tab.size()) miny = min(miny,tab[i].second);
  REP(i,tab.size()) maxy = max(maxy,tab[i].second);

  FOR(x,minx,maxx) {
    FOR(y,miny,maxy) {
      LL result = count_sum(tab,count,x,y);
      if (result<min_result) {
        min_result = result;
        res_x = x;
        res_y = y;
      }
    }
  }

  printf("%d %d\n",res_x, res_y);
  return 0;

}
