/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     per5.cpp                                                  *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie weryfikacyjne.                                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

const int MAX_N = 300000;
const int PODSTAWA = 512*1024;
const int MAX_ZAKRES = 300000;
int n; //rozmiar multizbioru
int mod; //liczba modulo ktora obliczamy wynik
int permutacja[MAX_N];

int drzewo_licznikowe[2*PODSTAWA];

void WczytajDane(){
  scanf("%d %d",&n,&mod);
  for (int i = 0; i < n; ++i) scanf("%d",permutacja+i);
}

//Zwraca liczbe mniejszych elementow w drzewie licznikowym.
//Przejscie od liscia do korzenia drzewa.
int IleMniejszych(int x){
  int wynik = 0;
  int pozycja = x + PODSTAWA;
  while (pozycja > 1){
    if (pozycja % 2) wynik += drzewo_licznikowe[pozycja-1];
    pozycja /= 2;
  }
  return wynik;
}

int Potega(int a,int n){
  int wynik = 1;
  int mnoznik = a;
  while (n){
    if (n%2) wynik = (long long)wynik*mnoznik%mod;
    mnoznik = (long long)mnoznik*mnoznik%mod;
    n /= 2;
  }
  return wynik;
}

// Rozszerzony algorytm Euklidesa znajdujacy najwiekszy wspolny
// dzielnik a i b.
int RozszerzonyEuklides(int a, int b, long long &xp, long long &yp){
  if (a==0){
    xp=0; yp=1;
    return b;
  }
  long long x,y;
  int d = RozszerzonyEuklides(b%a, a, x, y);
  yp = x;
  xp = y-(b/a)*x;
  return d;
}

int OdwrotnoscModulo(int a){
  long long x, y;
  RozszerzonyEuklides(a, mod, x, y);
  if (x < 0LL) return (mod - ((-x) % mod)) % mod;
  return x % mod;
}

vector<pair<int,int> > rozklad; //pary (liczba_pierwsza,krotnosc)
                                //w aktualnej liczbie permutacji
int reszta = 1; //iloczyn liczby wzglednie pierwszych z mod

// Pomnozenie aktualnej liczby permutacji przez x.
void Pomnoz(int x){
  for (int i = 0; i < (int)rozklad.size(); ++i)
    while (x % rozklad[i].first == 0){
      x /= rozklad[i].first;
      rozklad[i].second++;
    }
  reszta = (long long)reszta*x%mod;
}

// Podzielenie aktualnej liczby permutacji przez x.
void Podziel(int x){
  for (int i = 0; i < (int)rozklad.size(); ++i)
    while (x % rozklad[i].first == 0){
      x /= rozklad[i].first;
      rozklad[i].second--;
    }
  reszta = (long long)reszta*OdwrotnoscModulo(x)%mod;
}

void InicjalizujLiczbePermutacji(){
  //rozkladamy mod na czynniki pierwsze
  int i = 2;
  int x = mod;
  while (x > 1 && i*i <= x){
    int ile = 0;
    while (x%i == 0) x /= i, ile++;
    if (ile) rozklad.push_back(make_pair(i,0));
    i++;
  }
  if (x > 1) rozklad.push_back(make_pair(x,0));

  for (i = 2; i <= n; ++i) Pomnoz(i);
  for (i = 0; i <= MAX_ZAKRES; ++i)
    for (int j = 2; j <= drzewo_licznikowe[PODSTAWA+i]; ++j)
      Podziel(j);
}

void UsunElement(int a){
  //zmniejsza sie liczba wszystkich elementow permutacji
  Podziel(drzewo_licznikowe[1]);
  //zmniejsza sie liczba elementow o danej wartosci
  Pomnoz(drzewo_licznikowe[PODSTAWA+a]);
  //usuwanie z drzewa licznikowego
  int pozycja = a+PODSTAWA;
  while (pozycja >= 1){
    drzewo_licznikowe[pozycja]--;
    pozycja /= 2;
  }
}

int LiczbaPermutacji(){
  int wynik = reszta;
  for (int i = 0; i < (int)rozklad.size(); ++i)
    wynik = (long long)wynik*Potega(rozklad[i].first,rozklad[i].second)%mod;
  return wynik;
}

void ObliczWynik(){
  int wynik = 0;
  //konstrukcja drzewa licznikowego zawierajacego
  //wszystkie elementy permutacji
  for (int i = 0; i < n; ++i) drzewo_licznikowe[PODSTAWA+permutacja[i]]++;
  for (int i = PODSTAWA-1; i >= 1; --i)
    drzewo_licznikowe[i] = drzewo_licznikowe[2*i]+drzewo_licznikowe[2*i+1];

  InicjalizujLiczbePermutacji();
  for (int i = 0; i < n; ++i){
    int suma = IleMniejszych(permutacja[i]);
    if (suma > 0){
      Pomnoz(suma);
      Podziel(n-i);
      wynik = (wynik+LiczbaPermutacji())%mod;
      Pomnoz(n-i);
      Podziel(suma);
    }
    UsunElement(permutacja[i]);
  }
  printf("%d\n",(wynik+1)%mod);
}

int main(){
  WczytajDane();
  ObliczWynik();
  return 0;
}
