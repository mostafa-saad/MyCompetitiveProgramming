/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Kaglony                                        *
 *   Plik:                kagwer.cpp                                     *
 *   Autor:               Piotr Sankowski                                *
 *************************************************************************/

#include <vector>
#include <set>
#include <iostream>
#include <list>
#include <fstream>
using namespace std;
class Krawedz{
public:
  int v;
  list<Krawedz>::iterator w;
  Krawedz(int _v) : v(_v) {};
};

class Graf{
protected:
  int n;
  int m;
  vector<list<Krawedz> > krawedzie;
  vector<int> sasiedzi;
  int testsasiedztwa;
public:

  Graf(int _n, int _m) : n(_n), m(_m), krawedzie(n), sasiedzi(n) {};

  void polacz(int v1,int v2){
    krawedzie[v1].push_front(Krawedz(v2));
    krawedzie[v2].push_front(Krawedz(v1));
    krawedzie[v1].front().w = krawedzie[v2].begin();
    krawedzie[v2].front().w = krawedzie[v1].begin();
  };  

  void wczytaj(){
    for (int i=0 ; i<m ; i++){
      int v1,v2;
      scanf("%d%d",&v1,&v2);
      polacz(v1-1,v2-1);
    };
  };

  void usun(int v){
    list<Krawedz>::iterator it = krawedzie[v].begin();
    list<Krawedz>::iterator eit = krawedzie[v].end();
    while (it!=eit){
      krawedzie[it->v].erase(it->w);
      it++;
    }
  };

  bool tacysami(int v1, int v2){
    //    cout << "T " << v1 << " " << v2 << endl;
    testsasiedztwa++;
    if (krawedzie[v1].size()!=krawedzie[v2].size())
      return false;

    list<Krawedz>::iterator it = krawedzie[v1].begin();
    list<Krawedz>::iterator eit = krawedzie[v1].end();
    while (it!=eit){
      //      cout << it->v << " ";
      sasiedzi[it->v] = testsasiedztwa;
      it++;
    };
    //    cout << endl;
    sasiedzi[v1] = testsasiedztwa;
    sasiedzi[v2] = testsasiedztwa;
    it = krawedzie[v2].begin();
    eit = krawedzie[v2].end();
    while (it!=eit){
      //      cout << it->v << " ";
      if (sasiedzi[it->v] != testsasiedztwa)
	return false;
      it++;
    };
    //    cout << endl;
    return true;
  };
  
};


class Podzial{
  uint n;
  int krok;
  vector<int> permutacja;
  vector<int> pozycja;

  vector<int> koniec;
  vector<int> poczatek;

  vector<int> aktywne;
public:

  Podzial(uint _n) : n(_n), krok(0), permutacja(n), pozycja(n), koniec(n), poczatek(n) {
    poczatek[n-1] = 0;
    for (uint i=0 ; i<n ; i++){
      koniec[i] = n-1;
      permutacja[i] = i;
      pozycja[i] = i;
    };
  };
  void zamien(int elem1, int elem2){
    int tmp = pozycja[elem1];
    pozycja[elem1] = pozycja[elem2];
    pozycja[elem2] = tmp;
    permutacja[pozycja[elem1]] = elem1;
    permutacja[pozycja[elem2]] = elem2;
  };

  void wyjmij(int element){
    zamien(permutacja[poczatek[koniec[element]]], element);
    poczatek[koniec[element]]++;
    aktywne.push_back(element);
    /*
    cout << "wyjmij " << element << endl;
    for(uint i=0 ; i<n ; i++)
      cout << permutacja[i] << " ";
      cout << endl;*/
  };

  void wstaw(){
    //    cout << "wstaw" << endl;
    for (uint i=0 ; i<aktywne.size() ; i++){
      if (poczatek[koniec[aktywne[i]]] <= koniec[aktywne[i]]){
	koniec[aktywne[i]] = poczatek[koniec[aktywne[i]]]-1;
	poczatek[koniec[aktywne[i]]] = n;
      };
    };
    for (uint i=0 ; i<aktywne.size() ; i++){
      if (poczatek[koniec[aktywne[i]]] > koniec[aktywne[i]]){
	poczatek[koniec[aktywne[i]]] = pozycja[aktywne[i]];
      }
    };
    /*
    for(uint i=0 ; i<n ; i++)
      cout << permutacja[i] << " ";
    cout << endl;
    for(uint i=0 ; i<n ; i++)
      cout << pozycja[i] << " ";
    cout << endl;
    for(uint i=0 ; i<n ; i++)
      cout << koniec[i] << " ";
    cout << endl;
    for(uint i=0 ; i<n ; i++)
      cout << poczatek[i] << " ";
    cout << endl;
    */
    aktywne.clear();
  };

  void wyjmij(const list<Krawedz> &podzial){
    list<Krawedz>::const_iterator it = podzial.begin();
    list<Krawedz>::const_iterator eit = podzial.end();
    while (it!=eit){
      wyjmij(it->v);
      it++;
    };
  }

  list<int> permutacjaLista(){
    list<int> lista;
    for (uint i=0 ; i<n ; i++)
      lista.push_back(permutacja[i]);
    return lista;
  };
};

class Kaglon : public Graf{
  Podzial podzial;

  bool weryfikuj(list<int> perm){
    /*
    list<int>::iterator kit = perm.begin();
    while (kit!=perm.end()){
      cout << *kit << " ";
      kit++;
    };
    */
    list<int>::iterator it = perm.begin();
    int i = 0;
    while ((i < n-1)&&(it!=perm.end())){
      int poprzedniei = i;
      if (it!=perm.begin()){
	list<int>::iterator tit = it;
	tit--;
	if (tacysami(*tit, *it)){
	  usun(*tit);
	  perm.erase(tit);
	  i++;
	}
      } 
      else if (it!=perm.end()){
	list<int>::iterator tit = it;
	tit++;
	if (tacysami(*it, *tit)){
	  usun(*it);
	  perm.erase(it);
	  it = tit;
	  i++;
	}
      }
      if (i==poprzedniei) it++;
    };
    return perm.size()==1;
  };
  
  void faktoryzuj(int l, int p){
    /*
    podzial.wyjmij(krawedzie[l]);
    podzial.wstaw();
    podzial.wyjmij(l);
    podzial.wstaw();
    
    
    
    podzial.podziel(krawedzie[l]);
    podzial.podziel(l);
    */
    for (int i=0 ; i<n ; i++){
      podzial.wyjmij(krawedzie[i]);
      podzial.wstaw();
    }
  };


public:
  Kaglon(int _n, int _m) : Graf(_n,_m), podzial(n) {
    wczytaj();
    faktoryzuj(0,n-1);
    if (weryfikuj(podzial.permutacjaLista()))
      printf("TAK\n");
    else
      printf("NIE\n");    
  };
};

class Kaglony{
public:
  Kaglony(){
    int numK;
    scanf("%d",&numK);
    for (int i=0 ; i<numK ; i++){
      int n,m;
      scanf("%d%d",&n,&m);
      Kaglon(n,m);
    }
  };
};


int main(){
  Kaglony();
};




