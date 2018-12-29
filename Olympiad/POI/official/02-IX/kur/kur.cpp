/*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Kurort narciarski                              *
 *   Plik:                kur.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// zamiast standardowego bool'a:
// bedzie szybciej, bo zwykle w vector<bool> pojedynczy bool
// spychany jest do bitu i stad niepotrzebny narzut czasowy
typedef int boolean;

typedef vector< vector<int> > Trasy;
typedef vector< vector<boolean> > Przejazd;

struct Wyciag {
  int q1,q2,r;
};

typedef vector<Wyciag> Wyciagi;

// do wczytywania wyciagu
istream& operator>>(istream& s,Wyciag& w)
{
  s >> w.q1 >> w.q2 >> w.r;
  --w.q1;
  --w.q2;
  return s;
}

void wczytaj_trasy(istream& s,Trasy& t, int ile)
{
  for (int i=0;i<ile;i++) {
    int p1,p2;
    s >> p1 >> p2;
    t[--p1].push_back(--p2);
  }
}

void wczytaj_wyciagi(istream& s, Wyciagi& wyciagi,  int ile)
{
  for (int i=0;i<ile;i++) {
    Wyciag w;
    s >> w;
    wyciagi.push_back(w);
  }
}

//pomocnicza funkcja dla funkcji przejdz
void idz(int v,vector<boolean>& odwiedzone,const Trasy& trasy)
{
  const vector<int>& odjazdy = trasy[v];
  const int ile = odjazdy.size();
  for (int i=0;i<ile;++i)
    if (!odwiedzone[odjazdy[i]]) {
      const int nowe = odjazdy[i];
      odwiedzone[nowe]=true;
      idz(nowe,odwiedzone,trasy);
    }
}

//przechodzi wszystkie mozliwe wierzcholki w "odwiedzone" chodzac po "trasach"
//zaczyna od wierzcholkow juz odwiedzonych
void przejdz(vector<boolean>& odwiedzone, const Trasy& trasy) {
  const int n = odwiedzone.size();
  for (int i=0;i<n;i++)
    if (odwiedzone[i])
      idz(i,odwiedzone,trasy);
}

//nowe mozliwe konce podrozy wyciagami
void nowe_mozliwosci(int punkty, Przejazd& przejazd,
                     const vector<boolean>& aktualnie, const Wyciagi& wyciagi)
{
  const int m = wyciagi.size();
  for (int j=0;j<m;j++) {
    const Wyciag &w=wyciagi[j];
    if (aktualnie[w.q1]) {
      int reszta=punkty-w.r;
      if (reszta>=0) przejazd[reszta][j]=true;
    }
  }
}

//znajduje polany, do ktorych mozna dojechac teraz wyciagami
void dojazdy(const vector<boolean>& teraz, vector<boolean>& aktualnie,
             const Wyciagi& wyciagi)
{
  const int m = wyciagi.size();
  for(int j=0;j<m;j++)
    if (teraz[j]) 
      aktualnie[wyciagi[j].q2]=true;
}

int main()
{
  //wczytanie danych
  ifstream input("kur.in");
  int n,n1,k,m,b,s;
  input >> n >> n1 >> k;
  Trasy trasy(n);
  wczytaj_trasy(input,trasy,k);
  input >> m;
  Wyciagi wyciagi;
  wczytaj_wyciagi(input,wyciagi,m);
  input >> b >> s; b--;
  //przetworzenie danych
  int wynik=s+1;
  Przejazd przejazd(s);
  for (int i=0;i<s;i++) przejazd[i].resize(m,false);
  vector<boolean> aktualnie(n,false);
  aktualnie[b]=true;
  for (int i=s;;i--) {
    przejdz(aktualnie,trasy);
    for (int j=0;j<n1;j++)
      if (aktualnie[j]) {
        wynik=i;
        break;
      }
    if (!i) break;
    nowe_mozliwosci(i,przejazd,aktualnie,wyciagi);
    fill(aktualnie.begin(),aktualnie.end(),false);
    dojazdy(przejazd[i-1],aktualnie,wyciagi);
  }
  //zapisanie wyniku
  ofstream output("kur.out");
  if (wynik!=s+1) output << wynik << '\n';
  else {
    //powinno sie nigdy nie zdarzyc
    cerr << "Niepoprawny plik wejsciowy" << '\n';
    return 1;
  }
}
