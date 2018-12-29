/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     per.cpp                                                   *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


#define MAX_N 300000

int n,m;             // liczby z tresci zadania
int T[MAX_N];        // permutacja z zadania
int najw;            // najwiekszy element w permutacji
int h;               // wysokosc drzewa licznikowego
int ilosc[1048601];  // wezly drzewa licznikowego
int pod[10],wyk[10]; // m=pod[0]^wyk[0] * ...
int dziel[10];       // m=dziel[0]*dziel[1]*.. oraz NWD(dziel[i],dziel[j])=1 dla i<>j
int s;               // ilosc roznych liczb pierwszych dzielacych m



// rozszerzony algorytm Euklidesa
// dostajac na wejsciu liczby a oraz b
// zwraca trojke liczb takich, ze a*x+b*y=NWD(x,y)
inline void NWD(int a, int b, long long &x, long long &y, int &d)
{
  if (!b)
  {
    x=a,y=0;
    d=a;
  }
  else
  {
    long long x1,y1;
    int d1;
    NWD(b,a%b,x1,y1,d1);
    x=y1;
    y=x1-y1*(a/b);
    d=d1;
  }
}


// funkcja obliczajaca odwrotnosc pewnej liczby s modulo t
// na wejsciu musi byc spelniony warunek NWD(s,t)=1
inline int odwrotnosc(int s, int t)
{
  long long x,y;
  int d;
  NWD(s,t,x,y,d);
  return (int)((x%t+t)%t);
}


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


// fukcja rozkladajaca m na czynniki pierwsze
// po wywolaniu tej funkcji mamy:
// m=pod[0]^wyk[0]*pod[1]^wyk[1]*..
inline void rozklad_m()
{
  int M=m;
  s=0;
  for(int i=2; i*i<=m; i++)
    if (M%i==0)
    {
      int il=0,t=1;
      while (M%i==0)
        M/=i,il++,t*=i;
      pod[s]=i;
      wyk[s]=il;
      dziel[s++]=t;
    }
  if (M>1)
  {
    pod[s]=M;
    wyk[s]=1;
    dziel[s++]=M;
  }
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


// trzy funkcje do obslugi naszej reprezentacji liczb
// gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
// 1) funkcja zwracajaca wartosc modulo dziel[nr]
// 2) funkcja mnozaca liczbe w naszej reprezentacji przez int
// 3) funkcja dzielaca liczbe w naszej reprezentacji przez int

inline int wartosc(pair<int,int> x, int nr)
{
  if (x.second>=wyk[nr])
    return 0;
  return (int)((((long long)potega(pod[nr],x.second,dziel[nr]))*x.first)%dziel[nr]);
}


inline pair<int,int> pomnoz(pair<int,int> w, int x, int nr)
{
  int p=pod[nr];
  while (x%p==0)
    w.second++,x/=p;
  w.first=(int)(((long long)(w.first)*x)%dziel[nr]);
  return w;
}


inline pair<int,int> podziel(pair<int,int> w, int x, int nr)
{
  int p=pod[nr];
  while (x%p==0)
    w.second--,x/=p;
  w.first=(int)(((long long)(w.first)*odwrotnosc(x,dziel[nr]))%dziel[nr]);
  return w;
}


// funkcja obliczajaca SO i zwracajaca wynik w naszej reprezentacji
// gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
// oraz S0=(n-1)!/[l1!*...*lnajw!]
inline pair<int,int> oblicz_S0(int nr)
{
  pair<int,int> res=make_pair(1,0);
  for(int i=2; i<n; i++)
    res=pomnoz(res,i,nr);

  int pom=(1<<h);
  for(int i=1; i<=najw; i++)
    for(int j=2; j<=ilosc[pom+i]; j++)
      res=podziel(res,j,nr);

  return res;
}


// funkcja skladajaca wynik z chinskiego twierdzenia o resztach
// dane wejsciowe reprezentuja: m=dziel[0]*..*dziel[s-1]
// ponadto wynik = a[i] (modulo dziel[i])
inline int chinskie_twierdzenie(int s, int *a)
{
  int w[10],c[10];
  for(int i=0; i<s; i++)
  {
    w[i]=m/dziel[i];
    c[i]=(int)(((long long)(w[i]))*odwrotnosc(w[i],dziel[i]));
  }

  long long res=0;
  for(int i=0; i<s; i++)
    res+=((long long)a[i])*c[i];
  res%=m;
  return (int)res;
}


// funkcja obliczajaca wynik - po dokladny sposob dzialania
// odsylam do opracowania
inline int oblicz_wynik()
{
  pair<int,int> temp[10];
  int a[10],ile;

  ile=mniejsze(T[0]);
  for(int i=0; i<s; i++)
  {
    temp[i]=oblicz_S0(i);
    a[i]=0;

    if (ile!=0)
    {
      temp[i]=pomnoz(temp[i],ile,i);
      a[i]=wartosc(temp[i],i);
      temp[i]=podziel(temp[i],ile,i);
    }
  }

  for(int i=1; i<n-1; i++)
  {
    for(int j=0; j<s; j++)
    {
      temp[j]=pomnoz(temp[j],ilosc[(1<<h)+T[i-1]],j);
      temp[j]=podziel(temp[j],n-i,j);
    }

    wstaw(T[i-1],-1);
    ile=mniejsze(T[i]);
    if (!ile)
      continue;

    for(int j=0; j<s; j++)
    {
      temp[j]=pomnoz(temp[j],ile,j);
      a[j]+=(int)(wartosc(temp[j],j));
      a[j]%=dziel[j];
      temp[j]=podziel(temp[j],ile,j);
    }
  }

  return (chinskie_twierdzenie(s,a)+1)%m;
}



int main()
{
  scanf("%d%d",&n,&m);
  for(int i=0; i<n; i++)
    scanf("%d",T+i);

  buduj_drzewo();
  rozklad_m();

  int res=oblicz_wynik();
  printf("%d\n",res);

  return 0;
}

