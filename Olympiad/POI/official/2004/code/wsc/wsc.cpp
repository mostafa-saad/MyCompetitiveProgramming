/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Wschód-Zachód                                  *
 *   Plik:                wsc.cpp                                        *
 *   Autor:               Piotr Sankowski                                *
 *************************************************************************/

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

/// Klasa sortowania kubelkowego.
/// n - to liczba kubelkow
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

/// Klasa zawierajaca opis danych testowych.
class DaneWsc{
protected:
  /// Liczba miast
  int n;
  /// Liczba miast na wschodniej granicy
  int w;
  /// Liczba miast na zachodniej granicy
  int z;
  /// Liczba pociagow
  int p;
  /// Krawedzie miedzy miastami
  vector<vector<int> > krawedzie;
  /// Ile pociagow znajduje sie w miescie.
  /// mozliwe wartosci to 0 i 1.
  vector<int> liczbaPociagow;

  void dodajSkierowanaKrawedz(int zMiasta, int doMiasta){
    krawedzie[zMiasta].push_back(doMiasta);
  };

  void dodajKrawedz(int miasto1, int miasto2){
    dodajSkierowanaKrawedz(miasto1, miasto2);
    dodajSkierowanaKrawedz(miasto2, miasto1);
  };

public:
  /// Oznaczenia miast lub poddrzew
  const static int Wewnetrzne = 0; /// Miasta wewnetrzne
  const static int Wschodnie = 1;  /// Miasta na wschodniej granicy
  const static int Zachodnie = 2;  /// Miasta na zachodniej granicy
  const static int Obydwa = 3;     /// Miasta na wschodniej i zachodzniej granicy

  /// Zwraca gdzie lezy miasto
  int stronaMiasta(int i){
    if (i<=w) return Wschodnie;
    if (i>n-z) return Zachodnie;
    return Wewnetrzne;
  };

  /// Wczytuje dane wejsciowe 
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
  /// Odpowiedz programu
  int dni;
  /// Odcinek W torow przez ktory musza przejechac wszystkie pociagi
  int wschodW;
  int zachodW;

  /// Znajduje odcinek W
/*  int szukajW(int miasto, int przodek){
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
  };*/


  int szukajW(int m0,int prz){
    int miasto = m0;
    vector<int> przodek(n+1, prz);
    vector<int> strona(n+1, 0);
    vector<int> i(n+1, 0);
    while(miasto!=prz)
    {
    	if (i[miasto]>=krawedzie[miasto].size())
    	{
		strona[miasto] |= stronaMiasta(miasto);
    		if (strona[miasto] == Zachodnie)
    		{
    			wschodW = przodek[miasto];
    			zachodW = miasto;
    		}
    		strona[przodek[miasto]] |= strona[miasto];
    		miasto = przodek[miasto];
    		continue;
    	}
    	int i2 = i[miasto]++;
    	int nm = krawedzie[miasto][i2];
    	if (nm == przodek[miasto]) continue;
    	przodek[nm] = miasto;
    	miasto = nm;
    }
  };

  /// Oblicza odleglosc przy pomocy DFS, do miast na zachodniej granicy, lub
  /// do miast, w ktorych staja pociagi. Znalezione odleglosci dodaje do struktury
  /// odleglosci.
/*  void policzOdleglosci(int odleglosc, int miasto, int przodek, Sortowanie &odleglosci){
    if ((liczbaPociagow[miasto]|=0) || (stronaMiasta(miasto)==Zachodnie)){
      odleglosci.dodaj(odleglosc);
    }//else{
    for (int i=0 ; i<krawedzie[miasto].size() ; i++)
      if (krawedzie[miasto][i] != przodek)
	policzOdleglosci(odleglosc+1, krawedzie[miasto][i], miasto, odleglosci);
    //};
  };*/

  void policzOdleglosci(int odleglosc, int m0, int prz, Sortowanie &odleglosci){
    int miasto = m0;
    vector<int> przodek(n+1, prz);
    vector<int> i(n+1, 0);
    if ((liczbaPociagow[miasto]|=0) || (stronaMiasta(miasto)==Zachodnie)){
      odleglosci.dodaj(odleglosc);
    }
    while(miasto!=prz)
    {
    	if (i[miasto]>=krawedzie[miasto].size())
    	{
    		miasto = przodek[miasto];
    		--odleglosc;
    		continue;
    	}
    	int i2 = i[miasto]++;
    	int nm = krawedzie[miasto][i2];
    	if (nm == przodek[miasto]) continue;
    	przodek[nm] = miasto;
    	miasto = nm;
    	++odleglosc;
        if ((liczbaPociagow[miasto]|=0) || (stronaMiasta(miasto)==Zachodnie)){
          odleglosci.dodaj(odleglosc);
        }
    }
  };


  /// Wyznacza czas jaki zajmie przejazd wszytkimi pociagami
  void policzCzas(const vector<int> &odleglosciWschod, const vector<int> &odleglosciZachod){
    int odlegloscZachod = p - 1;
    int czas = -1;
    for (int i=0 ; i<p ; i++){
      if (czas < odleglosciWschod[i]) czas = odleglosciWschod[i];
      else if (czas >= odleglosciWschod[i]) czas++;
      if (dni < czas + odleglosciZachod[odlegloscZachod] + 1)
	dni = czas + odleglosciZachod[odlegloscZachod] + 1;
      odlegloscZachod--;
    };
  };

  /// Rozwiazuje zadanie
  void rozwiaz(){
    Sortowanie odleglosciWschodSort(n);
    Sortowanie odleglosciZachodSort(n);

    szukajW(1, 0);
    policzOdleglosci(0, wschodW, zachodW, odleglosciWschodSort);
    policzOdleglosci(0, zachodW, wschodW, odleglosciZachodSort);

    vector<int> odleglosciWschod = odleglosciWschodSort.sortuj();
    vector<int> odleglosciZachod = odleglosciZachodSort.sortuj();
    
    policzCzas(odleglosciWschod, odleglosciZachod);
  };

public:

  Wsc() : dni(0), DaneWsc(){
    rozwiaz();
  };

  friend ostream& operator<<(ostream &os, const Wsc &data){
    cout << data.dni << endl;
  };
};

int main(){
  cout << Wsc();
};
