/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Wschód-Zachód                                  *
 *   Plik:                wsc2.cpp                                       *
 *   Autor:               Piotr Sankowski                                *
 *************************************************************************/


#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

class SortowanieKubelkowe : public vector<int>{
public:
  SortowanieKubelkowe(int n) : vector<int>(n) {};

  void dodaj(int i){
    operator[](i)++;
  };

  vector<int> sortuj(){
    vector<int> wynik;
    for (int i=0 ; i<size() ; i++)
      for (int j=0 ; j<operator[](i) ; j++)
	wynik.push_back(i);
    return wynik;
  };
};

typedef SortowanieKubelkowe Sortowanie;

class DaneWsc{
protected:
  int n;
  int w;
  int z;
  
  int p;

  vector<vector<int> > krawedzie;
  vector<int> liczbaPociagow;

  void dodajSkierowanaKrawedz(int zMiasta, int doMiasta){
    krawedzie[zMiasta].push_back(doMiasta);
  };

  void dodajKrawedz(int miasto1, int miasto2){
    dodajSkierowanaKrawedz(miasto1, miasto2);
    dodajSkierowanaKrawedz(miasto2, miasto1);
  };

public:
  const static int Wewnetrzne = 0;
  const static int Wschodnie = 1;
  const static int Zachodnie = 2;
  const static int Obydwa = 3;

  int stronaMiasta(int i){
    if (i<=w) return Wschodnie;
    if (i>n-z) return Zachodnie;
    return Wewnetrzne;
  };

  DaneWsc(){
    scanf("%d %d %d", &n, &w, &z);
    krawedzie.resize(n+1, vector<int>());
    if (w + z + 2 > n) throw "Zla liczba miast";

    int miasto1, miasto2;
    for (int i=1 ; i<n ; i++){
      scanf("%d %d", &miasto1, &miasto2); 
      dodajKrawedz(miasto1, miasto2);
    };
    scanf("%d", &p);
    liczbaPociagow.resize(n+1);
    int miasto;
    for (int i=0 ; i<p ; i++){
      scanf("%d", &miasto);
      liczbaPociagow[miasto]++;
    };
  };

};

class Wsc : protected DaneWsc{

  int dni;

  int wschodW;
  int zachodW;

  vector<int> doW;
  vector<int> kolejnosc;

  int szukajW(int miasto, int przodek){
    int strona = 0;
    for (int i=0 ; i<krawedzie[miasto].size() ; i++)
      if (krawedzie[miasto][i] != przodek)
   	strona |= szukajW(krawedzie[miasto][i], miasto);
    strona |= stronaMiasta(miasto);
    if (strona == Zachodnie) {
      wschodW = przodek;
      zachodW = miasto;
    };
    return strona;
  };

  void policzOdleglosci(int odleglosc, int miasto, int przodek, Sortowanie &odleglosci){
    doW[miasto] = przodek;
    kolejnosc.push_back(miasto);
    if (krawedzie[miasto].size() == 1){
      odleglosci.dodaj(odleglosc);
    }else{
    for (int i=0 ; i<krawedzie[miasto].size() ; i++)
      if (krawedzie[miasto][i] != przodek)
	policzOdleglosci(odleglosc+1, krawedzie[miasto][i], miasto, odleglosci);
    };
  };

  void solve(){
    Sortowanie odleglosciWschodSort(n);
    Sortowanie odleglosciZachodSort(n);
    szukajW(1, 0);
    policzOdleglosci(0, wschodW, zachodW, odleglosciWschodSort);
    int maxKol = kolejnosc.size();
    policzOdleglosci(0, zachodW, wschodW, odleglosciZachodSort);

    vector<int> odleglosciZachod = odleglosciZachodSort.sortuj();
    
    int odlegloscZachod = p-1;
    int czas = 0;
    
    while (odlegloscZachod>=0){
      for (int i=0 ; i<maxKol ; i++){
	if (liczbaPociagow[kolejnosc[i]]>0){
	  liczbaPociagow[doW[kolejnosc[i]]]++;
	  liczbaPociagow[kolejnosc[i]]--;
	};
      };
      czas++;
      if (liczbaPociagow[zachodW]>0){
	if (dni < czas + odleglosciZachod[odlegloscZachod])
	  dni = czas + odleglosciZachod[odlegloscZachod];
	liczbaPociagow[zachodW]--;
        odlegloscZachod--;
      };
    };
  };

public:

  Wsc() : dni(0), DaneWsc(), doW(n+1){
    kolejnosc.reserve(n);
    solve();
  };

  friend ostream& operator<<(ostream &os, const Wsc &data){
    cout << data.dni << endl;
  };
};


int main(){
  cout << Wsc();
};
