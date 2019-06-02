/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                magb0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwi±zanie niepoprawne.                       *
 *                        Najpierw obracamy siatkê o 45 stopni,          *
 *                        a potem liczymy mediany, ale moga pojawic sie  *
 *                        bledy zaokraglen                               *
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

//Solves the problem for Manthattan one-dimension problem
//The median is the answer
float count_result(vector<pair<float,int> > & axis) {
  sort(axis.begin(),axis.end());

  LL allPoints = 0;
  REP(i,axis.size()) allPoints+=axis[i].second;

  LL onTheRight = allPoints;
  REP(i,axis.size()) {
    onTheRight -= axis[i].second;
    if (onTheRight<=(allPoints/2)) {
      return axis[i].first;
    }
  }
}

//Rotates point around (0,0) by 45 degrees
//Scales it also to avoid floating points errors
void rotate(pair<float,float> & point){
  float tempx = (point.first - point.second)/(sqrt(2.0));
  float tempy = (point.first + point.second)/(sqrt(2.0));
  point.first = tempx;
  point.second = tempy;
}

// Rotates in other direction
void unrotate(pair<float,float> & point){
  float tempx = (point.first + point.second)/(sqrt(2.0));
  float tempy = (point.second - point.first)/(sqrt(2.0));
  point.first = tempx;
  point.second = tempy;
}

void getBetter(pair<float,float> & best, pair<float,float> candidate,
    vector<pair<float,float> > & shops, vector<int> & count) {
  double difference = 0;

  REP(i,shops.size()) {
    double dist1 = max(abs(best.first-shops[i].first),abs(best.second - shops[i].second));
    double dist2 = max(abs(candidate.first-shops[i].first),abs(candidate.second - shops[i].second));
    double temp = dist1 - dist2;
    difference += temp * (double) count[i];
  }
  if (difference>0) best = candidate;
}


int main() {
  int n;
  scanf("%d",&n);
  int px,py,c;

  vector<pair<float,float> > shops;
  vector<int> count;

  // in counts we keep how many shops are there
  REP(i,n) {
    scanf("%d%d%d",&px,&py,&c);
    shops.push_back(make_pair(px,py));
    count.push_back(c);
  }

  // rotating all points
  REP(i,shops.size()) {
    rotate(shops[i]);
  }

  vector<pair<float,int> > xaxis;
  vector<pair<float,int> > yaxis;
  // now we're separating x and y axis.
  REP(i,shops.size()) {
    xaxis.push_back(make_pair(shops[i].first,count[i]));
    yaxis.push_back(make_pair(shops[i].second,count[i]));
  }


  // and count optimal result for x and for y axis
  float resultx = count_result(xaxis);
  float resulty = count_result(yaxis);
  pair<float,float> result_point = make_pair(resultx,resulty);
  // and rotates our point back
  unrotate(result_point);
  REP(i,shops.size()) {
    unrotate(shops[i]);
  }

  // need to check neighbours
  if ((int)(result_point.first*2+0.001)%2 == 1) {
    pair<float,float> bestPoint = result_point;
    bestPoint.first+=0.5; bestPoint.second+=0.5;
    float x1 = result_point.first;
    float y1 = result_point.second;


    getBetter(bestPoint,make_pair(x1+0.5,y1+0.5),shops,count);
    getBetter(bestPoint,make_pair(x1+0.5,y1-0.5),shops,count);
    getBetter(bestPoint,make_pair(x1-0.5,y1+0.5),shops,count);
    getBetter(bestPoint,make_pair(x1-0.5,y1-0.5),shops,count);
    result_point = bestPoint;
  }

  printf("%d %d\n",(int)(result_point.first+0.001),(int)(result_point.second+0.001));

  return 0;

}
