/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                mag.cpp                                        *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwi±zanie wzorcowe.                          *
 *                        Najpierw obracamy siatkê o 45 stopni,          *
 *                        a potem liczymy mediany.                       *
 *                        Z³o¿ono¶æ czasowa: O(n log n).                 *
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

//Rozwi±zanie jednowymiarowego przypadku w metryce miejskiej
//Rozwi±zaniem jest mediana
int licz_wynik(vector<pair<int,int> > & os) {
  sort(os.begin(),os.end());

  LL wszystkiePunkty = 0;
  REP(i,os.size()) wszystkiePunkty+=os[i].second;

  LL naPrawo = wszystkiePunkty;
  REP(i,os.size()) {
    naPrawo -= os[i].second;
    if (naPrawo<=(wszystkiePunkty/2)) {
      return os[i].first;
    }
  }
}

//Obrót punktów wokó³ punktu (0,0) o 45 stopni
//Jednoczesne przeskalowanie pozwala unikn±æ stosowanie typó³ nieca³kowitych
void obrot(pair<int,int> & punkt){
  int tymczx = punkt.first - punkt.second;
  int tymczy = punkt.first + punkt.second;
  punkt.first = tymczx;
  punkt.second = tymczy;
}

//Obrót w drug± stronê
void obrot2(pair<int,int> & punkt){
  int tymczx = (punkt.first + punkt.second)/2;
  int tymczy = (punkt.second - punkt.first)/2;
  punkt.first = tymczx;
  punkt.second = tymczy;
}


void wezLepszy(pair<int,int> & najlepszy, pair<int,int> kandydat,
    vector<pair<int,int> > & sklepy, vector<int> & liczba) {
  LL roznica = 0LL;

  REP(i,sklepy.size()) {
    LL odl1 = max(abs(najlepszy.first-sklepy[i].first),abs(najlepszy.second - sklepy[i].second));
    LL odl2 = max(abs(kandydat.first-sklepy[i].first),abs(kandydat.second - sklepy[i].second));
    LL tymcz = odl1 - odl2;
    roznica += tymcz * (LL) liczba[i];
  }
  if (roznica>0) najlepszy = kandydat;
}

int main() {
  int n;
  scanf("%d",&n);
  int px,py,c;

  vector<pair<int,int> > sklepy;
  vector<int> liczba;

  // liczba[i] to liczba odwiedzin sklepu dziennie
  REP(i,n) {
    scanf("%d%d%d",&px,&py,&c);
    // aby unikn±æ problemów w typami nieca³kowitymi
    px*=2;py*=2;
    sklepy.push_back(make_pair(px,py));
    liczba.push_back(c);
  }

  // obracamy wszystkie punkty
  REP(i,sklepy.size()) {
    obrot(sklepy[i]);
  }

  vector<pair<int,int> > os_x;
  vector<pair<int,int> > os_y;
  // teraz oddzielamy os x i os y
  REP(i,sklepy.size()) {
    os_x.push_back(make_pair(sklepy[i].first,liczba[i]));
    os_y.push_back(make_pair(sklepy[i].second,liczba[i]));
  }


  // i liczymy optymalne wyniki dla osi x i osi y
  int wynikx = licz_wynik(os_x);
  int wyniky = licz_wynik(os_y);
  pair<int,int> punkt = make_pair(wynikx,wyniky);
  // i obracamy punkty z powrotem
  obrot2(punkt);
  REP(i,sklepy.size()) {
    obrot2(sklepy[i]);
  }

  // musimy sprawdziæ s±siadów
  if (punkt.first%2 == 1) {
    pair<int,int> najlepszy = punkt;
    najlepszy.first++; najlepszy.second++;
    int x1 = punkt.first;
    int y1 = punkt.second;


    wezLepszy(najlepszy,make_pair(x1+1,y1+1),sklepy,liczba);
    wezLepszy(najlepszy,make_pair(x1+1,y1-1),sklepy,liczba);
    wezLepszy(najlepszy,make_pair(x1-1,y1+1),sklepy,liczba);
    wezLepszy(najlepszy,make_pair(x1-1,y1-1),sklepy,liczba);
    punkt = najlepszy;
  }

  printf("%d %d\n",punkt.first/2,punkt.second/2);
  return 0;

}
