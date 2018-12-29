/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                magchk.cpp                                     *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Weryfikator rozwiazania.                       *
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
class Natural {
  /* obowiazkowa czesc prywatna */
  static const int BASE = 100000000;
  static const int BASEDIGS = 8;
  int ndigs;
  int *digs;
  void init(int n,const int *d) {
    while(n>0 && d[n-1]==0) --n;
    ndigs=n;
    digs=new int[n];
    for(int i=0;i<n;++i) digs[i]=d[i];
  }
  Natural(int n,const int *d) { init(n,d); }
  /* przesuwanie (dla dzielenia i pierwiastkowania) */
  Natural operator<<(int sh) const { // sh >= 0
    int n=sh+ndigs;
    int d[n];
    REP(i,sh) d[i]=0;
    REP(i,ndigs) d[i+sh]=digs[i];
    return Natural(n,d);
  }
public:
  /* konstruktory */
  Natural(int x=0) {
    int d[2];
    d[0]=x%BASE;
    d[1]=x/BASE;
    init(2,d);
  }
  Natural(const Natural&a) {
    init(a.ndigs,a.digs);
  }
  /* destruktor */
  ~Natural() { delete[] digs; }
  /* przypisanie */
  Natural &operator=(const Natural&a) {
    delete[] digs;
    init(a.ndigs,a.digs);
    return *this;
  }
  /* dodawanie */
  Natural operator+(const Natural&a) const {
    int n=max(ndigs,a.ndigs)+1;
    int d[n];
    REP(i,n) d[i]=0;
    REP(i,n) {
      if(i<ndigs) d[i]+=digs[i];
      if(i<a.ndigs) d[i]+=a.digs[i];
      if(d[i]>=BASE) { d[i]-=BASE; ++d[i+1]; }
    }
    return Natural(n,d);
  }
  Natural &operator+=(const Natural&a) {
    return *this = *this + a;
  }
  /* mno¿enie przez inta */
  Natural operator*(int x) const { // !!! 0 <= x <= BASE
    int n=ndigs+1;
    int d[n];
    long long a=0;
    REP(i,ndigs) {
      a+=digs[i]*(long long)x;
      d[i]=a%BASE;
      a/=BASE;
    }
    d[ndigs]=a;
    return Natural(n,d);
  }
  Natural &operator*=(int x) {
    return *this = *this * x;
  }
  bool operator==(const Natural&a) const {
    if(ndigs!=a.ndigs) return false;
    REP(i,ndigs) {
      if(digs[i]!=a.digs[i]) return false;
    }
    return true;
  }
 
  /* wypisywanie */
  void write() const {
    if(ndigs==0) printf("0");
    else {
      printf("%d",digs[ndigs-1]);
      FORD(i,ndigs-2,0) printf("%0*d",BASEDIGS,digs[i]);
    }
  }
 
};
  

Natural licz_wynik(vector<pair<int,int> > & tab, VI liczba, int pozx, int pozy) {
  Natural wyn = 0;
  REP(i,tab.size()) {
    Natural tymcz = liczba[i];
    tymcz *= max(abs(pozx-tab[i].first),abs(pozy-tab[i].second));
    wyn += tymcz;
  }
  return wyn;
}

int main(int argcount, char * * args ) {
  if (argcount!=4) {
    cout << "Uzycie: ./magchk.e <wejscie> <wyjscie uzytkownika> <poprawne wyjscie>" << endl;
    return 0;
  }
  FILE * wejscie = fopen(args[1],"r");
  FILE * wyjscie = fopen(args[3],"r");
  FILE * zawodnik = fopen(args[2],"r");

  int n;
  fscanf(wejscie,"%d",&n);
  int a,b,c;
  vector<pair<int,int> > tab;
  VI liczba;
  REP(i,n) {
    fscanf(wejscie,"%d%d%d",&a,&b,&c);
    tab.push_back(make_pair(a,b));
    liczba.push_back(c);
  }

  int u1,u2;
  fscanf(wyjscie,"%d%d",&u1,&u2);
  Natural poprawny_wynik = licz_wynik(tab,liczba,u1,u2);
  
  fscanf(zawodnik,"%d%d",&u1,&u2);
  Natural wynik_zawodnika = licz_wynik(tab,liczba,u1,u2);

  if (wynik_zawodnika == poprawny_wynik)  {
    //Jakub Radoszewski
    char ch;
    while (fscanf(zawodnik,"%c",&ch)==1)
      if (!(ch==' ' || ch==char(10) || ch==char(13) || ch==char(9)))
      {
        cout << "ZLE" << endl;
        cout << "Zbedny znak na koncu wyjscia: " << ch << endl;
        return 1;
      }
    cout <<"OK" << endl;
    return 0;
  } else {
    cout << "ZLE" << endl;
    cout <<"Sumaryczna odleglosc w pliku wyjsciowym: ";
    wynik_zawodnika.write();
    cout << ", powinno byc: ";
    poprawny_wynik.write();
    cout << endl;
    return 1;
  }
  return 0;
}

