/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                magb0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwi±zanie niepoprawne.                       *
 *                        Znajduje minimum, poprzez porównywanie sasiadow*
 *                        ale robi to tylko w pionie i poziomie.         *
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
bool cc(int& akt_x, int & akt_y, vector<pair<int,int> > &tab, VI & count, LL & akt_result, int dx, int dy) {
  LL result = count_sum(tab,count,akt_x+dx,akt_y+dy);
  if (result<akt_result) {
    akt_result = result;
    akt_x+=dx;
    akt_y+=dy;
    return true;
  }
  return false;
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

  int minx = tab[0].first;
  REP(i,tab.size()) minx = min(minx,tab[i].first);

  int miny = tab[0].second;
  REP(i,tab.size()) miny = min(miny,tab[i].second);

  int akt_x = minx;
  int akt_y = miny;
  LL akt_result = count_sum(tab,count,akt_x,akt_y);
  bool ending = false;
  int duch = 0;
  while (!ending) {
    ending = true;
    duch ++;
//    if (duch%100 ==0)
//    cerr << duch << endl;
//    What was that for? -Jakub Radoszewski
    
    FOR(dx,-1,1) {
      FOR(dy,-1,1) {
        if ((dx==0)||(dy==0)) {
          if (cc(akt_x,akt_y,tab,count,akt_result,dx,dy)) {
            ending = false;
            break;
          }
        }
      }
      if (ending == false) break;
    }
  }

  printf("%d %d\n",akt_x, akt_y);
  return 0;

}
