/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Gazociagi (GAZ)                                            *}
{*   Plik:    gaz.cpp                                                    *}
{*   Autor:   Maciej Jaskowski                                           *}
{*   Opis:    Rozwiazanie wzorcowe. Miotla (na STLu)                     *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>

#include <set>
#include <vector>
#include <algorithm>

#define DB 0

using namespace std;

struct punkt{
  int x;
  int y;
  int zrodlo;
  int numer;
};

bool operator==(punkt p1, punkt p2){
  return (p1.x == p2.x && p1.y == p2.y && p1.numer == p2.numer);
}

ostream &operator<<(ostream &os, const punkt &m1){
  os <<"(x: "<<m1.x<<"; y: "<<m1.y<<"; zrodlo?: "<<m1.zrodlo<<"; nr: "<<m1.numer<<") ";
  return os;
}

//porzadek w Y-strukturze: rosnacy y, rosnacy x.
struct ltMiotla{
  bool operator()(punkt m1, punkt m2) const{
    if(m1.y < m2.y) return true;
    if(m1.y == m2.y && m1.x > m2.x) return true;
    return false;
  }
};

//porzadek punktow w X-strukturze: rosnacy x, malejacy y.
struct lt1{
  bool operator()(punkt m1, punkt m2) const{
    if(m1.x < m2.x) return true;
    if(m1.x == m2.x){
      if(m1.y > m2.y) return true;
    }
    return false;
  }
};

int main(){
//wczytaj
  int N;
  cin >> N;
  vector<punkt> V;
  for(int n = 0; n < N; n++){
    punkt m;
    cin >>m.x >>m.y;
    m.zrodlo = 1;
    m.numer = n+1;
    V.push_back(m);
  }
  for(int n = 0; n < N; n++){
    punkt m;
    cin >>m.x >>m.y;
    m.zrodlo = 0;
    m.numer = n+1;
    V.push_back(m);
  }

//sortujemy, zeby uzyskac X-strukture.
  sort(V.begin(),V.begin()+2*N,lt1());
#if DB
  for(int n = 0; n < 2*N; n++){
    cout <<V[n]<<endl;
  }
#endif
//stworz miotle (Y-strukture): S.
  set<punkt,ltMiotla> S;
//dla kazdego elementu z V (po kolei): 
// jesli v jest zrodlem to dodaj do miotly
// jesli v jest ujsciem to dodaj do wyniku pare (upper_bound(v),v);
//     usun z S upper_bound(v)
//     dodaj do wyniku odleglosc miedzy up_b(v) i v
 
  long long odl = 0;
  //wynik:
  vector<pair<int,int> > W;
#if DB
  cout <<endl<<endl;
#endif
  for(vector<punkt>::iterator v = V.begin(); v != V.end(); v++){
    if(v->zrodlo){
      S.insert(*v);
    }
    else{
      punkt w = *(S.lower_bound(*v));
#if DB
      cout <<"lower_bound("<<*v<<")="<<w<<endl;
#endif
    // na tych assertach sie wysypywal, jesli ktorys z testow jest zly.
      assert(w.x <= v->x);
      assert(w.y >= v->y);
      assert(w == *(S.lower_bound(*v)));
      S.erase(S.lower_bound(*v));
      odl += (v->x - w.x) + (w.y - v->y);
      W.push_back(make_pair(w.numer,v->numer));
    }
#if DB
    for(set<punkt>::iterator iterS = S.begin(); iterS != S.end(); iterS++){
      cout <<(*iterS)<<endl;
    }
    cout <<"---"<<endl;
 #endif
  }
  //wypisz wynik:
  cout <<odl<<endl;
  for(int n = 0; n < N; n++){
    cout <<W[n].first <<" "<<W[n].second <<endl;
  }
  return 0;
}
