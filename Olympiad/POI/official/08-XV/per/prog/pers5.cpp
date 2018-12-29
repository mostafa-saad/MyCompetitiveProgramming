/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     pers5.cpp                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie o zlozonosci O(n^2lgm) z drzewem licznikowym. *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


#define MAX_N 300000
#define MAX_P 28001


int n,m;    // liczby z tresci zadania
int T[MAX_N];    // permutacja z zadania
int najw;    // najwiekszy element w permutacji
int h;      // wysokosc drzewa licznikowego
int ilosc[1048601];  // wezly drzewa licznikowego
int il;      // ilosc liczb pierwszych
int nr[MAX_N+1];  // tablica z numerami kolejnych liczb pierwszych
int rozklad[MAX_N+1];  // tablica umozliwiacaja szybki rozklad dowolnej liczby na czynniki pierwsze
int pierw[MAX_P];  // ilosc liczb pierwszych w rozkladzie Si
int L[MAX_P];    // i-ta liczba pierwsza



// fukcja ktora buduje pelne statyczne drzewo licznikowe
// najw - najwiekszy element permutacji T
// h    - wysokosc drzewa
inline void buduj_drzewo()
{
  najw=*max_element(T,T+n);

  // aby wygodnie korzystalo sie z drzewa
  // potrzebujemy aby mialo conajmniej najw+1 lisci
  // ktore kolejno beda odpowiadac liczbom 0,..,najw
  for(h=0; (1<<h)<najw+1; h++);

  // teraz liscie drzewa maja w tablicy numery 2^h,..,2^(h+1)-1
  int pom=(1<<h);

  for(int i=0; i<n; i++)
    ilosc[pom+T[i]]++;
  for(int i=pom-1; i>0; i--)
    ilosc[i]=ilosc[2*i]+ilosc[2*i+1];
}


// funkcja modyfikujaca drzewo licznikowe
// wstaw(x,ile) zmienia ilosc elementow x o ile
inline void wstaw(int x, int ile)
{
  int i=(1<<h)+x;
  ilosc[i]+=ile;i/=2;
  while (i)
  {
    ilosc[i]=ilosc[2*i]+ilosc[2*i+1];
    i/=2;
  }
}


// fukcja zwracajaca ilosc elementow mniejszych niz x
inline int mniejsze(int x)
{
  int i=(1<<h)+x,res=0;
  while (i>1)
  {
    if (i%2)
      res+=ilosc[i-1];
    i/=2;
  }
  return res;
}


// funkcja wykonujaca szybkie potegowanie
// dostajac na wejsciu x,n,m, oblicza x^n mod m
inline int potega(int x, int n, int m)
{
  long long res=1LL,akt=(long long)x;
  while (n)
  {
    if (n%2)
    {
      res=(res*akt)%m;
      n--;
    }
    akt=(akt*akt)%m;
    n/=2;
  }
  return (int)res;
}


// sito eratostenesa umozliwajace pozniej
// szybki rozklad kazdej liczby na czynnkik pierwsze
// oraz numerujace kolejne liczby pierwsze z zakresu [2..roz]
inline void sito_eratostenesa(int roz)
{
  il=0;
  bool Q[roz+1];

  for(int i=0; i<=roz; i++)
    nr[i]=-1,rozklad[i]=-1,Q[i]=true;

  for(int i=2; i<=roz; i++)
    if (Q[i])
    {
      L[il]=i;
      nr[i]=il++;
      rozklad[i]=i;
      for(int j=2*i; j<=roz; j+=i)
      {
        Q[j]=false;
        if (rozklad[j]==-1)
          rozklad[j]=i;
      }
    }
}


// trzy funkcje do obslugi reprezentacji liczb w postaci
// rozkladu na liczby pierwsze
// 1) obliczanie wartosci danej liczby modulo m
// 2) mnozenie danej liczby przez int
// 3) dzielenie danej liczby przez int

inline int wartosc()
{
  long long res=1LL;
  for(int i=0; i<il; i++)
    res*=potega(L[i],pierw[i],m),res%=m;
  return (int)res;
}


inline void pomnoz(int x)
{
  while (x!=1)
  {
    pierw[nr[rozklad[x]]]++;
    x/=rozklad[x];
  }
}


inline void podziel(int x)
{
  while (x!=1)
  {
    pierw[nr[rozklad[x]]]--;
    x/=rozklad[x];
  }
}


// funkcja obliczajaca S0 i zwracajaca jego rozklad na liczby pierwsze
inline void oblicz_SO()
{
  for(int i=0; i<il; i++)
    pierw[i]=0;

  for(int i=2; i<n; i++)
    pomnoz(i);

  int pom=(1<<h);
  for(int i=1; i<=najw; i++)
    for(int j=2; j<=ilosc[pom+i]; j++)
      podziel(j);
}


// funkcja obliczajaca wynik - po dokladny sposob dzialania
// odsylam do opracowania - rozwiazania wolniejsze
inline int oblicz_wynik()
{
  long long res=1LL;

  oblicz_SO();
  int ile=mniejsze(T[0]);

  if (ile!=0)
  {
    pomnoz(ile);
    res+=wartosc(),res%=m;
    podziel(ile);
  }


  for(int i=1; i<n-1; i++)
  {
    pomnoz(ilosc[(1<<h)+T[i-1]]);
    podziel(n-i);

    wstaw(T[i-1],-1);
    ile=mniejsze(T[i]);
    if (!ile)
      continue;

    pomnoz(ile);
    res+=wartosc(),res%=m;
    podziel(ile);
  }

  return (int)res;
}



int main()
{
  scanf("%d%d",&n,&m);
  for(int i=0; i<n; i++)
    scanf("%d",T+i);

  buduj_drzewo();
  sito_eratostenesa(n);

  int res=oblicz_wynik();
  printf("%d\n",res);

  return 0;
}

