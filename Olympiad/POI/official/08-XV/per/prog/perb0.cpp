/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     perb0.cpp                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie zakladajace, ze kazda liczba w permutacji     *
 *             jest inna od pozosta³ych.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


#define MAX_N 300000

int n,m;    // liczby z tresci zadania
int T[MAX_N];    // permutacja z zadania
int najw;    // najwiekszy element w permutacji
int h;      // wysokosc drzewa licznikowego
int ilosc[1048601];  // wezly drzewa licznikowego
int silnia[MAX_N];  // reszty z dzielenie przez m silnii kolejnych liczb naturalnych



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


// funkcja obliczajaca wynik - po dokladny sposob dzialania
// odsylam do opracowania - rozwiazania niepoprawne
inline int oblicz_wynik()
{
  silnia[0]=1;
  silnia[1]=1;

  for(int i=2; i<n; i++)
    silnia[i]=(int)((((long long)silnia[i-1])*((long long)i))%m);

  long long res=1LL;
  int ile;

  for(int i=0; i<n-1; i++)
  {
    ile=mniejsze(T[i]);
    res+=((long long)silnia[n-1-i])*((long long)ile);
    res%=m;
    wstaw(T[i],-1);
  }

  return (int)res;
}



int main()
{
  scanf("%d%d",&n,&m);
  for(int i=0; i<n; i++)
    scanf("%d",T+i);

  buduj_drzewo();

  int res=oblicz_wynik();
  printf("%d\n",res);

  return 0;
}

